# -*- coding: cp936 -*-

import sys                       # Load the sys module
import string
import os, shutil

whiteList = [

             "Emphasis",
             "EmphasisProtocol",
             "EmphasisResponse",
             "CourseSection"
]

def removeDirFiles(fromPath, toPath, filetype):
    print fromPath
    print toPath
    #print path
    for root,Dirs,files in os.walk(toPath):
        for file in files:
            #print file
            if '.' in file:
                print ':' + file.rsplit('.', 1)[0] 
                print 'BBM'+file.rsplit('.', 1)[0]
                if file.rsplit('.',1)[1]==filetype and (file.rsplit('.', 1)[0] in whiteList or file.rsplit('.', 1)[0][3:] in whiteList):
                    #move files
                    fullfilename = os.path.join(root, file)

                    print fullfilename
                    print 'removed!'

                    os.remove(fullfilename)

if __name__=="__main__":
    iosSDK_IncFrom = os.path.join(os.getcwd(), 'sdk-gen/wrapinc')
    iosSDK_SrcFrom = os.path.join(os.getcwd(), 'sdk-gen/wrapsrc')

    # iosSDK_IncTo = os.path.join(os.getcwd(), 'sdk-gento/wrapinc')
    # iosSDK_SrcTo = os.path.join(os.getcwd(), 'sdk-gento/wrapsrc')
    
    iosSDK_IncTo = os.path.join('', '../../BlackboardMobile/include/ios/deviceapis/models')
    iosSDK_SrcTo = os.path.join('', '../../BlackboardMobile/iOS/deviceapis/models')

    removeDirFiles(iosSDK_IncFrom, iosSDK_IncTo, "h")
    removeDirFiles(iosSDK_SrcFrom, iosSDK_SrcTo, "mm")

    #############################################

    modelSDK_IncFrom = os.path.join(os.getcwd(), 'sdk-gen/inc')
    modelSDK_SrcFrom = os.path.join(os.getcwd(), 'sdk-gen/src')

    # modelSDK_IncTo = os.path.join(os.getcwd(), 'sdk-gento/inc')
    # modelSDK_SrcTo = os.path.join(os.getcwd(), 'sdk-gento/src')

    modelSDK_IncTo = os.path.join('', '../../BlackboardMobile/include/deviceapis/models')
    modelSDK_SrcTo = os.path.join('', '../../BlackboardMobile/deviceapis/models')

    removeDirFiles(modelSDK_IncFrom, modelSDK_IncTo, "h")
    removeDirFiles(modelSDK_SrcFrom, modelSDK_SrcTo, "cpp")
