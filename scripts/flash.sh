#!/bin/bash

set -e

TTY_DEVICE=/dev/ttyACM0
FLASH_RATE=1200
BAUD_RATE=115200
MOUNT_POINT=/run/media/${USER}/RPI-RP2

if [ "$*" = "" ]
then
    echo -e "Missing file to flash"
    exit 1
fi

if [ ! -d ${MOUNT_POINT} ]
then
    echo -e "Switching device to flash mode"
    if [ ! -e ${TTY_DEVICE} ]; then
        echo -e "Cannot find ${TTY_DEVICE}"
        exit 1
    fi
    stty -F ${TTY_DEVICE} ${FLASH_RATE}
    echo -e "Waiting..."
    while [ ! -d ${MOUNT_POINT} ]; do sleep 0.1; done
    sleep 0.5
else
    echo -e "Device already in flash mode"
fi

echo -e "Copying $1 to ${MOUNT_POINT}"
cp $1 ${MOUNT_POINT} &
while [ ! -e ${TTY_DEVICE} ]; do sleep 0.1; done
sleep 0.5
echo -e "Done"

echo "Starting screen (to quit: Ctrl-a, k, y)"
read -n 1 -r -s -p $'Press enter to continue...\n'
screen ${TTY_DEVICE} ${BAUD_RATE}
