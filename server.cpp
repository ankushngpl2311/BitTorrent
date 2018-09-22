#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include <netdb.h>
#include <netinet/in.h>
#include<unistd.h>

#include<string.h>
using namespace std;
int main(int argc, char *argv[])
{
	int sockfd,newsockfd,portno,clilen;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	int n;
	
	sockfd= socket( AF_INET, SOCK_STREAM,0);

	if(sockfd<0)
	{
		perror("Erroe opening socket");
		exit(1);
	}
    
     cout<<"Socket created\n";
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = 5002;
   //initialize socket struct
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
 
    //bind host addr 

    if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    {
       perror("Error on binding");
       exit(1);

    }

   cout<<"Binding done\n";

     //listening

    listen(sockfd,5);

    clilen = sizeof(cli_addr);

    cout<<"sizeof cli_addr="<<clilen<<"\n";
     

    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, (socklen_t *) &clilen);

    if(newsockfd <0)
    {
    	perror("Error on accept");
    	exit(1);
    }
     cout<<"accepted\n";
    //start communication

    bzero(buffer,256);
    n=read(newsockfd,buffer,255);
    int length=strlen(buffer);
    cout<<"len of message= "<<length<<"\n";

    if(n<0)
    {
    	perror("Error reading from socket");
    	exit(1);
    }
    printf("Here is the message %s:",buffer);

    
    n= write(newsockfd,"I got your message",18);

    if(n<0)
    {
    	perror("Error writing to socket");
    	exit(1);
    }

    close(sockfd);
    return 0;

}