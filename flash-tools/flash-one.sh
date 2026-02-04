#!/bin/bash

GREEN='\033[0;32m'
NC='\033[0m' # No Color

SET_BAUDRATE='-b 921600'
CONFIG=${2:-hifi-esp}

if [[ ! -z $1 ]] ; then
	DEVICE="--port $1"
else
	DEVICE=""
fi

echo -e "${GREEN} Using $CONFIG config ${NC}"
echo -e "${GREEN} Using $DEVICE port ${NC}"

if [ -d "$HOME/storage/sdk/esp-idf-4.4.7" ]
then
    if [[ -z "$IDF_PATH" ]]; then
    	export IDF_PATH=$HOME/storage/sdk/esp-idf-4.4.7
    	. $IDF_PATH/export.sh
    fi

	echo -e "${GREEN} Flashing firmware ${NC}"

	if [[ "$CONFIG" == *s3 ]]
	then
		esptool.py $SET_BAUDRATE $DEVICE --chip esp32s3 --before=default_reset --after=hard_reset write_flash -z \
		0x0000   firmware/common-esp32s3-2.1681-16-bootloader.bin \
		0x8000   firmware/common-esp32s3-2.1681-16-partition-table.bin \
		0x9000   firmware/common-esp-nvs.bin \
		0xd000   firmware/common-esp32s3-2.1681-16-ota_data_initial.bin \
		0x10000  firmware/common-esp32s3-2.1681-16-recovery.bin \
		0x150000 firmware/common-esp32s3-2.1681-16-squeezelite.bin \
		0x3f0000 firmware/$CONFIG-settings.bin
	else
		esptool.py $SET_BAUDRATE $DEVICE --chip esp32 --before=default_reset --after=hard_reset write_flash -z \
		0x1000   firmware/common-esp-2.1681-16-bootloader.bin \
		0x8000   firmware/common-esp-2.1681-16-partition-table.bin \
		0x9000   firmware/common-esp-nvs.bin \
		0xd000   firmware/common-esp-2.1681-16-ota_data_initial.bin \
		0x10000  firmware/common-esp-2.1681-16-recovery.bin \
		0x150000 firmware/common-esp-2.1681-16-squeezelite.bin \
		0x3f0000 firmware/$CONFIG-settings.bin
	fi
	
else
    echo "Error: Directory storage/sdk/esp-idf-5 does not exists."
fi