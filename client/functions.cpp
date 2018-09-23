#include<vector>
#include <openssl/sha.h>
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<fstream>
#include<string>
#include<string.h>
//#include <stdlib.h>  
#include <errno.h>  
#include <unistd.h>   //close  
#include <arpa/inet.h>    //close  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  

#include "functions.h"
using namespace std;
#define BUFFER_SIZE 524288
#define BLOCKSIZE 524288
#define TRUE   1  
#define FALSE  0


void splitString(vector <string> &v_str  , string line  , char delim)
{   
  v_str.clear();


  int i;
  int l= line.length();
  
  
  string s="";
  
  for(i=0;i<l;i++)
  {   
       
       if(line[i]==delim)
       {  if(s!="")
          v_str.push_back(s);
          s="";
          continue;
       }

       s= s + line[i];
  
  }


  if(s!="")
    v_str.push_back(s);
  
}



bool mapToFile(const string &filename,map < string , string > &fileMap)     //Write Map   sha|downloadpath  sha|bitmap
{
    ofstream ofile;
    ofile.open(filename.c_str(),ios::out|ios::app);
    if(!ofile)
    {
        return false;           //file does not exist and cannot be created.
    }
    
    for(map < string , string >::const_iterator iter= fileMap.begin(); iter!=fileMap.end(); ++iter)
    {
        ofile<<iter->first<<"|";
        
        
         ofile<<iter->second;
        ofile<<"\n";
    }
    return true;
}



bool fileToMap(const string &filename,map < string , string >  &fileMap)  //Read Map
{
    ifstream ifile;
    ifile.open(filename.c_str());
    if(!ifile)
    {   cout<<"coulnot read file\n";
         return false;   //could not read the file.
    
        
    }
    string line;
    string key;
    vector<string> v_str;
    while(ifile>>line)
    {     //cout<<"before\n";
         string value;
        splitString(v_str,line,'|');
        // v_str.push_back("sha1");
         //v_str.push_back("127.0.0.1:1010,126.0.0.1:1010,124.0.0.1:1010,");
        //v_str={"sha1","127.0.0.1:1010,126.0.0.1:1010,124.0.0.1:1010,"}
        int l=line.length();
        //cout<<"after\n";
        for(vector<string>::iterator iter = v_str.begin();;++iter)        //First vector element is the key.
        {     //cout<<"in for\n";
            if(iter == v_str.begin())
            {     //vector < string > test;
                fileMap[*iter]="test";
                key= *iter;
                continue;
            }
            value= *iter;
            //fileMap[key]= *iter;
            break;
        }
     //cout<<"vec = "<<vec<<"\n"; 
     //vector <string> ip;
     //splitString(ip,vec,',');
     fileMap[key]=value;
       
       // cout<<"in while\n";
    }
    ifile.close();
    return true;
}

void conntrackershare(string command,string tracker1addrstr,string tracker2addrstr, string hashofhash,string filename,string clientaddrstr)
{  

   string tosendstr = "";
   
   tosendstr = command + " " + hashofhash + " " + filename + " " + clientaddrstr;

   

   int sockfd,portno ,n;
  
  struct sockaddr_in serv_addr;
  struct hostent *server;

  char buffer[256];

  

    // vector < string > clientaddr;

    // splitString(clientaddr , argv[1], ':');
    //   string clientip=clientaddr[0];
    //   string clientport=clientaddr[1];
         
      vector < string > tracker1addrvec;

      splitString(tracker1addrvec, tracker1addrstr, ':');
      

      //get port of tracker1
     int len= tracker1addrvec[1].length();          //len of port
     char tracker1portarr[len+1];
     strcpy(tracker1portarr, tracker1addrvec[1].c_str());
     tracker1portarr[len]=0;
     portno =atoi(tracker1portarr);

                        
     
      sockfd = socket(AF_INET, SOCK_STREAM, 0);
     

     if(sockfd<0)
     {
        perror("Error opening socket");
        exit(1);
     }
     printf("socket created");
      
       

     //get ip of tracker1
      len= tracker1addrvec[0].length();
     char tracker1iparr[len+1];
     strcpy(tracker1iparr, tracker1addrvec[0].c_str());
     tracker1iparr[len]=0;
     server= gethostbyname(tracker1iparr);
      
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

   cout<<"connected\n";
   
   
     /* Now read tracker's response */
   bzero(buffer,256);
   n = read(sockfd, buffer, 255);
   
   if (n < 0) {
      perror("ERROR reading from socket");
      exit(1);
   }
  
   printf("%s\n",buffer);

      
  //str to char*
    int ltosendstr = tosendstr.length();  
      
    
    char tosendarr[ltosendstr + 1];  
      
    strcpy(tosendarr, tosendstr.c_str());  
   

    //Send message to the tracker 
   n = write(sockfd, tosendarr, strlen(tosendarr));
   
   if (n < 0) {
      perror("ERROR writing to socket");
      exit(1);
   }
  


    close(sockfd);

}
void downloadpathfile(string hashofhash, string localpathstr)
{
    map < string, string > m;
    ofstream ofile;
     m[hashofhash] = localpathstr;
     mapToFile("downloadpath.txt",m);
   // ofile.open("downloadpath.txt",ios::out|ios::app);

    // string entry = sha + "|" + localpathstr;
    // ofile << entry;
    // ofile << "\n";
}

