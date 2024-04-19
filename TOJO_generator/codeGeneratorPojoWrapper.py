# -*- coding: cp936 -*-

import sys                       # Load the sys module (����sysģ��)
import string
import os
import getpass

from codeGeneratorPojoJson import FindClassDir
#from codeGeneratorPojoJson import get_username
from fieldInfo import FieldInfo, parseFieldInfo


def ReplaceStrings(stringlist, fromString, toString):
    for i in range(0, len(stringlist)):
        s = stringlist[i]
        s = string.replace(s, fromString, toString);
        stringlist[i] = s

def CodeGenerate(declareTxt):
    f = open("WrapperTmpl.h")            # template.txt
    templateDeclareLines = f.readlines()          # Read all lines into a list
    f.close()
    
    f = open("WrapperTmpl.mm")            # template.txt
    templateImplLines = f.readlines()          # Read all lines into a list
    f.close()
    
    declareLines = []
    # open server file
    serverTxt = str.replace(declareTxt, "sdk-txt", "server-txt")
    if os.path.exists(serverTxt):
        f = open(serverTxt)
        declareLines = f.readlines()
        f.close
        
    f = open(declareTxt)#(sys.argv[1])            # Filename on the command line (�������ж�ȡ�ļ���)
    declareLines += f.readlines()          # Read all lines into a list , strip all space and \n
    f.close()
    
    if len(declareLines) == 0:
        return
    
    baseClassString = ""
    typeString = ""
    nameString = ""
    defaultValue = ""
    isSdkOnly = False
    sdkClassString = declareLines[0].strip("\n").strip()
    slashIndex = sdkClassString.find('/')
    classComment = '''/**
 * classComment
 */'''
    if slashIndex != -1:
        if sdkClassString[slashIndex:].strip('/').strip() != '':
            classComment = str.replace(classComment, "classComment", sdkClassString[slashIndex:].strip('/'))
            classComment = str.replace(classComment, "\\n", "\n * \n * ")
        else:
            classComment = ""
        sdkClassString = sdkClassString[:slashIndex].strip()
    else:
        sdkClassString = sdkClassString.strip()
        classComment = ''

    (projectName, classDir) = FindClassDir(sdkClassString, False)
    if projectName == '' or classDir == '':
        return

    sdkClassSubPath = classDir + sdkClassString
    bbmClassNameStr = "BBM" + sdkClassString
    
    # check data
    classObjectStr = sdkClassString[0].lower() + sdkClassString[1:]  # for initial
    
    #list string
    variableListstring = ""
    constructorParameterListString = ""
    
    defaultInitialListString = ""
    parameterListString = ""
    assignmentListString = ""
    methodDeclareString = ""
    methodImplString = ""

    baseClassListString = ""
    baseClassInitListString = "super init"
    includeListString = ""
    preDeclarationListString = ""

    ToSDKObjectListString = ""

    includePathPrefix = '#import "'

    (projectName, classDir) = FindClassDir(sdkClassString, False)
    if projectName == '' or classDir == '':
        return

    includePathPrefix += projectName + '/model'
    includeSDKPathPrefix = '#import "' + projectName + '/model'

    newIncludeFile = includePathPrefix + classDir + bbmClassNameStr + '.h"\n'
    if not newIncludeFile in includeListString:
        includeListString += newIncludeFile

    newIncludeFile = '#include <vector>\n'
    if not newIncludeFile in includeListString:
        includeListString += newIncludeFile

    newIncludeFile = '#include <string>\n'
    if not newIncludeFile in includeListString:
        includeListString += newIncludeFile

    # obj ptr
    serviceInitializeString = '''
        BBMobileSDK::ClassName *ClassObjectObj = (BBMobileSDK::ClassName*)[ClassObject pointerValue];
        if (NULL == ClassObjectObj)
        {
            return self;
        }
'''

    serviceInitializeString = str.replace(serviceInitializeString, "ClassName", sdkClassString);
    serviceInitializeString = str.replace(serviceInitializeString, "ClassObject", classObjectStr);

    defaultInitialListString += serviceInitializeString
    
    for i in range(1, len(declareLines)):
        lineString = declareLines[i]
        lineString = lineString.lstrip()
        lineString = lineString.rstrip()
        lineString = lineString.rstrip("\n")
        if lineString == "":
            continue
        
        ################ decompose  ###################
        splittedStrings = lineString.split()

        commentString = ""
        for i in range(1, len(splittedStrings)):
            if splittedStrings[i].startswith("//") :
                commentString = " ".join(splittedStrings[i:])
                splittedStrings = splittedStrings[:i]
                break;

        if len(splittedStrings) == 1:
            baseClassString = splittedStrings[0]
        else:
            fieldInfo = parseFieldInfo(lineString)
            if not fieldInfo :
                continue
                
            typeString = fieldInfo.type
            nameString = fieldInfo.name
            defaultValue = fieldInfo.defaultVal
            isSdkOnly = fieldInfo.isSdkOnly
            #isSerializable = fieldInfo.isSerializable
        
        ################################################
        
        if len(splittedStrings) == 1:
            baseClassListString += "BBM" + baseClassString + ", "   # less
            baseClassInitListString += "With" + baseClassString + " : " + classObjectStr
            
            ToSDKObjectListString += "        [super toSDKObject: value];\n"
            
            if not ('BBM' + baseClassString + '.h"') in preDeclarationListString:
                preDeclarationListString += buildBaseClassImportString(classDir, baseClassString)

        else:

            #skip sdk only fields
            if isSdkOnly:
                continue

            osTypeString = ""
            if typeString[-4:] == "long":
                typeString += " long"

            if typeString == "struct tm":  # local time, no support
                osTypeString = "NSDate"
                continue


