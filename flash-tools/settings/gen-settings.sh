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
        name=$(basename "$file" .csv)
        # common-esp-nvs.csv targets the shared "nvs" partition (0x9000, size
        # 0x4000); every other file here targets the per-device "settings"
        # partition (size 0x10000). Sizes must match partitions.csv.
        if [ "$name" == "common-esp-nvs" ]; then
            size=16384
        else
            size=65536
        fi
        echo -e "${GREEN}Generating $file -> ../firmware/${name}.bin (size $size)${NC}"
        $NVS_GEN generate "$file" "../firmware/${name}.bin" $size
    done
	
else
    echo "Error: Directory storage/sdk/esp-idf-5 does not exists."
fi