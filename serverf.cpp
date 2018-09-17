#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include <netdb.h>
#include <netinet/in.h>
#include<unistd.h>
#include<fstream>
#include<string.h>

#define BUFFER_SIZE 512
#define BLOCKSIZE 512

// int gfilesize(ifstream &fin)
// {
//     int fsize = fin.tellg();
//     fin.seekg( 0, std::ios::end );
//     fsize = fin.tellg() - fsize;
//     fin.seekg( 0, std::ios::beg);
//     return fsize;
// }


using namespace std;



int main(int argc, char *argv[])
{
	int sockfd,newsockfd,portno,clilen;
	char buffer[256];
    unsigned char fbuffer[BUFFER_SIZE];
	struct sockaddr_in serv_addr, cli_addr;
	int n;
	//ifstream fin;
	sockfd= socket( AF_INET, SOCK_STREAM,0);

	if(sockfd<0)
	{
		perror("Erroe opening socket");
		exit(1);
	}
    
     cout<<"Socket created\n";
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = 5001;
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

    //start communication

    bzero(buffer,256);
    n=read(newsockfd,buffer,255);


    if(n<0)
    {
    	perror("Error reading from socket");
    	exit(1);
    }
    printf("Here is the message %s:",buffer);

    
   //***************************************************
    //   send file
   //***************************************************

    ifstream fin;
   //ofstream fout;
  
   fin.open("file.txt", fstream::binary);
   //fout.open("newfile.txt");
   
   //int fsize= gfilesize(fin);
    int fsize = fin.tellg();
    fin.seekg( 0, std::ios::end );
    fsize = fin.tellg() - fsize;
    fin.seekg( 0, std::ios::beg);
    //return fsize;
    cout<<"filesize is= "<<fsize<<"\n";
   while(fsize>=0)
   {
       
         if(fsize>BUFFER_SIZE)
         {
             fin.read((char *)fbuffer, BUFFER_SIZE);
              n= write(newsockfd,fbuffer,BUFFER_SIZE);
         }
         else
         {
            fin.read((char *)fbuffer, fsize);
              n= write(newsockfd,fbuffer,fsize);
         }

         fsize=fsize-BUFFER_SIZE;
        // cout<<"in progress fsize = "<<fsize<<"\n";

      bzero((char *) fbuffer, BUFFER_SIZE);
      if(n<0)
    {
        perror("Error writing to socket");
        exit(1);
    }

   }

    
    //n= write(newsockfd,"I got your message",18);

    cout<<"file send success";
    close(sockfd);
    fin.close();
    //fout.close();

    return 0;

}