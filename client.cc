#include<iostream>
#include<stdlib.h>
#include<netdb.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>

#include "Employee.pb.h"
const int max_data_size = 4096;
using std::cout;
using std::endl;
using std::cerr;

void error(const char *msg){

     cerr << "Error: " << msg << "\n";
     exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]){

     int sockfd, portno, n;
     
     struct sockaddr_in serv_addr;
     struct hostent *server;
     
    /*portno = 2000;
    server = gethostbyname("localhost");
    */ 
     char buffer[max_data_size];
    if(argc < 3){
          error("Please provide hostname and port number");
    }

    portno = atoi(argv[2]);
     
     //Create socket
     sockfd = socket(AF_INET,SOCK_DGRAM, 0);
     if(sockfd < 0)
          error("ERROR opening socket");
     
    server = gethostbyname(argv[1]);
     if(server == NULL)
          error("No such host");
      
     bzero((char *) &serv_addr, sizeof(serv_addr));
     serv_addr.sin_family = AF_INET;
     bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr,server->h_length);
     serv_addr.sin_port = htons(portno);

     if(connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) < 0 )
          error("ERROR connecting");

      
    /* cout << "Please enter the message " << endl;
     bzero(buffer,256);
     //cin.get(buffer,strlen(buffer));
     cin >> buffer;
     cout << "entered message is : " << buffer << endl;
     n = write(sockfd, buffer,strlen(buffer));
     if(n < 0)
          error("ERROR writing to socket");
     bzero(buffer,256);
     n = read(sockfd, buffer, 255);
     if(n < 0)
          error("ERROR reading from socket");

     cout << buffer << endl;
     */
     //PROTOBUFFER USE
     std::string msg;
     demo::Employee e;
     e.set_name("Matt");
     e.set_email("Matt@abc.com");
     e.set_id(1002);
     e.SerializeToString(&msg);
     sprintf(buffer,"%s",msg.c_str());
     n = write(sockfd,buffer,strlen(buffer));

     n = read(sockfd,buffer,max_data_size);
     buffer[n] = '\0';
     std::string data = buffer;
     demo::Employee p;
     p.ParseFromString(data);
     cout << "Employee:\t" << endl;
     cout << "Name:\t" << p.name() << endl;
     cout << "ID:\t" << p.id() << endl;
     cout << "Email:\t" << p.email() << endl;

     close(sockfd);     
     return 0;

}













    


