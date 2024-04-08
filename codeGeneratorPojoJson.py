# -*- coding: cp936 -*-

import sys
import string
import os
import shutil
import getpass
import config
from fieldInfo import FieldInfo, parseFieldInfo

# read current username from system
#def get_username():
#    username = getpass.getuser()
#    dict = config.author_list
#    return dict[username] if dict.has_key(username) else username
#*/
def get_class_name(classNameStr):
    classNameStr = classNameStr.strip("\n").strip()
    slashIndex = classNameStr.find('/')
    if (slashIndex != -1):
        classNameStr = classNameStr[:slashIndex].strip()
    else:
        classNameStr = classNameStr.strip()
    return classNameStr

def ParseFullPath(fullPath, classNameStr, withClassName):
    splashItems = fullPath.split('/')
    projectName = splashItems[1]
    fileDirectory = ''
    if (len(splashItems) >= 2):
        for i in range(0, len(splashItems)):
            if (i != 1):
                fileDirectory += splashItems[i] + '/'
    if withClassName:
        fileDirectory += classNameStr

    return (projectName, fileDirectory)

def FindClassDir(classNameStr, withClassName=True):
    for root,Dirs,files in os.walk(os.getcwd()):
        for file in files:
            if '.' in file and 'server-txt' in root:
                if file.rsplit('.',1)[1]=="txt":
                    if classNameStr == file[:-4]:#declareLines[0].strip("\n").strip():
                        fullfilename = os.path.join(root, file)
                        rootSplitDirs = root.split("server-txt")
                        if (len(rootSplitDirs) == 2):
                            # here we need split project name and file directory
                            return ParseFullPath(rootSplitDirs[1], classNameStr, withClassName)
                        else:
                            print 'fatal error! file structure doesnot meet our request'
    return ('', '')

def ReplaceStrings(stringlist, fromString, toString):
    for i in range(0, len(stringlist)):
        s = stringlist[i]
        s = str.replace(s, fromString, toString); 
        stringlist[i] = s

def CodeGenerate(declareTxt):
    f = open("templateDeclaration.h")            # template.txt
    templateDeclareLines = f.readlines()          # Read all lines into a list
    f.close()

    f = open("templateImpl.cpp")            # template.txt
    templateImplLines = f.readlines()          # Read all lines into a list
    f.close()


    JsonDeclarationStr = ''''''

    JsonImplementationStr = ''''''
        
    declareLines = []
    sdkDeclareLines = []
    # open server file
    isOnlySDKFile = True
    serverTxt = str.replace(declareTxt, "sdk-txt", "server-txt")
    if os.path.exists(serverTxt):
        isOnlySDKFile = False
        
        f = open(serverTxt)
        declareLines = f.readlines()
        f.close
        #print declareLines


        JsonDeclarationStr = '''
        virtual void FromJson(rapidjson::Value &json);
        virtual void ToJson(rapidjson::Writer<rapidjson::StringBuffer> &writer, IToJsonFieldControllerPtr toJsonCtrl = nullptr);

        std::string ToJsonString(ToJsonFieldControllerType jsonCtrlType = ToJsonFieldControllerType::ToServer);
'''
        JsonProtectedDeclarationStr = '''
        virtual void ToJsonWithoutObject(rapidjson::Writer<rapidjson::StringBuffer> &writer,
                                         IToJsonFieldControllerPtr toJsonCtrl = nullptr);
'''

        JsonImplementationStr = '''
    void ClassName::FromJson(rapidjson::Value &jsonItems)
    {
        if (!jsonItems.IsNull())
        {
            JsonHelper::BeforeFromJson(this, jsonItems);
            FromJsonStrList

            JsonHelper::AfterFromJson(this, jsonItems);
        }
    }

    void ClassName::ToJson(rapidjson::Writer<rapidjson::StringBuffer> &writer, IToJsonFieldControllerPtr toJsonCtrl)
    {
        writer.StartObject();
        ToJsonWithoutObject(writer, toJsonCtrl);
        writer.EndObject();
    }

    void ClassName::ToJsonWithoutObject(rapidjson::Writer<rapidjson::StringBuffer> &writer, IToJsonFieldControllerPtr toJsonCtrl)
    {
        JsonHelper::BeforeToJson(this, writer);
        ToJsonStrList

        JsonHelper::AfterToJson(this, writer);
    }
    
    std::string ClassName::ToJsonString(ToJsonFieldControllerType jsonCtrlType)
    {
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);

        auto toJsonCtrl = ToJsonFieldControllerFactory::GetToJsonFieldController(jsonCtrlType);
        ToJson(writer, toJsonCtrl);

        return buffer.GetString();
    }
'''
        
    ReplaceStrings(templateDeclareLines, "JsonDeclaration", JsonDeclarationStr)
    ReplaceStrings(templateDeclareLines, "JsonProtectedDeclaration", JsonProtectedDeclarationStr)
    ReplaceStrings(templateImplLines, "JsonImplementation", JsonImplementationStr)

    f = open(declareTxt)#(sys.argv[1])            # Filename on the command line
    declareLines += f.readlines()          # Read all lines into a list , strip all space and \n
    f.seek(0)
    sdkDeclareLines += f.readlines()
    f.close()

    classNameStr = get_class_name(declareLines[0])

    baseClassString = ""
    typeString = ""
    nameString = ""
    defaultValue = ""
    isSdkOnly = False
    isSerializable = True

