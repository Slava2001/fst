#! /bin/bash

# time grep -l "world" ./test_files/*

set -e

OUTPUT_DIR="./test_files"
WORDS_PER_FILE=1000
FILES_COUNT=1000
OUTPUT_CONFIG_FILE="config.json"

mkdir -p "${OUTPUT_DIR}"

for ((i=0; i < FILES_COUNT; i++)); do
    file_name="${OUTPUT_DIR}/file$(printf "%03d" "$i").txt"
    echo "Create file: $file_name"
    touch "${file_name}"
    curl -s https://random-word-api.herokuapp.com/word?number=${WORDS_PER_FILE} > "${file_name}"
done

echo '{'                                   > "${OUTPUT_CONFIG_FILE}"
echo '    "config": {'                     >> "${OUTPUT_CONFIG_FILE}"
echo '        "name": "fst",'              >> "${OUTPUT_CONFIG_FILE}"
echo '        "version": "0.0.1",'         >> "${OUTPUT_CONFIG_FILE}"
echo '        "max_responses": 5'          >> "${OUTPUT_CONFIG_FILE}"
echo '    },'                              >> "${OUTPUT_CONFIG_FILE}"
echo '    "files": ['                      >> "${OUTPUT_CONFIG_FILE}"
for ((i=0; i < FILES_COUNT; i++)); do
    file_name="${OUTPUT_DIR}/file$(printf "%03d" "$i").txt"
    echo -n '        "'"${file_name}"'"' >> "${OUTPUT_CONFIG_FILE}"
    if ((i < FILES_COUNT - 1)); then
        echo "," >> "${OUTPUT_CONFIG_FILE}"
    else
        echo "" >> "${OUTPUT_CONFIG_FILE}"
    fi
done
echo '    ]'                               >> "${OUTPUT_CONFIG_FILE}"
echo '}'                                   >> "${OUTPUT_CONFIG_FILE}"