string givebitmap(string hashofhash)
{

   map <string , string > filemap;

   fileToMap("bitmap",filemap);

   string bitmap;

   bitmap = filemap[hashofhash];
   return bitmap;

}
void bitmapfile(string hashofhash,int noofpiece)
{     
         int i;

         string bitmap= "";

         for(i=0;i<noofpiece;i++)
          bitmap = bitmap + "1";

        map <string , string> filemap;

        filemap[hashofhash] = bitmap;
         
         mapToFile("bitmap",filemap);
       

}
void share(string clientaddrstr,string tracker1addrstr,string tracker2addrstr, string localpathstr, string torrentfilename)
{
       
      //cout<<"torrent file name "<<torrentfilename<<"\n";
      //cout<<"len= "<<torrentfilename.length()<<"\n";

       mtorrent(localpathstr,tracker1addrstr,tracker2addrstr,torrentfilename);
       

       int n = localpathstr.length();  
      
       ifstream fin;
       char filepatharr[n+1];        

       strcpy(filepatharr, localpathstr.c_str());         //filepath needed just to open the file 
       fin.open(filepatharr, fstream::binary);  
    
       int fsize= getfilesize(fin);
      
                                             //**********************************
       string sha =getsha(fin,fsize);       //getsha() closes the  fin file
                                           //*************************************
         string hashofhash= shaOfStr(sha);
       downloadpathfile(hashofhash , localpathstr );

         
       //**************************************************
       //connect to tracker to update seeder file
       //**************************************************
         vector < string > localpathvec;
         splitString(localpathvec, localpathstr , '/');
           int lpathvec = localpathvec.size();
         string filename =   localpathvec[ lpathvec - 1 ]; 

         thread t1(conntrackershare,"share",tracker1addrstr,tracker2addrstr,hashofhash,filename,clientaddrstr);

         t1.join();                  //thread runs as a deamon  (independent from main prog)
           
       int noofpiece =sha.length()/20;
       cout<<"no of piece = "<<noofpiece;
        bitmapfile(hashofhash,noofpiece);


}




