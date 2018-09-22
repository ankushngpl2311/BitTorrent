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
       


       mtorrent(localpathstr,tracker1addrstr,tracker2addrstr,torrentfilename);
       

       int n = localpathstr.length();  
      
       ifstream fin;
       char filepatharr[n+1];        

       strcpy(filepatharr, localpathstr.c_str()); 
       fin.open(filepatharr, fstream::binary);  
    
       int fsize= getfilesize(fin);
      
                                             //**********************************
       string sha =getsha(fin,fsize);       //getsha closes the  fin file
                                           //*************************************
         string hashofhash= shaOfStr(sha);
       downloadpathfile(hashofhash , localpathstr );



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
      
     
  char torrentfilenamearr[n+1];        

  strcpy(torrentfilenamearr, torrentfilename.c_str()); 
   
   fout.open(torrentfilenamearr);

     
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

