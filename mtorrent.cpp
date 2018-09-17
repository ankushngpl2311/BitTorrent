//share <local file path> <filename>.mtorrent

#include <openssl/sha.h>
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<fstream>
#include<string>
#include<string.h>
using namespace std;
#define BUFFER_SIZE 524288
#define BLOCKSIZE 524288


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
         exit(1);
    }  

	else
	{
		printf("File opened successfully!\n");
	}

  	


while(fsize>0)
{  
  if(fsize>BUFFER_SIZE)
  {  fin.read((char *)buffer, BUFFER_SIZE);
   
    
    SHA1(buffer, strlen((const char*)buffer), obuf);
   string s="";

   s=hexStr(obuf,20);
        	
   sha+= s;
  

  }
  else
   { fin.read((char *)buffer, fsize);
    //fout.write((char *)buffer, fsize);
     
    SHA1(buffer, strlen((const char*)buffer), obuf);
    string s="";
    s= hexStr(obuf,20);

    sha+= s;
    cout<<"fsize= "<<fsize<<"\n";


    }
  fsize=fsize-BUFFER_SIZE;

  bzero((char *) buffer, BUFFER_SIZE);


}

  fin.close();
  
  
  return sha;

}



int main()
{
    

   ifstream fin;
   ofstream fout;

    fin.open("a.mp4", fstream::binary);  //Opens the text file - fstream::binary as well??
       
    
    int fsize= getfilesize(fin);
  cout<<"filesize"<<fsize<<"\n\n\n";

  string sha =getsha(fin,fsize);
   cout<<sha.length()<<"\n";
   cout<<sha;


   string tracker1ip= "127.0.0.1:5001";
   
   string tracker2ip= "127.0.0.1:5002";
   string filename="a.mp4";
   string filesize= to_string(fsize);

    

   fout.open("abc.txt");

     
int n = tracker1ip.length();  
      
     
    char arr[n+1];  
      
     
    strcpy(arr, tracker1ip.c_str());
    fout<<arr;
    n = tracker2ip.length();  
     fout<<"\n";  
    
    strcpy(arr, tracker2ip.c_str());
    fout<<arr;
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

}