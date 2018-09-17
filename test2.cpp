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

int main()
{
	string s="";

	char arr[5]="abcd";
  int x=12564;

  s= to_string(x);
  cout<<s;
	// s=s+arr;
	// cout<<s<<"\n";
	// s=s+arr;
	// cout<<s<<"\n";
	// s=s+arr;
	// cout<<s<<"\n";
	// cout<<s;
}