#includelist
            if typeString[-4:] == "VPtr":

                (projectNameTemp, classDirTemp) = FindClassDir(typeString[:-4], False)

                newIncludeFile = '#import "' + projectNameTemp + '/model' + classDirTemp + "BBM" + typeString[:-4] + '.h"\n'
                if not newIncludeFile in includeListString:
                    includeListString += newIncludeFile
                    preDeclarationListString += "@class BBM" + typeString[:-4] + ";\n"

                newIncludeFile = '#import "' + projectNameTemp + '/model' + classDirTemp + typeString[:-4] + '.h"\n'
                if not newIncludeFile in includeListString:
                    includeListString += newIncludeFile
                    
            elif typeString[-3:] == "Ptr": # and not ('BBM' + typeString[:-3] + '.h"') in includeListString:

                (projectNameTemp, classDirTemp) = FindClassDir(typeString[:-3], False)

                newIncludeFile = '#import "' + projectNameTemp + '/model' + classDirTemp + "BBM" + typeString[:-3] + '.h"\n'
                if not newIncludeFile in includeListString:
                    includeListString += newIncludeFile
                    preDeclarationListString += "@class BBM" + typeString[:-3] + ";\n"

                newIncludeFile = '#import "' + projectNameTemp + '/model' + classDirTemp + typeString[:-3] + '.h"\n'
                if not newIncludeFile in includeListString:
                    includeListString += newIncludeFile

