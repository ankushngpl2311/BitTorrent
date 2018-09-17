#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<fstream>
#include<string>
#include<string.h>
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
int main()
{
   


   ifstream fin;
   ofstream fout;
    //char input[1000];

    fin.open("a.mp4", fstream::binary);  //Opens the text file - fstream::binary as well??
       
    // int fsize = fin.tellg();
    // fin.seekg( 0, std::ios::end );
    // fsize = fin.tellg() - fsize;
    // fin.seekg( 0, std::ios::beg);
    int fsize= getfilesize(fin);
  cout<<"filesize"<<fsize<<"\n\n\n";
    //file.close();

   // fseek(fin,0,SEEK_END);
   // int fsize= ftell(fin)+1;
   // rewind(fin);    
    if(!fin.is_open())       //If the file opening fails, ERROR message prints
    {
         printf("ERROR: The file open failed.\n");  
         system("PAUSE");
         exit(1);
    }  

	else
	{
		printf("File opened successfully!");
	}

  fout.open("test.mp4");
unsigned char buffer[BUFFER_SIZE];
//...
int i=0;
// do{
    
// 	//fin.read((char *)buffer, BUFFER_SIZE);
  
//     //int l=strlen((char*)buffer);
// //  cout<<"block"<<i<<"\n\n\n\n\n\n";
// //  i++;
// // cout<<buffer<<"\n";
//   if(fsize>BUFFER_SIZE)
//   {  fin.read((char *)buffer, BUFFER_SIZE);
// 	 fout.write((char *)buffer, BUFFER_SIZE);
//    // cout<<"buffer"<<buffer<<"\n";
//    // cout<<"ptr at "<<fin.tellg()<<"\n";
//    //  cout<<"filesize in f>b "<<fsize;
//   }
//   else
//    { fin.read((char *)buffer, fsize);
//     fout.write((char *)buffer, fsize);
//     }
//   fsize=fsize-BUFFER_SIZE;
//   // cout<<"fsize in loop "<<fsize<<"\n\n\n";

//   bzero((char *) buffer, BUFFER_SIZE);
// }while(fin);

while(fsize>0)
{  
  if(fsize>BUFFER_SIZE)
  {  fin.read((char *)buffer, BUFFER_SIZE);
   fout.write((char *)buffer, BUFFER_SIZE);
   // cout<<"buffer"<<buffer<<"\n";
   // cout<<"ptr at "<<fin.tellg()<<"\n";
   //  cout<<"filesize in f>b "<<fsize;
  }
  else
   { fin.read((char *)buffer, fsize);
    fout.write((char *)buffer, fsize);
    }
  fsize=fsize-BUFFER_SIZE;
  // cout<<"fsize in loop "<<fsize<<"\n\n\n";

  bzero((char *) buffer, BUFFER_SIZE);


}
// while (fin.read((char *)buffer, BUFFER_SIZE))
// {
//   fout.write((char *)buffer, BUFFER_SIZE);
//   bzero((char *) buffer, BUFFER_SIZE);  
// }


// int l=strlen((char*)buffer);
// cout<<"l=="<<l;

//  // fin.read((char *)buffer, l);
//  fout.write((char *)buffer, l);

	cout<<"File written successfully";
  fin.close();
  fout.close();
}
