#i/bin/bash

rm -r sdk-gen
python3 codeGeneratorPojoJson.py
#python codeGeneratorPojoWrapper.py
python3 copy_files.py

rm -r sdk-txt