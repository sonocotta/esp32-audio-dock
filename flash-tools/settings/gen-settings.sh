#!/bin/bash

GREEN='\033[0;32m'
NC='\033[0m' # No Color

if [ -d "$HOME/storage/sdk/esp-idf-5" ]
then
    if [[ -z "$IDF_PATH" ]]; then
    	export IDF_PATH=$HOME/storage/sdk/esp-idf-5 
    	. $IDF_PATH/export.sh
    fi

    NVS_GEN=$IDF_PATH/components/nvs_flash/nvs_partition_generator/nvs_partition_gen.py

    for file in ./*.csv; do
        echo -e "${GREEN}Generating $file -> ../firmware/${file%.csv}.bin${NC}"
        $NVS_GEN generate "$file" "../firmware/${file%.csv}.bin" 65536
    done
	
else
    echo "Error: Directory storage/sdk/esp-idf-5 does not exists."
fi