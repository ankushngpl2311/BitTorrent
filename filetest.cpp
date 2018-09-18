#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<fstream>
#include<string>
#include<string.h>
#include<thread>
using namespace std;
#define BUFFER_SIZE 512
#define BLOCKSIZE 512


int main()
{


	ifstream fin;
    ofstream fout;

     
    fout.open("text.txt");
     // fout2=fout;
   // fout.seekg( 0, std::ios::end );

     fout.write ("This is an apple",16);
  long pos = fout.tellp();
  fout.seekp (pos-7);
  // fout2.seekp(pos+7);
  // pos=fout.tellp();
  // long pos2=fout2.tellp();

  // cout<<pos<<"\n";
  // cout<<pos2<<"\n";
  // fout.write (" sam",4);

  fout.close();



}