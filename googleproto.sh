#!/bin/sh -e
sudo apt-get update -y
sudo apt-get upgrade -y
git clone https://github.com/google/protobuf.git
cd protobuf
sudo apt-get install autoconf automake libtool curl make g++ unzip
./autogen.sh 
./configure 
make -j2
make check -j2
sudo make install -j2
sudo ldconfig

