# -*- coding: cp936 -*-

import sys                       # Load the sys module (导入sys模块)
import string
import os

def VisitDir(path):
    print path
    for root,Dirs,files in os.walk(path):
        for file in files:
            print file
            if 'BBM_' in file:
                os.remove(os.path.join(root, file))


if __name__=="__main__":
    VisitDir(os.getcwd())