#list string
    variableListstring = ""
    constructorParameterListString = ""

    defaultInitialListString = ""
    parameterInitListString = ""
    assignmentListString = ""
    methodDeclareString = ""
    methodImplString = ""
    fromJsonString = ""
    toJsonString = ""
    baseClassListString = ":"
    includeListString = ""
    jsonIncludeListStr = ""
    ptrDefListString = "" 
    virtualString = "" 
    includePathPrefix = ""
    fileSubDirname = ""
    newIncludeFile = ""

    constructorWithParameterImplString = ""
    constructorWithParameterDeclareString = ""

    #remove project name in header file include rule
    (projectName, classDir) = FindClassDir(classNameStr)
    if projectName == '' or classDir == '':
        return

    jsonIncludeListStr += '#include "' + projectName + '/util/' + projectName.title() + 'JsonHelper.h"\n'
    jsonIncludeListStr += '#include "' + projectName + '/util/' + projectName.title() + 'ModelUtil.h"\n'
    includePathPrefix = '#include "' + projectName + '/model'
    newIncludeFile =  includePathPrefix  + classDir + '.h"\n'
    if not newIncludeFile in jsonIncludeListStr:
        jsonIncludeListStr += newIncludeFile


    for i in range(1, len(declareLines)):
        lineString = declareLines[i]
        lineString = lineString.lstrip()
        lineString = lineString.rstrip()
        lineString = lineString.rstrip("\n")
        if lineString == "": 
            continue
        splittedStrings = lineString.split()

        commentString = ""
        for i in range(1, len(splittedStrings)):
            if splittedStrings[i].startswith("//") :
                commentString = " ".join(splittedStrings[i:])
                splittedStrings = splittedStrings[:i]
                break;

        # if len(splittedStrings) > 2:
        #     typeString = splittedStrings[0] + " " + splittedStrings[1]
        #     nameString = splittedStrings[2]

        # elif len(splittedStrings) > 1:
        #     typeString = splittedStrings[0]
        #     nameString = splittedStrings[1]
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
            isSerializable = fieldInfo.isSerializable

        ptrDefTempl = '''
    BB_FORWARD_DECLARE(typeString)
'''
  
        if len(splittedStrings) == 1:
            virtualString = "virtual "
            # deal with the derived class
