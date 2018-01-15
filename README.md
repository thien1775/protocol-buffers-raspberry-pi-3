# protobuffer_demo
Client and Server socket communication using google protocol buffer (shows how to serialize and deserialize data)

1. Download protocol buffer. Protocol buffer libs can be downloaded here. https://github.com/google/protobuf

2. Check if g++ compiler is installed on box. Protocol buffer needs g++ compiler to be present on your box before it can be builded. This is a crisp post on how to install g++ compiler on your box. Install g++ compiler.

3. Extract the protocol buffer archive and switch to the extracted directory.

4. Inside the extracted directory hit the below commands to install protocol buffer. These may take a while, kindly be patient.

$ sudo ./configure
$ sudo make
$ sudo make check
$ sudo make install
$ protoc --version

5. Thats it. Protocol buffer version 2.5.0 is installed on your box.

6. Note: Sometimes the latest version of protocol version does not load up. So we can do it manually by this command

$ sudo ldconfig
$ protoc --version
----------------------------------------------------------------------------------------------------------------------------------
HOW TO USE:                   
$ make all            
$ Run the server first : ./server $portno                     
$ Run the Client:        ./client localhost $portno
