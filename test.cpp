#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<fstream>
#include<string>
#include<string.h>
using namespace std;
#define BUFFER_SIZE 512
#define BLOCKSIZE 512
int main()
{
   


   ifstream fin;
   ofstream fout;

    fin.open("test", fstream::binary);  //Opens the text file - fstream::binary as well??
       
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

  fout.open("test1");
unsigned char buffer[BUFFER_SIZE];
//...
do{
    
	fin.read((char *)buffer, BUFFER_SIZE);
    //int l=strlen((char*)buffer);

	fout.write((char *)buffer, BUFFER_SIZE);
  bzero((char *) buffer, BUFFER_SIZE);
}while(fin);
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
}