#            if baseClassString != "BASECLASS":

            baseClassListString += " public " + baseClassString + ","
            defaultInitialListString += baseClassString + "()\n    , "
            parameterInitListString += baseClassString + "()\n    , "
            assignmentListString += baseClassString + "::operator=(rhs);\n            "

            fromJsonString += baseClassString + "::FromJson(jsonItems);\n"
            toJsonString += baseClassString + "::ToJsonWithoutObject(writer);\n"

            (projectName, classDir) = FindClassDir(baseClassString)
            if projectName == '' or classDir == '':
                return

            includePathPrefixShared = '#include "' + projectName + '/model'
            newIncludeFile = includePathPrefixShared + classDir + '.h"\n'
            if not newIncludeFile in jsonIncludeListStr:
                jsonIncludeListStr += newIncludeFile


            newIncludeFile = includePathPrefixShared + classDir + '.h"\n'
            if not newIncludeFile in includeListString:
                includeListString += newIncludeFile

        else:
            #type conversion
            if typeString[-4:] == "long":
                typeString = typeString + " long"

            mem_nameString = "m_" + nameString[0].upper() + nameString[1:]
            variableListstring += typeString + " " + mem_nameString + "; " + commentString + "\n        "
            
            methodDeclareBaseTempl = '''
        void SetNameString(typeString nameString);
        typeString GetNameString(void);
'''
            methodImplBaseTempl = '''
    void ClassName::SetNameString(typeString nameString)
    {
        mem_nameString = nameString;
    }

    typeString ClassName::GetNameString(void)
    {
        return mem_nameString;
    }
'''

            methodDeclareObjectTempl = '''
        void SetNameString(const typeString &nameString);
        typeString GetNameString(void);
'''
            methodImplObjectTempl = '''
    void ClassName::SetNameString(const typeString &nameString)
    {
        mem_nameString = nameString;
    }

    typeString ClassName::GetNameString(void)
    {
        return mem_nameString;
    }
'''

            methodImplObjectTempl = str.replace(methodImplObjectTempl, "ClassName", classNameStr)
            methodImplBaseTempl = str.replace(methodImplBaseTempl, "ClassName", classNameStr)

            if defaultValue:
                defaultInitialListString += mem_nameString + "(" + defaultValue + ")\n    , "
            else:    
                if typeString == "bool":
                    defaultInitialListString += mem_nameString + "(false)\n    , "
                elif typeString == "int":
                    defaultInitialListString += mem_nameString + "(INT_MAX)\n    , "
                elif typeString == "long":
                    defaultInitialListString += mem_nameString + "(LONG_MAX)\n    , "
                elif typeString == "long long":
                    defaultInitialListString += mem_nameString + "(LLONG_MAX)\n    , "
                elif typeString == "unsigned int":
                    defaultInitialListString += mem_nameString + "(UINT_MAX)\n    , "
                elif typeString == "unsigned long":
                    defaultInitialListString += mem_nameString + "(ULONG_MAX)\n    , "
                elif typeString == "unsigned long long":
                    defaultInitialListString += mem_nameString + "(ULLONG_MAX)\n    , "
                elif typeString == "float" or typeString == "double": 
                    defaultInitialListString += mem_nameString + "(DBL_MAX)\n    , "
                    if "#include \"float.h\"\n" not in jsonIncludeListStr:
                        jsonIncludeListStr += "#include \"float.h\"\n"

            if typeString=="bool" or typeString=="int" or typeString == "unsigned int" or typeString=="float" or typeString=="double" or typeString=="long" or typeString=="long long" or typeString == "unsigned long" or typeString == "unsigned long long":
                constructorParameterListString += typeString + " " + nameString + ", "

                methodDeclareBaseTempl = str.replace(methodDeclareBaseTempl, "typeString", typeString)
                methodDeclareBaseTempl = str.replace(methodDeclareBaseTempl, "nameString", nameString)
                methodDeclareBaseTempl = str.replace(methodDeclareBaseTempl, "NameString", nameString[0].upper() + nameString[1:])

                methodImplBaseTempl = str.replace(methodImplBaseTempl, "mem_nameString", mem_nameString)
                methodImplBaseTempl = str.replace(methodImplBaseTempl, "typeString", typeString)
                methodImplBaseTempl = str.replace(methodImplBaseTempl, "nameString", nameString)
                methodImplBaseTempl = str.replace(methodImplBaseTempl, "NameString", nameString[0].upper() + nameString[1:])

                methodDeclareString += methodDeclareBaseTempl
                methodImplString += methodImplBaseTempl
            else:
                constructorParameterListString += "const " + typeString + " &" + nameString + ", "
                defaultInitialListString += mem_nameString + "()\n    , "
                
