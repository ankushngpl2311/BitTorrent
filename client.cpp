#include<stdio.h>
#include<stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include<unistd.h>
#include <string.h>
#include<iostream>
#include<vector>
using namespace std;

void splitString(vector <string> &v_str  , string line  , char delim)
{   
    v_str.clear();


    int i;
  int l= line.length();
  
  
  string s="";
  for(i=0;i<l;i++)
  {   
       
       if(line[i]==delim)
       { 
          v_str.push_back(s);
          s="";
          continue;
               }
       s= s+ line[i];
  }
  if(s!="")
    v_str.push_back(s);
  
}
string command(string com,string sha,string filename,string clientip,string clientport)
{
                        
}

int main(int argc, char **argv)
{
	int sockfd,portno ,n;
  //cout<<"hello\n";
	struct sockaddr_in serv_addr;
	struct hostent *server;

	char buffer[256];

	if(argc < 3)
	{
	 fprintf( stderr, "usage %s hostname port \n",argv[0]);
	}
     
    vector < string > clientaddr;

    splitString(clientaddr , argv[1], ':');
      string clientip=clientaddr[0];
      string clientport=clientaddr[1];
         
      vector < string > servaddr;

      splitString(servaddr, argv[2], ':');
      
     int len= servaddr[1].length();
     char arr[len+1];
     strcpy(arr, servaddr[1].c_str());
     arr[len]=0;
     portno =atoi(arr);
       


   printf("Please enter the command: ");
   bzero(buffer,256);
   fgets(buffer,255,stdin);
   



     //create a socket


     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     

     if(sockfd<0)
     {
        perror("Error opening socket");
        exit(1);
     }
     printf("socket created");
      //getchar();
       


      len= servaddr[0].length();
     char servip[len+1];
     strcpy(servip, servaddr[0].c_str());
     servip[len]=0;
     server= gethostbyname(servip);
      
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

   cout<<"connected";
   
   /* Now ask for a message from the user, this message
      * will be read by server
   */

    printf("Please enter the message: ");
   bzero(buffer,256);
   fgets(buffer,255,stdin);
   
    //Send message to the server 
   n = write(sockfd, buffer, strlen(buffer));
   
   if (n < 0) {
      perror("ERROR writing to socket");
      exit(1);
   }
	

   /* Now read server response */
   bzero(buffer,256);
   n = read(sockfd, buffer, 255);
   
   if (n < 0) {
      perror("ERROR reading from socket");
      exit(1);
   }
  
   printf("%s\n",buffer);

   // printf("Please enter the message: ");
   // bzero(buffer,256);
   // // fgets(buffer,255,stdin);
   
   // /* Send message to the server */
   // n = write(sockfd, buffer, strlen(buffer));
   
   // if (n < 0) {
   //    perror("ERROR writing to socket");
   //    exit(1);
   // }
   
  
   // /* Now read server response */
   // bzero(buffer,256);
   // n = read(sockfd, buffer, 255);
   
   // if (n < 0) {
   //    perror("ERROR reading from socket");
   //    exit(1);
   // }
  
   // printf("%s\n",buffer);
   while(1)
   {  char t;
    cin>>t;
    cout<<t<<"\n";
    if(t=='1')
      break;
   }
   close(sockfd);
   return 0;
}
