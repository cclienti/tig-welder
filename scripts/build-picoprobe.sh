#!/bin/bash
#
# This file is part of the tig-welder project
# (https://github.com/cclienti/tig-welder)
# Copyright (c) 2021 Christophe Clienti
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, version 3.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.

set -e

CPU_COUNT=$(cat /proc/cpuinfo | grep processor | wc -l)
OPENODCD_INSTALL_DIR=${HOME}/rpi-openocd

#############################################
# Build picoprobe firmware
#############################################
git clone https://github.com/raspberrypi/picoprobe.git
mkdir picoprobe/build
pushd picoprobe/build
cmake -DPICO_SDK_FETCH_FROM_GIT=1 ..
make -j${CPU_COUNT}
popd

#############################################
# Build the rpi openocd
#############################################
git clone --branch picoprobe https://github.com/raspberrypi/openocd.git rpi-openocd
pushd rpi-openocd
git submodule init
git submodule update
./bootstrap
./configure --prefix=${HOME}/rpi-openocd
make -j${CPU_COUNT}
make install
popd

#############################################
# Add a startup script
#############################################
mkdir -p ${OPENODCD_INSTALL_DIR}/bin

cat <<EOF >${OPENODCD_INSTALL_DIR}/bin/pico-openocd.sh
#!/bin/bash
${OPENODCD_INSTALL_DIR}/bin/openocd \
        -f ${HOME}/rpi-openocd/share/openocd/scripts/interface/picoprobe.cfg \
        -f ${HOME}/rpi-openocd/share/openocd/scripts/target/rp2040.cfg \
        $*
EOF
chmod u+x ${OPENODCD_INSTALL_DIR}/bin/pico-openocd.sh
echo "You can start openocd by launching the command: ${OPENODCD_INSTALL_DIR}/bin/pico-openocd.sh"
echo "Warning:"
echo "Examine rpi-openocd/contrib/60-openocd.rules to add the picoprobe usb vendor_id/product_id and copy the file to /etc/udev/rules.d/"
echo "Then reboot or reload udev rules with the command 'sudo udevadm control --reload-rules && udevadm trigger'"
echo "Proposed patch:"
echo "# Picoprobe"
echo 'ATTRS{idVendor}=="2e8a", ATTRS{idProduct}=="0004", MODE="660", GROUP="plugdev", TAG+="uaccess"'
