import re

class FieldInfo:
    type = None
    name = None
    defaultVal = None
    isSdkOnly = False
    isSerializable = True
    comment = None

# regex pattern that matchs line with format "type name #default=defaultvalue #sdkonly=true #serializable=false //comment"
pattern = "(?P<type>(\w|[<:>])*) (?P<name>\w*)((.*)//(?P<comment>.*))?"
tagDefault = "#default=(\w*)"
tagSdkOnly = "#sdkonly=(\w*)"
tagSerializable = "#serializable=(\w*)"

def extractTag(tag_pattern, str):
    tags  = re.search(tag_pattern, str, re.IGNORECASE)
    if tags:
        return tags.group(1)
    else:
        return None

def parseFieldInfo(str):
    match = re.search(pattern, str)
    type = match.group('type')
    name = match.group('name')

    if (not type or not name):
        return None

    fieldInfo = FieldInfo()
    fieldInfo.type = type
    fieldInfo.name = name
    fieldInfo.comment = match.group('comment')

    fieldInfo.defaultVal = extractTag(tagDefault, str)

    strSdkOnly = extractTag(tagSdkOnly, str)
    if strSdkOnly and strSdkOnly.lower() == 'true':
        fieldInfo.isSdkOnly = True

    strSerializable = extractTag(tagSerializable, str)
    if strSerializable and strSerializable.lower() == 'false':
        fieldInfo.isSerializable = False
    
    return fieldInfo