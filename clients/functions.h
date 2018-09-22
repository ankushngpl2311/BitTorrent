
#include<vector>
#include <openssl/sha.h>
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<fstream>
#include<string>
#include<string.h>
#include<map>

//#include "functions.h"
using namespace std;

void splitString(vector <string> &v_str  , string line  , char delim);
void share(string clientaddrstr,string tracker1addrstr,string tracker2addrstr, string localpathstr, string torrentfilename);


void mtorrent(string filepath,string tracker1ip,string tracker2ip,string torrentfilename);
int getfilesize(ifstream &fin);

string hexStr(unsigned char *data, int len);
string getsha(ifstream &fin,int fsize);
string shaOfStr(string hashstr);

void downloadpathfile(string sha, string localpathstr);
bool mapToFile(const string &filename,map < string , string > &fileMap);





