#! /bin/bash

# time grep -l "world" ./test_files/*

set -euo pipefail

OUTPUT_DIR="./test_files"
WORDS_PER_FILE=1000
FILES_COUNT=1000
OUTPUT_CONFIG_FILE="config.json"
OUTPUT_REQUEST_FILE="request.json"
REQUEST_COUNT=1000
WORDS_PER_REQUEST=3

trap_error() {
    local exit_code=$?
    local line_no=${BASH_LINENO[0]}
    local cmd="${BASH_COMMAND}"
    echo "ERROR $line_no: $cmd"
    echo "RC: $exit_code"
    exit $exit_code
}
trap trap_error ERR

get_random_words() {
    words_count=$1
    # echo -n "random word"
    # curl -s https://random-word-api.herokuapp.com/word?number=${words_count}&length=10
    grep -E "^\w{10}$" /usr/share/dict/words \
          | head -n 1000 \
          | shuf -rn $words_count \
          | tr '\n' ' ' || true
}

rm -rf "${OUTPUT_DIR}" "${OUTPUT_CONFIG_FILE}" "${OUTPUT_REQUEST_FILE}"
mkdir -p "${OUTPUT_DIR}"
for ((i=0; i < FILES_COUNT; i++)); do
    file_name="${OUTPUT_DIR}/file$(printf "%03d" "$i").txt"
    echo "Create file: $file_name"
    touch "${file_name}"
    (get_random_words $WORDS_PER_FILE) > "${file_name}"
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

echo '{'                                   > "${OUTPUT_REQUEST_FILE}"
echo '    "requests": ['                   >> "${OUTPUT_REQUEST_FILE}"
for ((i=1; i <= REQUEST_COUNT; i++)); do
    echo -e "Create request: $i/$REQUEST_COUNT"
    echo -n '        "' >> "${OUTPUT_REQUEST_FILE}"
    (get_random_words $WORDS_PER_REQUEST) \
        | sed -e 's/\["\|"\]\|","/ /g' >> "${OUTPUT_REQUEST_FILE}"
    echo -n '"' >> "${OUTPUT_REQUEST_FILE}"
    if ((i < REQUEST_COUNT)); then
        echo "," >> "${OUTPUT_REQUEST_FILE}"
    else
        echo "" >> "${OUTPUT_REQUEST_FILE}"
    fi
done
echo '    ]'                               >> "${OUTPUT_REQUEST_FILE}"
echo '}'                                   >> "${OUTPUT_REQUEST_FILE}"

echo "Done!!!"
