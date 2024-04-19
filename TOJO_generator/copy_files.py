# -*- coding: cp936 -*-

import os
import shutil
import re
import config


blackList = '''
'''
blackListProtocolWrapper = "BBM.+Protocol\..+"

# see config.white_list, do not modify this file just for white list change
whiteList = config.white_list
project_list = config.project_list

def copyDirFiles(fromPath, toPath, filetype):
    print fromPath
    print toPath
    #print path
    for root,Dirs,files in os.walk(fromPath):
        for file in files:
            #print file
            if '.' in file and not re.search(blackListProtocolWrapper, file):
                print ':' + file.rsplit('.', 1)[0] 
                print 'BBM'+file.rsplit('.', 1)[0]
                if file.rsplit('.',1)[1]==filetype and (file.rsplit('.', 1)[0] in whiteList or file.rsplit('.', 1)[0][3:] in whiteList):
                    #move files
                    fullfilename = os.path.join(root, file)

                    newfilename = str.replace(fullfilename, fromPath, toPath)
                                        
                    if not os.path.exists(os.path.dirname(newfilename)):
                        print os.path.dirname(newfilename)
                        os.makedirs(os.path.dirname(newfilename))

                    print newfilename
                    shutil.copyfile(fullfilename,newfilename)

def copyFilesByProject(projectName):

    iosSDK_IncFrom = os.path.join(os.getcwd(), 'sdk-gen/wrapinc/', projectName)
    iosSDK_SrcFrom = os.path.join(os.getcwd(), 'sdk-gen/wrapsrc/', projectName)

    iosSDK_IncTo = os.path.join(os.getcwd(), '../../VsboardMobile/wrapper/iOS/inc/', projectName, 'model')
    iosSDK_SrcTo = os.path.join(os.getcwd(), '../../VsboardMobile/wrapper/iOS/src/', projectName, 'model')

    copyDirFiles(iosSDK_IncFrom, iosSDK_IncTo, "h")
    copyDirFiles(iosSDK_SrcFrom, iosSDK_SrcTo, "mm")

    #############################################

    modelSDK_IncFrom = os.path.join(os.getcwd(), 'sdk-gen/inc/', projectName)
    modelSDK_SrcFrom = os.path.join(os.getcwd(), 'sdk-gen/src/', projectName)

    modelSDK_IncTo = os.path.join(os.getcwd(), '../../VsboardMobile/include/', projectName, 'model')
    modelSDK_SrcTo = os.path.join(os.getcwd(), '../../VsboardMobile/', projectName, 'model')

    copyDirFiles(modelSDK_IncFrom, modelSDK_IncTo, "h")
    copyDirFiles(modelSDK_SrcFrom, modelSDK_SrcTo, "cpp")

if __name__=="__main__":
    for project_name in project_list:
        copyFilesByProject(project_name)
