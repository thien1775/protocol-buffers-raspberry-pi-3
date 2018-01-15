/* Server Program to handle TCP connections */

#include<iostream>
#include<string.h>
#include<unistd.h>
#include<stdlib.h> /* exit, EXIT_FAILURE */
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#include "Employee.pb.h"
const int max_data_size = 4096;


void error(const char *msg)
{
    perror(msg);
    exit(0);
}


int main(int argc, char *argv[]){

     int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[max_data_size];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     if(argc < 2){
          error("No port provided ");
     }    
     sockfd = socket(AF_INET,SOCK_DGRAM,0);
     if(sockfd < 0){
          error("Error opening socket");
     }

     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);

     /*if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0 )
          error("ERROR on binding");
    */
     //maximum backlog queue = 5
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     //accept connection and create new socket
     //old socket will continue listen for new connection
    cout << sockfd << endl;
     newsockfd = accept(sockfd,(struct sockaddr *)&cli_addr, &clilen);
     if(newsockfd < 0)
          error("Error on accept");

     cout << "Server: got connection from: " << inet_ntoa(cli_addr.sin_addr) << "Port : " << ntohs(cli_addr.sin_port) << endl;
  
     //n = read(newsockfd,buffer,max_data_size-1);
     if(n < 0)
          error("ERROR reading from socket");
     cout << "Received message: " << endl;
     std::string a = buffer;
     demo::Employee e;
     e.ParseFromString(a);
     cout << "Received message: " << endl;
     cout << "Employee:\t" << endl;
     cout << "Name:\t" << e.name() << endl;
     cout << "ID:\t" << e.id() << endl;
     cout << "Email:\t" << e.email() << endl;

     //Send message to Client
     std::string data;
     demo::Employee e2;
     e2.set_name("Vince");
     e2.set_id(123);
     e2.set_email("Vince@xyz.com");
     e2.SerializeToString(&data);
     char bts[data.length()];
     sprintf(bts, "%s", data.c_str());
     send(newsockfd,bts,sizeof(bts),0);    
 



    
   /*  send(newsockfd, "Hello, World!\n", 13, 0);
     bzero(buffer,256);
     n = read(newsockfd,buffer,255);
     if(n < 0 )
          error("ERROR reading from socket");
    // cout << "Message : " << buffer << endl;
     n = write(newsockfd, "I got your message",18);
     if(n < 0)
          error("ERROR writing to socket");*/
 
 //    send(newsockfd, "Hello, World!\n", 13, 0);
     close(newsockfd);
     close(sockfd);
     
     return 0;

}
