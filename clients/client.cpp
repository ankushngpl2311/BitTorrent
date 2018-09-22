#include<stdio.h>
#include<stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include<unistd.h>
#include <string.h>
#include<iostream>
#include<vector>

#include "functions.h"

using namespace std;




// string command(string com,string sha,string filename,string clientip,string clientport)
// {    
                            
// }





int main(int argc, char **argv)
{
	int sockfd,portno ,n;
  //cout<<"hello\n";
	struct sockaddr_in serv_addr;
	struct hostent *server;

	char buffer[256];

	if(argc < 3)
	{  cout<<"LESS NO OF ARGUMENTS specify clientip:port tracker1ip:port tracker2ip:port\n";
     exit(1);
	 //fprintf( stderr, "usage %s hostname port \n",argv[0]);
	}
     

      
   



    vector < string > clientaddr;

    splitString(clientaddr , argv[1], ':');
      string clientip=clientaddr[0];
      string clientport=clientaddr[1];
         
      vector < string > tracker1addr;

      splitString(tracker1addr, argv[2], ':');
      
     int len= tracker1addr[1].length();          //len of port
     char tracker1arr[len+1];
     strcpy(tracker1arr, tracker1addr[1].c_str());
     tracker1arr[len]=0;
     portno =atoi(tracker1arr);
       

 while(1)
 {
     printf("Please enter the command: ");
    //fflush(stdin);
   bzero(buffer,256);
   fgets(buffer,255,stdin);
   
   string commandstr(buffer);
   vector <string> commandvec;
   splitString(commandvec, commandstr , ' ');
   cout<<"command= "<<commandvec[0]<<"\n";
   if(commandvec[0]=="share")
    {    if(commandvec.size()!=3)
          cout<<"Error Few arguments for share command\n";
          else
      {
         string localpathstr= commandvec[1];
         string torrentfilename = commandvec[2];
         string clientaddrstr =  argv[1];
         string tracker1addrstr= argv[2];
         string tracker2addrstr = argv[3];

        cout<<"before command\n";
         share(clientaddrstr, tracker1addrstr, tracker2addrstr, localpathstr,torrentfilename);
       cout<<"after command\n";
      }

    }
     cout<<"outside command\n";
 //     cout<<"press 1 to exit";
 //   char input;
 // input =getchar();  
 // if(input=='1')
 // break; 
 //  else
 //    { fflush(stdin);
 //      fflush(stdout);
 //      continue;
 //    }

  }
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
