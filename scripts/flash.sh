#!/bin/bash
set -e

TTY_DEVICE=/dev/ttyACM0
MOUNT_POINT=/run/media/${USER}/RPI-RP2

if [ "$*" = "" ]; then
    echo "Missing file to flash"
    exit 1
fi

stty -F ${TTY_DEVICE} 1200
echo waiting
while [ ! -d ${MOUNT_POINT} ]; do sleep 0.1; done
sleep 0.5
echo copying
cp $1 ${MOUNT_POINT}
while [ ! -e ${TTY_DEVICE} ]; do sleep 0.1; done
echo done
