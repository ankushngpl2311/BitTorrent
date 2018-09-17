#include<stdio.h>
#include<stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include<unistd.h>
#include <string.h>
#include<iostream>
#include<fstream>

using namespace std;
#define BUFFER_SIZE 512
#define BLOCKSIZE 512

int getfilesize(ifstream &fin)
{
    int fsize = fin.tellg();
    fin.seekg( 0, std::ios::end );
    fsize = fin.tellg() - fsize;
    fin.seekg( 0, std::ios::beg);
    return fsize;
}

int main(int argc, char **argv)
{
	int sockfd,portno ,n;
  
	struct sockaddr_in serv_addr;
	struct hostent *server;

	char buffer[256];
  unsigned char fbuffer[BUFFER_SIZE];
	if(argc < 3)
	{
	 fprintf( stderr, "usage %s hostname port \n",argv[0]);
	}
     

     portno =atoi((char*)argv[2]);

     //create a socket

     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     

     if(sockfd<0)
     {
        perror("Error opening socket");
        exit(1);
     }
     printf("socket created");

     server= gethostbyname((char*)argv[1]);
      
     if (server == NULL) {
      fprintf(stderr,"ERROR, no such host\n");
      exit(0);
   }

     bzero((char *) &serv_addr, sizeof(serv_addr));
   serv_addr.sin_family = AF_INET;
   bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
   serv_addr.sin_port = htons(portno);
   
   /* Now connect to the server */
   if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
      perror("ERROR connecting");
      exit(1);
   }
   
   /* Now ask for a message from the user, this message
      * will be read by server
   */
	 
   printf("Please enter the message: ");
   bzero(buffer,256);
   fgets(buffer,255,stdin);
   
   /* Send message to the server */
   n = write(sockfd, buffer, strlen(buffer));
   
   if (n < 0) {
      perror("ERROR writing to socket");
      exit(1);
   }
   //**********************************************************************
   //                   Read and write file
   //**********************************************************************
   ifstream fin;
   ofstream fout;
  
   fin.open("file.txt", fstream::binary);
   fout.open("socket.txt");
   
   int fsize= getfilesize(fin);

   /* Now read server response */
  cout<<"fsize= "<<fsize<<"\n";   
   while(fsize>=0)                     
   { 
      if(fsize>BUFFER_SIZE)
       { 
         n = read(sockfd, fbuffer, BUFFER_SIZE);
           fout.write((char *)fbuffer, BUFFER_SIZE);
       }
       else
       {
             n = read(sockfd, fbuffer, fsize);
             fout.write((char *)fbuffer, fsize);
       }  
       fsize=fsize-BUFFER_SIZE;
  
         //cout<<"in progress fsize = "<<fsize<<"\n";
      bzero((char *) fbuffer, BUFFER_SIZE);
      
       if (n < 0) 
       {
          perror("ERROR reading from socket");
          exit(1);
       }
   }	
   //printf("%s\n",buffer);
   cout<<"FIle accepted successfully";
   close(sockfd);
   fin.close();
   fout.close();
   return 0;
}
