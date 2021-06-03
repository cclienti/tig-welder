#!/bin/bash

set -e

# Default Values
TTY_DEVICE=/dev/ttyACM0
BAUD_RATE=115200
FLASH_RATE=1200

if [ -d /run/media ]
then
    MOUNT_POINT=/run/media/${USER}/RPI-RP2
else
    MOUNT_POINT=/media/${USER}/RPI-RP2
fi

usage () {
    echo -e "usage: $(basename $0) [OPTIONS] {UF2 File}"
    echo -e "\nOptions:"
    echo -e "\t-h\tshow help"
    echo -e "\t-d\ttty device (default: ${TTY_DEVICE})"
    echo -e "\t-m\tmount point (default: ${MOUNT_POINT})"
    echo -e "\t-r\tscreen baud rate (default: ${BAUD_RATE})"
}

# Parse optional args
while getopts "hd:m:r:" opt
do
    case "${opt}" in
        h)
            usage
            exit 0
            ;;
        d)
            TTY_DEVICE=$OPTARG
            ;;
        m)
            MOUNT_POINT=$OPTARG
            ;;
        r)
            BAUD_RATE=$OPTARG
            ;;
    esac
done

# Parse positional arg
UF2_FILE=${@:$OPTIND:1}
if [ "${UF2_FILE}" = "" ]
then
    echo -e "Missing file to flash"
    usage
    exit 1
fi
if [ ! -e ${UF2_FILE} ]
then
    echo -e "file '${UF2_FILE}' not found"
    exit 1
fi

# Print variables
echo "TTY device: ${TTY_DEVICE}"
echo "Mount point: ${MOUNT_POINT}"
echo "Screen baud rate: ${BAUD_RATE}"
echo "UF2 file: ${UF2_FILE}"

# Switch device in flash mode if needed
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

# Copy the UF2 file
echo -e "Copying ${UF2_FILE} to ${MOUNT_POINT}"
cp ${UF2_FILE} ${MOUNT_POINT}
while [ ! -e ${TTY_DEVICE} ]; do sleep 0.1; done
sleep 0.5
echo -e "Done"

# Start screen
echo "Starting screen (to quit: Ctrl-a, k, y)"
read -n 1 -r -s -p $'Press enter to continue...\n'
screen ${TTY_DEVICE} ${BAUD_RATE}