void conntrackerget(string tracker1addrstr, string tracker2addrstr, string hashofhash,string &peers)
{
    
   string tosendstr = "";
   tosendstr = tosendstr + "get" + " " + hashofhash;     // get hashofhash


     int sockfd,portno ,n;
  
  struct sockaddr_in serv_addr;
  struct hostent *server;

  char buffer[256];

  
         
      vector < string > tracker1addrvec;

      splitString(tracker1addrvec, tracker1addrstr, ':');
      

      //get port of tracker1
     int len= tracker1addrvec[1].length();          //len of port
     char tracker1portarr[len+1];
     strcpy(tracker1portarr, tracker1addrvec[1].c_str());
     tracker1portarr[len]=0;
     portno =atoi(tracker1portarr);

                        
     
      sockfd = socket(AF_INET, SOCK_STREAM, 0);
     

     if(sockfd<0)
     {
        perror("Error opening socket");
        exit(1);
     }
     printf("socket created");
      
       

     //get ip of tracker1
      len= tracker1addrvec[0].length();
     char tracker1iparr[len+1];
     strcpy(tracker1iparr, tracker1addrvec[0].c_str());
     tracker1iparr[len]=0;
     server= gethostbyname(tracker1iparr);
      
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

   cout<<"connected\n";
   
   
     /* Now read tracker's response */   //read welcome message i.e connectivity ack
   bzero(buffer,256);
   n = read(sockfd, buffer, 255);
   
   if (n < 0) {
      perror("ERROR reading from socket");
      exit(1);
   }
  
   printf("%s\n",buffer);

      
  //str to char*
    int ltosendstr = tosendstr.length();  
      
    
    char tosendarr[ltosendstr + 1];  
      
    strcpy(tosendarr, tosendstr.c_str());  
   

    //Send message to the tracker    ( get hashofhash )
   n = write(sockfd, tosendarr, strlen(tosendarr));
   
   if (n < 0) {
      perror("ERROR writing to socket");
      exit(1);
   }
  

  //read peers from tracker
   char peerarr[1024];
   bzero(peerarr,1024);
   n = read(sockfd, peerarr, 1023);
   
   if (n < 0) {
      perror("ERROR reading from socket");
      exit(1);
   }
  
   printf("%s\n",peerarr);

    peers =string(peerarr);

    close(sockfd); 

   
}

void connpeersget(string peers ,string hashofhash,vector <string> &piecevec)
{
    //vector < string > piecevec;
    string tosendstr = "";
    tosendstr = tosendstr + "get" + " " + hashofhash;   // get hashofhash


   vector < string > seederaddr;

   splitString(seederaddr , peers, ',');
    
    int veclen= seederaddr.size();

    int i;
for(i=0;i<veclen;i++)
{
  cout<<"vec of peer= "<<seederaddr[i]<<"\n";
    
    vector <string> seederipport;
    splitString(seederipport , seederaddr[i], ':');
   string seeder1ipstr   = seederipport[0];
   cout<<"seeder1ip"<<seeder1ipstr<<"\n";
   string seeder1portstr = seederipport[1];
  
    int lenport = seeder1portstr.length();
   // seeder1portstr.erase(lenport-1,1);
 cout<<"seeder1port"<<seeder1portstr<<"\n";
  cout<<"len port = "<<seeder1portstr.length()<<"\n";


  int sockfd,portno ,n;
  
  struct sockaddr_in serv_addr;
  struct hostent *server;

  char buffer[256];

  
         
      //vector < string > tracker1addrvec;

      //splitString(tracker1addrvec, tracker1addrstr, ':');
      

      //get port of tracker1
     int len= seeder1portstr.length();          //len of port
     char seeder1portarr[len+1];
     strcpy(seeder1portarr, seeder1portstr.c_str());
     seeder1portarr[len]=0;
     cout<<"arr= "<<seeder1portarr<<"\n";
     //cout<<"array port";
     portno =atoi(seeder1portarr);

                        
     
      sockfd = socket(AF_INET, SOCK_STREAM, 0);
     

     if(sockfd<0)
     {
        perror("Error opening socket");
        exit(1);
     }
     printf("socket created");
      
       

     //get ip of tracker1
      len= seeder1ipstr.length();
     char seeder1iparr[len+1];
     strcpy(seeder1iparr, seeder1ipstr.c_str());
     seeder1iparr[len]=0;
     server= gethostbyname(seeder1iparr);
      
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

   cout<<"connected\n";
   
   
     /* Now read seeder's response */   //read welcome message i.e connectivity ack
   bzero(buffer,256);
   n = read(sockfd, buffer, 255);
   
   if (n < 0) {
      perror("ERROR reading from socket");
      exit(1);
   }
  
   printf("%s\n",buffer);

      
  //str to char*
    int ltosendstr = tosendstr.length();  
      
    
    char tosendarr[ltosendstr + 1];  
      
    strcpy(tosendarr, tosendstr.c_str());  
   

    //Send message to the seeder    ( get hashofhash )
   n = write(sockfd, tosendarr, strlen(tosendarr));
   
   if (n < 0) {
      perror("ERROR writing to socket");
      exit(1);
   }
  

  //read piece info from seeder
   char piecearr[1024];
   bzero(piecearr,1024);
   n = read(sockfd, piecearr, 1023);
   
   if (n < 0) {
      perror("ERROR reading from socket");
      exit(1);
   }
  
   printf("%s\n",piecearr);
     string piecestr;
     piecestr=string(piecearr);
     piecevec.pushback(piecestr);
    //cout<<"piece str in connseeder ="<<piecestr<<"\n";
    close(sockfd);


   }
}
void get(const string &mtorrentpathstr, string tracker1addrstr,string tracker2addrstr,string destinationpathstr)
{   
     string sha;
     sha= shafrommtorrent(mtorrentpathstr);
     string hashofhash;
     hashofhash = shaOfStr(sha);
     string peers;
     
      conntrackerget(tracker1addrstr, tracker2addrstr, hashofhash,peers);
       
       vector < string > piecevec;
      connpeersget( peers , hashofhash,piecevec);

      //t1.join(); 


}

