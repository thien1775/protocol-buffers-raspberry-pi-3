#!/bin/sh -e
sudo apt-get update -y
sudo apt-get upgrade -y
git clone https://git.com/google/protobuf.git
cd protobuf
sudo apt-get install autoconf suto make libtool curl make g++ unzip
./autogen.sh 
./configure 
sudo make -j2
sudo make -j2
sudo make install -j2
sudo ldconfig

