#include<stdio.h>
#include<stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include<unistd.h>
#include <string.h>
#include<iostream>

using namespace std;

void splitString(vector <string> &v_str  , string line  , char delim)
{   
    v_str.clear();

  cout<<"in split string startjhsjdhsjdh\n";
    int i;
  int l= line.length();
  
  cout<<"hello";
  //getchar();
  string s="";
  for(i=0;i<l;i++)
  {  //cout<<"he"; 
       
       if(line[i]==delim)
       {  cout<<"1";
          v_str.push_back(s);
          s="";
          continue;
        //break;
       }
       s= s+ line[i];
  }
  if(s!="")
    v_str.push_back(s);
  
}
string command(string c,string sha,)
{

}

int main(int argc, char **argv)
{
	int sockfd,portno ,n;
  cout<<"hello\n";
	struct sockaddr_in serv_addr;
	struct hostent *server;

	char buffer[256];

	if(argc < 3)
	{
	 fprintf( stderr, "usage %s hostname port \n",argv[0]);
	}
     
    vector < string > addr;

    splitString(addr , argv[2], ':');
      string clientip=addr[0];
      string clientport=addr[1];

      vector < string > servaddr;

      splitString(servaddr, argv[3], ':');

     portno =atoi((char*)servaddr[1]);

     //create a socket

     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     

     if(sockfd<0)
     {
        perror("Error opening socket");
        exit(1);
     }
     printf("socket created");
      //getchar();
     server= gethostbyname((char*)servaddr[0]);
      
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