#type conversion, INIT LIST
            if typeString == "std::vector<std::string>":
                defaultInitialListString += "\n        " + typeString + " " + nameString + "_ = " + classObjectStr + "Obj->Get" + nameString[0].upper() + nameString[1:] + "();\n\n"
                defaultInitialListString += "        NSMutableArray<NSString*> *" + nameString[:-1] + "Array = [[NSMutableArray alloc] init];\n"
                defaultInitialListString += "        for(int i=0; i<" + nameString + "_.size(); i++)\n"
                defaultInitialListString += "        {\n"
                defaultInitialListString += "            [" + nameString[:-1] + "Array addObject: [NSString stringWithUTF8String:" + nameString + "_[i].c_str()] ];\n"
                defaultInitialListString += "        }\n"
                
                defaultInitialListString += "        self." + nameString + " = " + nameString[:-1] + "Array;\n\n"
                
                osTypeString = "NSMutableArray<NSString*>"

            if typeString == "std::vector<int>":
                defaultInitialListString += "\n        " + typeString + " " + nameString + "_ = " + classObjectStr + "Obj->Get" + nameString[0].upper() + nameString[1:] + "();\n\n"
                defaultInitialListString += "        NSMutableArray<NSNumber*> *" + nameString[:-1] + "Array = [[NSMutableArray alloc] init];\n"
                defaultInitialListString += "        for(int i=0; i<" + nameString + "_.size(); i++)\n"
                defaultInitialListString += "        {\n"
                defaultInitialListString += "            [" + nameString[:-1] + "Array addObject: [NSNumber numberWithInt:" + nameString + "_[i]] ];\n"
                defaultInitialListString += "        }\n"
                
                defaultInitialListString += "        self." + nameString + " = " + nameString[:-1] + "Array;\n\n"
                
                osTypeString = "NSMutableArray<NSNumber*>"

            if typeString[-4:] == "VPtr":
                defaultInitialListString += "\n        BBMobileSDK::" + typeString + " " + nameString + "_ = " + classObjectStr + "Obj->Get" + nameString[0].upper() + nameString[1:] + "();\n\n"
                defaultInitialListString += "        NSMutableArray<BBM" + typeString[:-4] + "*> *" + nameString[:-1] + "Array = [[NSMutableArray alloc] init];\n"
                defaultInitialListString += "        for(int i=0; i<" + nameString + "_.size(); i++)\n"
                defaultInitialListString += "        {\n"
                defaultInitialListString += "            if (" + nameString + "_[i] != NULL)\n"
                defaultInitialListString += "            {\n"
                defaultInitialListString += "                [" + nameString[:-1] + "Array addObject: [[" + "BBM" + typeString[:-4] +" alloc] initWith" + typeString[:-4] + ":[NSValue value:&" + nameString + "_[i]  withObjCType:@encode(void *)]] ];\n"
                defaultInitialListString += "            }\n"
                

                defaultInitialListString += "        }\n"
                
                defaultInitialListString += "        self." + nameString + " = " + nameString[:-1] + "Array;\n\n"

                osTypeString = "NSMutableArray" + "<BBM" + typeString[:-4] + "*>"
                    
            elif typeString[-3:] == "Ptr":
                defaultInitialListString += "\n        BBMobileSDK::" + typeString + " " + nameString + "_ = " + classObjectStr + "Obj->Get" + nameString[0].upper() + nameString[1:] + "();\n"
                defaultInitialListString += "        if (" + nameString + "_ != NULL)\n"
                defaultInitialListString += "        {\n"
                defaultInitialListString += "            self." + nameString + " = [[BBM" + typeString[:-3] + " alloc] initWith" + typeString[:-3] + ":[NSValue value:&" + nameString + "_ withObjCType:@encode(void *)]];\n"
                defaultInitialListString += "        }\n"
                osTypeString = "BBM" + typeString[:-3]

            if typeString == "std::map<std::string, std::string>":
                mapInitString = '''
                           typeString nameStrings_ = classObjectStrObj->GetClassString();
                           
                           NSMutableArray *nameStringDictionary = [[NSMutableDictionary alloc] init];
                           for(int i=0; i<" + nameString + "_.size(); i++)
                           {
                               [" + nameString[:-1] + "Array addObject: [NSNumber numberWithInt:" + nameString + "_[i]] ];
                           }
                   
                           self." + nameString + " = " + nameString[:-1] + "Array;
                   
                   '''
                           
                osTypeString = "NSMutableDictionary"



            initialStringTemplate = '''
        if (!classObjectStrObj->GetNameString().empty())
        {
            self.nameString = [NSString stringWithUTF8String: classObjectStrObj->GetNameString().c_str()];
        }
'''
            
            if typeString == "std::string":
                osTypeString = "NSString"
                if nameString == "id" or nameString == "description":
                    wrapNameString = nameString + "Str"
                    
                    initialStringTemplate = str.replace(initialStringTemplate, "nameString", wrapNameString)
                    initialStringTemplate = str.replace(initialStringTemplate, "NameString", nameString[0].upper() + nameString[1:])
                    initialStringTemplate = str.replace(initialStringTemplate, "classObjectStr", classObjectStr)
                else:
                    initialStringTemplate = str.replace(initialStringTemplate, "nameString", nameString)
                    initialStringTemplate = str.replace(initialStringTemplate, "NameString", nameString[0].upper() + nameString[1:])
                    initialStringTemplate = str.replace(initialStringTemplate, "classObjectStr", classObjectStr)

                defaultInitialListString += initialStringTemplate;

            commentTempl = '''
/**
 * commentString
 */
'''

            if commentString != "":
                commentString = commentString.strip('/')
                commentString = str.replace(commentString, "\\n", "\n * \n * ")
                variableListstring += str.replace(commentTempl, "commentString", commentString)
            if typeString=="bool" or typeString=="int" or typeString=="float" or typeString=="double" or typeString=="long" or typeString=="long long":
                variableListstring += "@property (nonatomic, assign) " + typeString + " " + nameString + "; " + "\n"
                defaultInitialListString += "        self." + nameString + " = " + classObjectStr + "Obj->Get" + nameString[0].upper() + nameString[1:] + "();\n"
            else:
                if nameString == "id" or nameString == "description":
                    wrapNameString = nameString + "Str"
                    variableListstring += "@property (nonatomic, strong) " + osTypeString + " *" + wrapNameString + "; " + "\n"
                else:
                    variableListstring += "@property (nonatomic, strong) " + osTypeString + " *" + nameString + "; " + "\n"

