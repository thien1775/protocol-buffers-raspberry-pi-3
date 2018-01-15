all:
	protoc --cpp_out=. Employee.proto
	c++ client.cc  Employee.pb.cc -o client `pkg-config --cflags --libs protobuf`
	c++ server.cc  Employee.pb.cc -o server `pkg-config --cflags --libs protobuf`
#	protoc --cpp_out=. Employee.proto
#	g++ -g -Wall server.cc Employee.pb.cc -o server -lprotobuf
#	g++ -g -Wall client.cc Employee.pb.cc -o client -lprotobuf 


clean:
	rm server client Employee.pb.cc Employee.pb.h

