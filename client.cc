#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

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
    //set of connection//////////////////////////////////
    int sock, n;
    int port = 1024;
    unsigned int length;
    struct sockaddr_in server, from;
    struct hostent *hp;
    char buffer[max_data_size];
    length=sizeof(struct sockaddr_in);
    
    sock= socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) error("socket");

    server.sin_family = AF_INET;
    hp = gethostbyname("192.168.1.32");
    bcopy((char *)hp->h_addr, 
            (char *)&server.sin_addr,
            hp->h_length);
    server.sin_port = htons(port);
    //test the send with a string//////////////////////////
    n=sendto(sock,"hello\n",
            6,0,(const struct sockaddr *)&server,length);
    ////////////////////////////////////////////////////////
    
    
    
       printf("Star protobuf\n");
    demo::Hand message;
    std::string data;
    /*
    message.set_flex_resistor1(3.14f);
    message.set_flex_resistor2(3.24f);
    message.set_flex_resistor3(3.34f);
    message.set_flex_resistor4(3.44f);
    message.set_flex_resistor5(3.54f);
    */
    printf("set int hands\n");
    message.add_flex_resistor(0.12f);
    message.add_flex_resistor(1.12f);
    message.add_flex_resistor(2.14f);
    message.add_flex_resistor(3.14f);
    message.add_flex_resistor(4.15f);
    printf("set worked\n");
    printf("%f\n", message.flex_resistor(0));
    printf("%f\n", message.flex_resistor(1));
    printf("%f\n", message.flex_resistor(2));
    printf("%f\n", message.flex_resistor(3));
    printf("%f\n", message.flex_resistor(4));
    
    message.SerializeToString(&data);
    //char bts[data.length()];
    //bzero(bts,data.length());
    //bts = data.c_str();
    sprintf(buffer, "%s", data.c_str());
    
    //int size = sizeof(bts)/sizeof(*bts); 
    n=sendto(sock,buffer,
            strlen(buffer),0,(const struct sockaddr *)&server,length);
    if (n < 0) error("Sendto");
    printf("done with client send\n");
    close(sock);
    printf("client finish\n");
    return 0;   
}













    


