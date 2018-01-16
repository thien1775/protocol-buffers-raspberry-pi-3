/* Server Program to handle TCP connections */

#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <stdio.h>
#include <iostream>

#include "Hand.pb.h"
const int max_data_size = 4096;

using std::cout;
using std::endl;
using std::cerr;


void error(const char *msg){

    perror(msg);
    exit(0);
}


int main(void){
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    printf("Server start  \n");
    int sock, length, n;
    socklen_t fromlen;
    int port = 1024;
    struct sockaddr_in server;
    struct sockaddr_in client;
    char buf[max_data_size];
    
    sock=socket(AF_INET, SOCK_DGRAM, 0);
       if (sock < 0) error("Opening socket");
    length = sizeof(server);
    bzero(&server,length);
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=htons(port);
    if (bind(sock,(struct sockaddr *)&server,length)<0) 
       error("binding");
    fromlen = sizeof(struct sockaddr_in);
    
    //this is the hello test to see if you can send data correctly
    n = recvfrom(sock,buf,max_data_size,0,(struct sockaddr *)&client,&fromlen);
    if (n < 0) error("recvfrom");
    write(1,buf,n);
    // google proto
    printf("trying to read   %d \n", strlen(buf));
    
    n = recvfrom(sock,buf,max_data_size,0,(struct sockaddr *)&client,&fromlen);
    //n = read(sock,buf,max_data_size-1);
    if (n < 0) error("recvfrom");
    printf("receive message  \n");
    /*std::string mystr;
    mystr.assign(buf, strlen(buf));
    printf("input string = %s\n", mystr);
    */
    std::string a = buf;
    demo::Hand message;
    message.ParseFromString(a);
    //const  demo::Hand::flex_resistor::
    /*
    cout << "Resistor value:\t" << message.flex_resistor1() << endl;
    cout << "Resistor value:\t" << message.flex_resistor2() << endl;
    cout << "Resistor value:\t" << message.flex_resistor3() << endl;
    cout << "Resistor value:\t" << message.flex_resistor4() << endl;
    cout << "Resistor value:\t" << message.flex_resistor5() << endl;
    */
    printf("Flex values\n");
    printf("1 = %f\n", message.flex_resistor(0));
    printf("2 = %f\n", message.flex_resistor(1));
    printf("3 = %f\n", message.flex_resistor(2));
    printf("4 = %f\n", message.flex_resistor(3));
    printf("5 = %f\n", message.flex_resistor(4));
    /*
    float fResistor [5] = {message.flex_resistor(0),
                           message.flex_resistor(1),
                           message.flex_resistor(2),
                           message.flex_resistor(3),
                           message.flex_resistor(4)};
    printf("%f %f %f %f %f\n", fResistor[0],
                                fResistor[1],
                                fResistor[2],
                                fResistor[3],
                                fResistor[4]);
    */
    close(sock);
    printf("done with server\n");
    return 0;

}
