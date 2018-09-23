#include<vector>
#include <openssl/sha.h>
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<fstream>
#include<string>
#include<string.h>

#include "functions.h"
using namespace std;
#define BUFFER_SIZE 524288
#define BLOCKSIZE 524288


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



bool mapToFile(const string &filename,map < string , string > &fileMap)     //Write Map
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



}




void conntrackerget(tracker1addrstr, tracker2addrstr, hashofhash,string &peers)
{
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

void get(const string &mtorrentpathstr, string tracker1addrstr,string tracker2addrstr,string destinationpathstr)
{   
     string sha;
     sha= shafrommtorrent(mtorrentpathstr);
     string hashofhash;
     hashofhash = shaOfStr(sha);
     string peers;
     
      thread t1(conntrackerget(tracker1addrstr, tracker2addrstr, hashofhash,ref(peers)));

      t1.join(); 


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

      cout<<"sha from mtorrent = "<<sha<<endl;
      cout<<"len of sha frm mtorr= "<<sha.length()<<endl;

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

