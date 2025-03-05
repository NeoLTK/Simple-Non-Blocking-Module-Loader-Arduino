#!/bin/bash
date=$(date +'%y%m%d');
build=36;#build
next_b=$[$build+1]

sed -i "/#build$/s/=.*#/=$next_b;#/" ${0}

sed -i '/VERSION/c\#define VERSION '${date} /home/sscssc/HybrideBox/src/core/version.h
sed -i '/BUILD/c\#define BUILD '${build} /home/sscssc/HybrideBox/src/core/version.h
arduino-cli compile --fqbn arduino:avr:nano:cpu=atmega328old /home/sscssc/HybrideBox/HybrideBox.ino --quiet

echo "Upload en cours..."
arduino-cli upload /home/sscssc/HybrideBox/HybrideBox.ino -p /dev/ttyUSB0 --fqbn arduino:avr:nano:cpu=atmega328old 