###############################################just for android
                if typeString == "std::vector<std::string>":
                    methodDeclareVecStrTempl = '''
#ifdef ANDROID
        void SetNameString(const std::vector<StringWrapper> &nameString);
        std::vector<StringWrapper> GetNameString(void);
#else
    '''
                    methodImplVecStrTempl = '''
#ifdef ANDROID
    void ClassName::SetNameString(const std::vector<StringWrapper> &nameString)
    {
        mem_nameString = StringWrapper::ConvertToStdVec(nameString);
    }
    
    std::vector<StringWrapper> ClassName::GetNameString(void)
    {
        return StringWrapper::ConvertToWrapVec(mem_nameString);
    }
#else
    '''


                    methodDeclareVecStrTempl = str.replace(methodDeclareVecStrTempl, "nameString", nameString)
                    methodDeclareVecStrTempl = str.replace(methodDeclareVecStrTempl, "NameString", nameString[0].upper() + nameString[1:])
                    
                    methodImplVecStrTempl = str.replace(methodImplVecStrTempl, "ClassName", classNameStr)
                    methodImplVecStrTempl = str.replace(methodImplVecStrTempl, "mem_nameString", mem_nameString)
                    methodImplVecStrTempl = str.replace(methodImplVecStrTempl, "nameString", nameString)
                    methodImplVecStrTempl = str.replace(methodImplVecStrTempl, "NameString", nameString[0].upper() + nameString[1:])
                    
                    methodDeclareString += methodDeclareVecStrTempl
                    methodImplString += methodImplVecStrTempl

                    newIncludeFile = '#include "core/util/StringWrapper.h"'
                    if not newIncludeFile in includeListString:
                        includeListString += newIncludeFile

###############################################

                methodDeclareObjectTempl = str.replace(methodDeclareObjectTempl, "typeString", typeString)
                methodDeclareObjectTempl = str.replace(methodDeclareObjectTempl, "nameString", nameString)
                methodDeclareObjectTempl = str.replace(methodDeclareObjectTempl, "NameString", nameString[0].upper() + nameString[1:])

                methodImplObjectTempl = str.replace(methodImplObjectTempl, "mem_nameString", mem_nameString)
                methodImplObjectTempl = str.replace(methodImplObjectTempl, "typeString", typeString)
                methodImplObjectTempl = str.replace(methodImplObjectTempl, "nameString", nameString)
                methodImplObjectTempl = str.replace(methodImplObjectTempl, "NameString", nameString[0].upper() + nameString[1:])

                methodDeclareString += methodDeclareObjectTempl
                methodImplString += methodImplObjectTempl

###############################################just for android
                if typeString == "std::vector<std::string>":
                    methodDeclareString += "#endif\n"
                    methodImplString += "#endif\n"

###############################################

            if typeString[-4:] == "VPtr":
                (projectName, classDir) = FindClassDir(typeString[:-4])
                newIncludeFile = '#include "' + projectName + '/model' + classDir + '.h"\n'
                if not newIncludeFile in jsonIncludeListStr:
                    jsonIncludeListStr += newIncludeFile

                ptrDefTempl = str.replace(ptrDefTempl, "typeString", typeString[:-4])
                if not ptrDefTempl in ptrDefListString:
                    ptrDefListString += ptrDefTempl
            elif typeString[-3:] == "Ptr":
                (projectName, classDir) = FindClassDir(typeString[:-3])
                newIncludeFile = '#include "' + projectName + '/model' + classDir + '.h"\n'
                if not newIncludeFile in jsonIncludeListStr:
                    jsonIncludeListStr += newIncludeFile

                ptrDefTempl = str.replace(ptrDefTempl, "typeString", typeString[:-3])
                if not ptrDefTempl in ptrDefListString:
                    ptrDefListString += ptrDefTempl

            parameterInitListString += mem_nameString + "(" + nameString + ")\n    , "
            assignmentListString += mem_nameString + " = rhs." + mem_nameString + "; \n            "

    # json
            # if nameString[:5] == "local":
            #     continue

            if lineString in sdkDeclareLines:
                continue
            # skip serialize & deserialize wrapper only fields
            if not isSerializable:
                continue

