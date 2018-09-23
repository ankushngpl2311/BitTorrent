#include<vector>
#include<map>
#include<iostream>
#include<fstream>

using namespace std;






bool fileToMap(const string &filename,map < string ,vector < string > > &fileMap);
bool mapToFile(const string &filename,map < string , vector <string> > &fileMap);


void share(vector < string > &commandvec);

void splitString(vector <string> &v_str  , string line  , char delim);
