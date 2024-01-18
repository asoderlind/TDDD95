#! /bin/bash

# This script is used to run the test cases for the project
FOLDER="spiderman"

# Check if the folder exists
if [ ! -d "$FOLDER" ]; then
    echo "Folder $FOLDER does not exist"
    exit 1
fi

# Check if the folder is empty
if [ -z "$(ls -A $FOLDER)" ]; then
    echo "Folder $FOLDER is empty"
    exit 1
fi

# Check if the folder contains the required files
if [ ! -f "$FOLDER/main.py" ]; then
    echo "File $FOLDER/main.py does not exist"
    exit 1
fi

# run the main file
python3 $FOLDER/main.py < $FOLDER/data/sample1.in > $FOLDER/data/sample1.run

# compare the output
diff $FOLDER/data/sample1.out $FOLDER/data/sample1.run > $FOLDER/data/sample1.diff