# fromJson
            jsonTemplBaseStr = '''
            JsonHelper::FromJson(mem_nameString, jsonItems, "nameString");'''

            jsonTemplBaseStr = str.replace(jsonTemplBaseStr, "mem_nameString", mem_nameString);
            jsonTemplBaseStr = str.replace(jsonTemplBaseStr, "nameString", nameString);
            fromJsonString += jsonTemplBaseStr

########### continue in json. watch out ##############

#toJson
            toJsonTemplBaseStr = '''
        JsonHelper::ToJson(this, mem_nameString, writer, "nameString", toJsonCtrl);'''
            toJsonTemplBaseStr = str.replace(toJsonTemplBaseStr, "mem_nameString", mem_nameString);
            toJsonTemplBaseStr = str.replace(toJsonTemplBaseStr, "nameString", nameString);
            toJsonString += toJsonTemplBaseStr

                ############

    variableListstring = variableListstring.rstrip(" \n        ")
    constructorParameterListString = constructorParameterListString.rstrip(", ")
            
    defaultInitialListString = defaultInitialListString.rstrip("\n    , ")
    parameterInitListString = parameterInitListString.rstrip("\n     , ")
    assignmentListString = assignmentListString.rstrip(" \n        ")


    if variableListstring != "":
        constructorWithParameterDeclareString = "        ClassName(ConstructorParameterList);"
        constructorWithParameterDeclareString = str.replace(constructorWithParameterDeclareString, "ClassName", classNameStr)
        constructorWithParameterDeclareString = str.replace(constructorWithParameterDeclareString, "ConstructorParameterList", constructorParameterListString)

        constructorWithParameterImplString = '''
    ClassName::ClassName(ConstructorParameterList)
    : ParameterInitializationList
    {

    }
'''
        constructorWithParameterImplString = str.replace(constructorWithParameterImplString, "ClassName", classNameStr)
        constructorWithParameterImplString = str.replace(constructorWithParameterImplString, "ConstructorParameterList", constructorParameterListString)
        constructorWithParameterImplString = str.replace(constructorWithParameterImplString, "ParameterInitializationList", parameterInitListString)


    #ReplaceStrings(templateDeclareLines, "Yi Zheng", get_username())
    ReplaceStrings(templateDeclareLines, "ClassName", get_class_name(declareLines[0]))
    ReplaceStrings(templateDeclareLines, "VirtualDeclare ", virtualString)

    ReplaceStrings(templateDeclareLines, "IncludeList", includeListString)
    ReplaceStrings(templateDeclareLines, "PtrDefList", ptrDefListString)
    
    ReplaceStrings(templateDeclareLines, "VariableList", variableListstring)
    ReplaceStrings(templateDeclareLines, "DefaultInitializationList", "    : " + defaultInitialListString)
    ReplaceStrings(templateDeclareLines, "ConstructorWithParameterDeclare", constructorWithParameterDeclareString)
    ReplaceStrings(templateDeclareLines, "ParameterInitializationList", parameterInitListString)
    ReplaceStrings(templateDeclareLines, "AssignmentList", assignmentListString)
    ReplaceStrings(templateDeclareLines, "MethodDeclaration", methodDeclareString)
    ReplaceStrings(templateDeclareLines, "MethodImpl", methodImplString)
    if baseClassListString != ":":
        baseClassListString = baseClassListString.rstrip(",")
    else:
        baseClassListString = ""

    ReplaceStrings(templateDeclareLines, "BaseClassList", baseClassListString)

    #ReplaceStrings(templateImplLines, "Yi Zheng", get_username())
    ReplaceStrings(templateImplLines, "ClassName", classNameStr)
    ReplaceStrings(templateImplLines, "JsonIncludeList", '\n'.join(sorted(jsonIncludeListStr.split('\n'))))

    ReplaceStrings(templateImplLines, "VariableList", variableListstring)
    if defaultInitialListString != "":
        defaultInitialListString = ": " + defaultInitialListString
        
    ReplaceStrings(templateImplLines, "DefaultInitializationList", defaultInitialListString)
    ReplaceStrings(templateImplLines, "ConstructorParameterList", constructorParameterListString)
    ReplaceStrings(templateImplLines, "ConstructorWithParameterImpl", constructorWithParameterImplString)
    ReplaceStrings(templateImplLines, "AssignmentList", assignmentListString)
    ReplaceStrings(templateImplLines, "MethodDeclaration", methodDeclareString)
    ReplaceStrings(templateImplLines, "MethodImpl", methodImplString)
    ReplaceStrings(templateImplLines, "FromJsonStrList", fromJsonString)
    ReplaceStrings(templateImplLines, "ToJsonStrList", toJsonString)

    incPath = str.replace(os.path.dirname(declareTxt), "-txt", "-gen/inc")
    if not os.path.exists(incPath):
        os.makedirs(incPath)

    f = open(incPath + "/" + classNameStr + ".h","w+")     # Open file for writing
    for s in templateDeclareLines:
        f.write(s)
    f.close()

    srcPath = str.replace(os.path.dirname(declareTxt), "-txt", "-gen/src")
    if not os.path.exists(srcPath):
        os.makedirs(srcPath)

    f = open(srcPath + "/" + classNameStr + ".cpp","w+")     # Open file for writing
    for s in templateImplLines:
        f.write(s)
    f.close()

    print "done sdk layer generate for " + srcPath + "/" + classNameStr + '.cpp'