####   to sdk object
            toSDKTemplateVecStr = '''
        std::vector<std::string> nameString_;
        if (nil != _nameString)
        {
            for (NSString *nameStringItem in _nameString)
            {
                if (nil != nameStringItem)
                {
                    nameString_.push_back([nameStringItem UTF8String]);
                }
            }
            classObjectStrObj->SetNameString(nameString_);
        }
''';
            if typeString == "std::vector<std::string>":
                toSDKTemplateVecStr = str.replace(toSDKTemplateVecStr, "nameString", nameString);
                toSDKTemplateVecStr = str.replace(toSDKTemplateVecStr, "NameString", nameString[0].upper() + nameString[1:]);
                toSDKTemplateVecStr = str.replace(toSDKTemplateVecStr, "classObjectStr", classObjectStr);

                ToSDKObjectListString += toSDKTemplateVecStr;

            ####

            toSDKTemplateVecInt = '''
        std::vector<typeString> nameString_;
            
        if (nil != _nameString)
        {
            for (NSNumber *nameStringItem in _nameString)
            {
                nameString_.push_back([nameStringItem intValue]);
            }
            classObjectStrObj->SetNameString(nameString_);
        }
''';
            if typeString == "std::vector<int>":
                toSDKTemplateVecInt = str.replace(toSDKTemplateVecInt, "typeString", "int");
                toSDKTemplateVecInt = str.replace(toSDKTemplateVecInt, "nameString", nameString);
                toSDKTemplateVecInt = str.replace(toSDKTemplateVecInt, "NameString", nameString[0].upper() + nameString[1:]);
                toSDKTemplateVecInt = str.replace(toSDKTemplateVecInt, "classObjectStr", classObjectStr);

                ToSDKObjectListString += toSDKTemplateVecInt;

            ######
            toSDKTemplateVPtr = '''
        BBMobileSDK::typeStringVPtr nameString_;
            
        if (nil != _nameString)
        {
            for (BBMtypeString *nameStringItem in _nameString)
            {
                if (nil != nameStringItem)
                {
                    BBMobileSDK::typeStringPtr nameStringSDKItem(new BBMobileSDK::typeString);
                    [nameStringItem toSDKObject: [NSValue value:&nameStringSDKItem  withObjCType:@encode(void *)]];
                    nameString_.push_back(nameStringSDKItem);
                }
            }
            classObjectStrObj->SetNameString(nameString_);
        }
''';
            if typeString[-4:] == "VPtr":
                toSDKTemplateVPtr = str.replace(toSDKTemplateVPtr, "typeString", typeString[:-4]);
                toSDKTemplateVPtr = str.replace(toSDKTemplateVPtr, "nameString", nameString);
                toSDKTemplateVPtr = str.replace(toSDKTemplateVPtr, "NameString", nameString[0].upper() + nameString[1:]);
                toSDKTemplateVPtr = str.replace(toSDKTemplateVPtr, "classObjectStr", classObjectStr);

                ToSDKObjectListString += toSDKTemplateVPtr;
            elif typeString[-3:] == "Ptr":
                toSDKTemplatePtr = '''
        if (nil != self.nameString)
        {
            BBMobileSDK::typeStringPtr nameString_(new BBMobileSDK::typeString);
            [self.nameString toSDKObject: [NSValue value:&nameString_  withObjCType:@encode(void *)]];
            classObjectStrObj->SetNameString(nameString_);
        }
''';
                toSDKTemplatePtr = str.replace(toSDKTemplatePtr, "typeString", typeString[:-3]);
                toSDKTemplatePtr = str.replace(toSDKTemplatePtr, "nameString", nameString);
                toSDKTemplatePtr = str.replace(toSDKTemplatePtr, "NameString", nameString[0].upper() + nameString[1:]);
                toSDKTemplatePtr = str.replace(toSDKTemplatePtr, "classObjectStr", classObjectStr);
                
                ToSDKObjectListString += toSDKTemplatePtr;

            if typeString == "std::map<std::string, std::string>":
                mapInitString = '''
                    typeString nameStrings_ = classObjectStrObj->GetClassString();
                    
                    NSMutableArray *nameStringDictionary = [[NSMutableDictionary alloc] init];
                    for(int i=0; i<" + nameString + "_.size(); i++)
                    {
                    [" + nameString[:-1] + "Array addObject: [NSNumber numberWithInt:" + nameString + "_[i]] ];
                    }
                    
                    self." + nameString + " = " + nameString[:-1] + "Array;
                    
                    '''

            ###string
            toSDKTemplateString = '''
        if (nil != self.nameString)
        {
            classObjectStrObj->SetNameString([self.nameString UTF8String]);
        }
''';
    
            if typeString == "std::string":
                if nameString == "id" or nameString == "description":
                    wrapNameString = nameString + "Str"
                    toSDKTemplateString = str.replace(toSDKTemplateString, "nameString", wrapNameString)
                else:
                    toSDKTemplateString = str.replace(toSDKTemplateString, "nameString", nameString)
                toSDKTemplateString = str.replace(toSDKTemplateString, "NameString", nameString[0].upper() + nameString[1:]);
                toSDKTemplateString = str.replace(toSDKTemplateString, "classObjectStr", classObjectStr);
                
                ToSDKObjectListString += toSDKTemplateString;

            ###native, simple
            toSDKTemplateSimple = "        classObjectStrObj->SetNameString(self.nameString);\n";

            if typeString=="bool" or typeString=="int" or typeString=="float" or typeString=="double" or typeString=="long" or typeString=="long long":
                toSDKTemplateSimple = str.replace(toSDKTemplateSimple, "nameString", nameString);
                toSDKTemplateSimple = str.replace(toSDKTemplateSimple, "NameString", nameString[0].upper() + nameString[1:]);
                toSDKTemplateSimple = str.replace(toSDKTemplateSimple, "classObjectStr", classObjectStr);
                ToSDKObjectListString += toSDKTemplateSimple;


    baseClassListString = baseClassListString.rstrip(", ")
    variableListstring = variableListstring.rstrip(" \n")

    assignmentListString = assignmentListString.rstrip(" \n        ")

    ReplaceStrings(templateDeclareLines, "classComment", classComment)
   # ReplaceStrings(templateDeclareLines, "Yi Zheng", get_username())
    ReplaceStrings(templateDeclareLines, "ClassName", sdkClassString)
    ReplaceStrings(templateDeclareLines, "ClassObject", classObjectStr)
    ReplaceStrings(templateDeclareLines, "SDKClass", sdkClassString)
    
    ReplaceStrings(templateDeclareLines, "PreDeclarationList", preDeclarationListString)
    
    ReplaceStrings(templateDeclareLines, "VariableList", variableListstring)
    ReplaceStrings(templateDeclareLines, "DefaultInitializationList", defaultInitialListString)
    ReplaceStrings(templateDeclareLines, "ConstructorParameterList", constructorParameterListString)
    ReplaceStrings(templateDeclareLines, "ParameterInitializationList", parameterListString)
    ReplaceStrings(templateDeclareLines, "AssignmentList", assignmentListString)
    ReplaceStrings(templateDeclareLines, "MethodDeclaration", methodDeclareString)
    ReplaceStrings(templateDeclareLines, "MethodImpl", methodImplString)
    if baseClassListString != "":
        ReplaceStrings(templateDeclareLines, "NSObject", baseClassListString)
        ReplaceStrings(templateImplLines, "NSObject", baseClassListString)

    #ReplaceStrings(templateImplLines, "Yi Zheng", get_username())
    ReplaceStrings(templateImplLines, "ClassName", sdkClassString)
    ReplaceStrings(templateImplLines, "ClassObject", classObjectStr)
    ReplaceStrings(templateImplLines, "SDKClass", sdkClassString)
    ReplaceStrings(templateImplLines, "SDKSubPath", sdkClassSubPath[1:])
    ReplaceStrings(templateImplLines, "ProjectName", projectName)
    ReplaceStrings(templateImplLines, "IncludeList", includeListString)


    
    ReplaceStrings(templateImplLines, "VariableList", variableListstring)
    ReplaceStrings(templateImplLines, "DefaultInitializationList", defaultInitialListString)
    ReplaceStrings(templateImplLines, "ConstructorParameterList", constructorParameterListString)
    ReplaceStrings(templateImplLines, "ParameterInitializationList", parameterListString)
    ReplaceStrings(templateImplLines, "AssignmentList", assignmentListString)
    ReplaceStrings(templateImplLines, "MethodDeclaration", methodDeclareString)
    ReplaceStrings(templateImplLines, "MethodImpl", methodImplString)

    ReplaceStrings(templateImplLines, "ToSDKObjectList", ToSDKObjectListString)

    ReplaceStrings(templateImplLines, "BaseClassInitList", baseClassInitListString)