string shafrommtorrent(const string &mtorrentpathstr)
{

    ifstream ifile;
    ifile.open(mtorrentpathstr.c_str());
       if(!ifile)
    {   cout<<"coulnot read file\n";
        // return false;   //could not read the file.
    
        
    }
      string line;
      string sha;

      while(ifile>>line)
      {
          sha=line;
         // cout<<"sha in loop ="<<sha<<"\n";

      }

     // cout<<"sha from mtorrent = "<<sha<<endl;
      //cout<<"len of sha frm mtorr= "<<sha.length()<<endl;

      return sha;


}


void mtorrent(string filepath, string tracker1ip, string tracker2ip, string torrentfilename)
{

    
   ifstream fin;
   ofstream fout;
   
   
  vector <string> localpathvec;
  splitString(localpathvec,filepath,'/');
      
  int localpathlen = localpathvec.size();
  string filename= localpathvec[localpathlen-1];
       



  int n = filepath.length();  
      
     
  char filepatharr[n+1];        

  strcpy(filepatharr, filepath.c_str()); 
  fin.open(filepatharr, fstream::binary);  
    
  int fsize= getfilesize(fin);
  //cout<<"filesize"<<fsize<<"\n\n\n";
                                             //**********************************
  string sha =getsha(fin,fsize);            //closes the file
   //cout<<sha.length()<<"\n";              //*************************************
   //cout<<sha;
   

   //string tracker1ip= "127.0.0.1:5001";
   
   //string tracker2ip= "127.0.0.1:5002";
   //string filename="a.mp4";
   string filesize= to_string(fsize);

    
  
  n = torrentfilename.length();  
  //cout<<"torrent file name in mtorr "<<torrentfilename<<"\n";
    //  cout<<"len in mtorr = "<<torrentfilename.length()<<"\n";
     
  char torrentfilenamearr[n+1];        

  strcpy(torrentfilenamearr, torrentfilename.c_str()); 
   
   torrentfilenamearr[torrentfilename.length()]=0;
   
   fout.open(torrentfilenamearr,ios::binary);

     
    n = tracker1ip.length();  
      
     
    char tracker1iparr[n+1];  
      
     
    strcpy(tracker1iparr, tracker1ip.c_str());
    fout<<tracker1iparr;
     
     fout<<"\n";  
   
     
    n = tracker2ip.length(); 
    
    char tracker2iparr[n+1];
    strcpy(tracker2iparr, tracker2ip.c_str());
    fout<<tracker2iparr;
    fout<<"\n";
   
   n = filename.length();
   char fname[n+1];
   strcpy(fname, filename.c_str());
    fout<<fname;
    fout<<"\n";

    n = filesize.length();
   char filsize[n+1];
   strcpy(filsize, filesize.c_str());
    fout<<filesize;
    fout<<"\n";

    n = sha.length();
   char fsha[n+1];
   strcpy(fsha, sha.c_str());
    fout<<fsha;
    //fout<<"\n";

    fout.close();


    cout<<"mtorrent file created successfully!!\n";

}



int getfilesize(ifstream &fin)
{
    int fsize = fin.tellg();
    fin.seekg( 0, std::ios::end );
    fsize = fin.tellg() - fsize;
    fin.seekg( 0, std::ios::beg);
    return fsize;
}


