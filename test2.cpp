
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<fstream>
#include<string>
#include<string.h>
#include<thread>
using namespace std;
//#define BUFFER_SIZE 17695606
#define BUFFER_SIZE 512

//#define BLOCKSIZE 524288
int filesize;
int getfilesize(ifstream &fin)
{
    int fsize = fin.tellg();
    cout<<"in get fn beg ="<<fsize<<"\n";
    fin.seekg( 0, std::ios::end );
    fsize = fin.tellg() - fsize;
    cout<<"in get fn beg ="<<fin.tellg()<<"\n";
    fin.seekg( 0, std::ios::beg);
    return fsize;
}
void f()
{   //int pos=0;
	int i;
	ofstream fout;
	ifstream fin;
    fin.open("file.txt", fstream::binary);  
	fout.open("thread.txt");
	static long oldpos=0;
	static long ifoldpos=0;
	
	fout.seekp(oldpos);
	fin.seekg(ifoldpos);

    //cout<<"in thread1 pos = "<<oldpos<<"\n";
	
	// for(i=0;i<5;i++)
 //     {  
 //     	//printf("in thread 1 i= %d\n",i);
 //     	  string s="";
 //          s= "in thread 1 i= " + to_string(i);
 //          cout<<"s in t1 "<<s<<"\n";
 //          int n = s.length();
 //          cout<<"len 1 ="<<n<<"\n";

 //         char arr[17];
 //         strcpy(arr, s.c_str());
 //         fout<<arr;
 //         fout<<"\n";


 //          //fout.write ("in thread 1",17);
    
 //    }
	unsigned char buffer[BUFFER_SIZE];
   int fsize=766;
   // while(fsize>=0)
   // {
    
   //   fin.read((char *)buffer, BUFFER_SIZE);
   //   fout << buffer;
   //   fsize=fsize- BUFFER_SIZE;

   //  }


  while(fsize>=0)
  {
    if(fsize>BUFFER_SIZE)
   {  fin.read((char *)buffer, BUFFER_SIZE);
      fout.write((char *)buffer, BUFFER_SIZE);
   
   }
   else
   { fin.read((char *)buffer, fsize);
    fout.write((char *)buffer, fsize);
    }
    fsize=fsize-BUFFER_SIZE;
    cout<<"fsize in t1 "<<fsize<<endl;
  // cout<<"fsize in loop "<<fsize<<"\n\n\n";

    bzero((char *) buffer, BUFFER_SIZE);
  }
     //fout.write((char *)buffer, BUFFER_SIZE);


    oldpos=fout.tellp();
    ifoldpos=fin.tellg();
    cout<<"o/p pos "<<oldpos<<"\n";
    cout<<"i/p pos "<<ifoldpos<<"\n";

}

void g()
{  //int pos=50;
	int i;
     ofstream fout;
	 ///fout.open("thread.mp4");
	 ifstream fin;
    fin.open("file.txt", fstream::binary);  
	fout.open("thread.txt");
	static long oldpos=766;
	static long ifoldpos=766;
	
	fout.seekp(oldpos);
	fin.seekg(ifoldpos);

  //static long oldpos=8847803;
  //oldpos = fout.tellp();  
  //fout.seekp(oldpos);
  //cout<<"in th2 pos= "<<oldpos<<"\n";
  //fout.seekp (pos-7);
     

	// for(i=0;i<5;i++)
	//   {	//printf("in thread 2 i= %d\n",i);
	//         string s="";
 //          s= "in thread 2 i= " + to_string(i);
 //          cout<<"s in t2 "<<s<<"\n";
 //          int n = s.length();
 //          cout<<"len2 ="<<n<<"\n";
 //         char arr[17];
 //         strcpy(arr, s.c_str());
 //         fout<<arr;
 //         fout<<"\n";

 //     }

  unsigned char buffer[BUFFER_SIZE];
   int fsize=767;
   // while(fsize>=0)
   // {
    
   //   fin.read((char *)buffer, BUFFER_SIZE);
   //   fout << buffer;
   //   fsize=fsize- BUFFER_SIZE;
   //    //bzero((char *) buffer, BUFFER_SIZE);
   //  }
     //f
   //fout.write("T", BUFFER_SIZE);
  while(fsize>=0)
 {
   if(fsize>BUFFER_SIZE)
  {  fin.read((char *)buffer, BUFFER_SIZE);
   fout.write((char *)buffer, BUFFER_SIZE);
   
  }
  else
   { fin.read((char *)buffer, fsize);
    fout.write((char *)buffer, fsize);
    }
  fsize=fsize-BUFFER_SIZE;
  
  bzero((char *) buffer, BUFFER_SIZE);

 }
    oldpos=fout.tellp();
    ifoldpos=fin.tellg();

}

int main()
{
     ofstream fout;
     ifstream fin;


      fin.open("file.txt", fstream::binary);  
	   
	   filesize = getfilesize(fin);
	   cout<<"file size is"<<filesize<<"\n";
     fout.open("thread.txt");
     char buffer[filesize];
     
      bzero((char *) buffer, filesize);

      fout<< buffer;
      fout.close();
      
      fin.close();

   

     // thread t1([&fout]() { f(fout); });
     // thread t2([&fout]() { g(fout); });
	thread t1(f);


       
	thread  t2(g);

	t1.join();
	t2.join();

	return 0;
}