#########################################################
    incPath = str.replace(os.path.dirname(declareTxt), "-txt", "-gen/wrapinc")
    if not os.path.exists(incPath):
        os.makedirs(incPath)
    
    f = open(incPath + "/" + bbmClassNameStr + ".h","w")     # Open file for writing
    for s in templateDeclareLines:
        f.write(s)
    f.close()
    
    srcPath = str.replace(os.path.dirname(declareTxt), "-txt", "-gen/wrapsrc")
    if not os.path.exists(srcPath):
        os.makedirs(srcPath)
    
    f = open(srcPath + "/" + bbmClassNameStr + ".mm","w")     # Open file for writing
    for s in templateImplLines:
        f.write(s)
    f.close()

#    if "server-txt" in os.path.dirname(declareTxt):
#        txtPath = str.replace(os.path.dirname(declareTxt), "server-txt", "sdk-txt")
#        if not os.path.exists(txtPath):
#            os.makedirs(txtPath)
#
#        txtSDKfilename = txtPath + "/" + bbmClassNameStr + ".txt"
#        if os.path.exists(txtSDKfilename):
#            os.remove(txtSDKfilename)


#    if "server-txt" in os.path.dirname(declareTxt):
#        txtPath = str.replace(os.path.dirname(declareTxt), "server-txt", "sdk-txt")
#        if not os.path.exists(txtPath):
#            os.makedirs(txtPath)
#        
#        txtSDKfilename = txtPath + "/" + bbmClassNameStr[3:] + ".txt"
#        if not os.path.exists(txtSDKfilename):
#            txtContent = "SDK" + bbmClassNameStr + "\n" + bbmClassNameStr
#            print " ####### New class file: " + txtSDKfilename
#            f = open(txtSDKfilename,"w")     # Open file for writing
#            f.write(txtContent)
#            f.close()
#########################################################

def buildBaseClassImportString(classDir, baseClassStr):
    importBaseClass = ""
    if baseClassStr == "":
        return importBaseClass

    importBaseClass += "#import \""

    if classDir != "":
        importBaseClass += '''../../../'''
    else:
        importBaseClass += '''../../'''

    proj = ""
    baseClassDir = "/"
    (proj, baseClassDir) = FindClassDir(baseClassStr, False)
    importBaseClass += proj + '/model' + baseClassDir + 'BBM' + baseClassStr + '.h\"\n'
    return importBaseClass

def VisitDir(path):
    for root,Dirs,files in os.walk(path):
        for file in files:
            print file
            if '.' in file and 'sdk-txt' in root:
                if file.rsplit('.',1)[1]=="txt":
                    CodeGenerate(os.path.join(root, file))

if __name__=="__main__":
    VisitDir(os.getcwd())