string hexStr(unsigned char *data, int len)
{


	constexpr char hexmap[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                           '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

  std::string s(len * 2, ' ');
  for (int i = 0; i < len; ++i) {
    s[2 * i]     = hexmap[(data[i] & 0xF0) >> 4];
    s[2 * i + 1] = hexmap[data[i] & 0x0F];
  }
  return s;
}


string shaOfStr(string hashstr)
{  
   //unsigned char ibuf[] = "compute sha1";
    unsigned char obuf[20];


  
    int n = hashstr.length();  
      
    // declaring character array 
    // uchar hasharr[n+1]; 
      char hasharr[n+1];

 strcpy(hasharr, hashstr.c_str() ); 
      
unsigned char digest[n+1];
strncpy((char *)digest, hasharr, n+1);
    // copying the contents of the  
   
    SHA1(digest, strlen((const char*)digest), obuf);

    string s="";

     s=hexStr(obuf,20);
  

  //cout<<"hash of hash = "<<s<<"\n";
     return s;


    

}

string getsha(ifstream &fin,int fsize)
{

   string sha="";
   unsigned char buffer[BUFFER_SIZE];
   unsigned char obuf[20];

   int i=0;



    if(!fin.is_open())       //If the file opening fails, ERROR message prints
    {
         printf("ERROR: The file open failed.\n");  
         system("PAUSE");

         //exit(1);
    }  

	else
	{
		//printf("File opened successfully!\n");
	}

  	


while(fsize>0)
{  
  if(fsize>BUFFER_SIZE)
  {  fin.read((char *)buffer, BUFFER_SIZE);
       
    
    SHA1(buffer, strlen((const char*)buffer), obuf);
   string s="";

   s=hexStr(obuf,20);
   //cout<<s<<" "<<s.length()<<"\n";
   s.erase(20,20);  	
   //cout<<s<<" "<<s.length()<<"\n";
   sha+= s;
  

  }
  else
   { fin.read((char *)buffer, fsize);
    //fout.write((char *)buffer, fsize);
     
    SHA1(buffer, strlen((const char*)buffer), obuf);
    string s="";
    s= hexStr(obuf,20);

    sha+= s;
   // cout<<"fsize= "<<fsize<<"\n";


    }
  fsize=fsize-BUFFER_SIZE;

  bzero((char *) buffer, BUFFER_SIZE);


}

  fin.close();
  
  
  return sha;

}





void seeder(string clientUploadIp,string clientUploadPort)   
{   
    int opt = TRUE;   
    int master_socket , addrlen , new_socket , client_socket[30] ,  
          max_clients = 30 , activity, i , valread , sd;   
    int max_sd;   
    struct sockaddr_in address;   
         
    char buffer[1025];  //data buffer of 1K  
         
    //set of socket descriptors  
    fd_set readfds;   
         
    //a message  
    char *message = "Seeder 1 active! Thank you for connecting. \r\n";   
     
    //initialise all client_socket[] to 0 so not checked  
    for (i = 0; i < max_clients; i++)   
    {   
        client_socket[i] = 0;   
    }   
         
    //create a master socket  
    if( (master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0)   
    {   
        perror("socket failed");   
        exit(EXIT_FAILURE);   
    }   
     
    //set master socket to allow multiple connections ,  
    //this is just a good habit, it will work without this  
    if( setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,  
          sizeof(opt)) < 0 )   
    {   
        perror("setsockopt");   
        exit(EXIT_FAILURE);   
    }   
     
     int portno;
     int lport= clientUploadPort.length();          //len of port
     char   clientUploadPortarr[lport+1];
     strcpy(clientUploadPortarr, clientUploadPort.c_str());
     clientUploadPortarr[lport]=0;
     portno =atoi(clientUploadPortarr);
    
    //type of socket created  
    address.sin_family = AF_INET;   
    address.sin_addr.s_addr = INADDR_ANY;         //random ip
    address.sin_port = htons( portno );   
         
    //bind the socket to localhost port 8888  
    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0)   
    {   
        perror("bind failed");   
        exit(EXIT_FAILURE);   
    }   
  //  printf("Listener on port %d \n", PORT);   
         
    //try to specify maximum of 3 pending connections for the master socket  
    if (listen(master_socket, 3) < 0)   
    {   
        perror("listen");   
        exit(EXIT_FAILURE);   
    }   
         
    //accept the incoming connection  
    addrlen = sizeof(address);   
    //puts("Waiting for connections ...");   
         
    while(TRUE)   
    {   
        //clear the socket set  
        FD_ZERO(&readfds);   
     
        //add master socket to set  
        FD_SET(master_socket, &readfds);   
        max_sd = master_socket;   
             
        //add child sockets to set  
        for ( i = 0 ; i < max_clients ; i++)   
        {   
            //socket descriptor  
            sd = client_socket[i];   
                 
            //if valid socket descriptor then add to read list  
            if(sd > 0)   
                FD_SET( sd , &readfds);   
                 
            //highest file descriptor number, need it for the select function  
            if(sd > max_sd)   
                max_sd = sd;   
        }   
     
        //wait for an activity on one of the sockets , timeout is NULL ,  
        //so wait indefinitely  
        activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);   
       
        if ((activity < 0) && (errno!=EINTR))   
        {   
            printf("select error");   
        }   
             
        //If something happened on the master socket ,  
        //then its an incoming connection  
        if (FD_ISSET(master_socket, &readfds))   
        {   
            if ((new_socket = accept(master_socket,  
                    (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)   
            {   
                perror("accept");   
                exit(EXIT_FAILURE);   
            }   
             
            //inform user of socket number - used in send and receive commands  
            printf("New connection , socket fd is %d , ip is : %s , port : %d\n" , new_socket , inet_ntoa(address.sin_addr) , ntohs (address.sin_port));   
           
            //send new connection greeting message  
            if( send(new_socket, message, strlen(message), 0) != strlen(message) )   
            {   
               //cout<<"hello\n";
                perror("send");   
            }   
                 

            // fflush(stdin);
            // fflush(stdout);
            // cout<<stdin;
            puts("Welcome message sent successfully");   
                 
            //add new socket to array of sockets  
            for (i = 0; i < max_clients; i++)   
            {   
                //if position is empty  
                if( client_socket[i] == 0 )   
                {   
                    client_socket[i] = new_socket;   
                    printf("Adding to list of sockets as %d\n" , i);   
                         
                    break;   
                }   
            }   
        }   
             
        //else its some IO operation on some other socket 
        for (i = 0; i < max_clients; i++)   
        {   
            sd = client_socket[i];   
                 
            if (FD_ISSET( sd , &readfds))   
            {   
                //Check if it was for closing , and also read the  
                //incoming message  
                if ((valread = read( sd , buffer, 1024)) == 0)   
                {   
                    //Somebody disconnected , get his details and print  
                    getpeername(sd , (struct sockaddr*)&address , \ 
                        (socklen_t*)&addrlen);   
                    printf("Host disconnected , ip %s , port %d \n" ,  
                          inet_ntoa(address.sin_addr) , ntohs(address.sin_port));   
                         
                    //Close the socket and mark as 0 in list for reuse  
                    close( sd );   
                    client_socket[i] = 0;   
                }   
                     
                //Echo back the message that came in  
                else 
                {      

                    //set the string terminating NULL byte on the end  
                    //of the data read  
                   //cout<<"in else "<<buffer<<"\n";
                   //fflush(stdin);
                   
                    buffer[valread] = '\0';  
                     cout<<"in else "<<buffer<<"\n";
                     cout<<"len= "<<strlen(buffer)<<"\n";
                    string commandstr(buffer);
                    vector <string> commandvec;
                    splitString(commandvec, commandstr ,' ');
                    
                    if(commandvec[0]=="get")
                    {    string hashofhash = commandvec[1];
                         string bitmapstr=givebitmap(hashofhash);
                        //peersipstr = get(commandvec);
                        //cout<<"hashofhash recieved = "<<commandvec[1]<<"\n";
                        int lbitmapstr = bitmapstr.length();  
                             
                        char bitmaparr[lbitmapstr + 1];  
                         
                        strcpy(bitmaparr, bitmapstr.c_str()); 
                        send(sd , bitmaparr , strlen(bitmaparr) , 0 );
                        bzero(bitmaparr,strlen(bitmaparr)+1);


                    }

                   //send(sd , buffer , strlen(buffer) , 0 );   
                    
                    
                   //send(sd , buffer , strlen(buffer) , 0 );   
                   bzero(buffer,1024);
                }   
            }   
        }  

    }   
 // cout<<"bye";
    //return 0;   
}   


