#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<fstream>
#include<string>
#include<string.h>
using namespace std;

#define BLOCKSIZE 512
int main()
{


 //    fstream fio; 
 //    string line; 
  
 //    // by default openmode = ios::in|ios::out mode 
 //    // Automatically overwrites the content of file, To append 
 //    // the content, open in ios:app 
 //    // fio.open("sample.txt", ios::in|ios::out|ios::app) 
 //    // ios::trunc mode delete all conetent before open 
 //    fio.open("file.txt"); 
	// fio.seekg(0, ios::beg); 
  
    // while (fio) { 
  
    //     // Read a Line from File 
    //     getline(fio, line); 
  
    //     // Print line in Console 
    //     cout << line << endl; 
    // } 


    ifstream fin;

    fin.open("server.cpp", fstream::in);  //Opens the text file - fstream::binary as well??
       
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


	//char message[BLOCKSIZE];
	
	int length;
	char * buffer;

    fin.seekg (0, fstream::end);
	length = fin.tellg();  
	fin.seekg (0, fstream::beg);

	cout << "Length of file: " << length << "\n";
	// allocate memory:
	//length =512;
	buffer = new char [length];

	// read data as a block:
	int i=1;
	    while(fin.read (buffer,BLOCKSIZE))
	    {  //replace length with 188 in some sort of loop??
	    	
	         cout<<"block"<<i<<"  \n\n\n"<<buffer<<"\n\n\n\n";
	         bzero((char *) buffer, length);                          //intialize buffer to null
                i++;
	      }
	      cout<<"final\n\n";
	      //bzero((char *) buffer, length);
	      fin.read(buffer,BLOCKSIZE);
	       cout<<"block"<<i<<"  \n\n\n"<<buffer<<"\n\n\n\n";
	      
               i++;
	fin.close();

	// strcpy(message, buffer.c_str());

	// delete[] buffer;
    
    
   
   


   //cout<<buffer;

  
    // Close the file 
    // fio.close(); 
  
	
}