def VisitDir(path):
    for root,Dirs,files in os.walk(path):
        for file in files:
            print file
            if '.' in file and 'sdk-txt' in root:
                if file.rsplit('.',1)[1]=="txt":
                    CodeGenerate(os.path.join(root, file))

def CopyNoExistFile(path):
    for root,Dirs,files in os.walk(path):
        for file in files:
            if '.' in file and 'server-txt' in root:
                if file.rsplit('.',1)[1]=="txt":
                    txtPath = str.replace(root, "server-txt", "sdk-txt")
                    if not os.path.exists(txtPath):
                        os.makedirs(txtPath)
                    txtSDKfilename = os.path.join(txtPath, file)
                    if not os.path.exists(txtSDKfilename):
                        f = open(txtSDKfilename,"w+")     # Open file for writing
                        f.close()


def copyDirFiles(fromPath, toPath, filetype):
    for root,Dirs,files in os.walk(fromPath):
        for file in files:

            if '.' in file:
                if file.rsplit('.',1)[1]==filetype and file[0] != '.':
                    #move files
                    fullfilename = os.path.join(root, file)

                    newfilename = str.replace(fullfilename, fromPath, toPath)
                                        
                    if not os.path.exists(os.path.dirname(newfilename)):
                        os.makedirs(os.path.dirname(newfilename))
                    shutil.copyfile(fullfilename,newfilename)

if __name__=="__main__":
    # if os.path.exists(os.path.join(os.getcwd(), "server-txt/")):
    #     shutil.rmtree(os.path.join(os.getcwd(), "server-txt/"))
    # copyDirFiles("/Users/jason/workview/mbaas-server/bin/sdk_out", os.path.join(os.getcwd(), "server-txt"), "txt")

    CopyNoExistFile(os.path.join(os.getcwd(), "server-txt"))
    VisitDir(os.getcwd())
    #print '''##### the base class pointer (inherited object) json should not be replace directly '''


