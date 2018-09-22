//#include "json.hpp"
//#include <json/value.h>
#include<iostream>
#include<map>
#include<vector>
#include<algorithm>
#include<fstream>
#include<string>
#include<string.h>
using namespace std;
//using json = nlohmann::json;




bool mapToFile(const string &filename,map < string , vector <string> > &fileMap)     //Write Map
{
    ofstream ofile;
    ofile.open(filename.c_str());
    if(!ofile)
    {
        return false;           //file does not exist and cannot be created.
    }
    int i;
    for(map < string , vector <string> >::const_iterator iter= fileMap.begin(); iter!=fileMap.end(); ++iter)
    {
        ofile<<iter->first<<"|";
        //<<"|"<<iter->second;
        int l= iter->second.size();

        for(i=0;i<l;i++)
        	ofile << iter->second[i] << ",";
        ofile<<"\n";
    }
    return true;
}
void splitString(vector <string> &v_str  , string line  , char delim)
{   
    v_str.clear();

	cout<<"in split string startjhsjdhsjdh\n";
    int i;
	int l= line.length();
	// cout<<"len= "<<l<<"\n";
	//  //line[3]=0;
	//  //int l;
 //     cout<<"string= "<<line;
     // fflush(stdout);
     // fflush(stdin);
 //     string s=" ";
 //     cout<<"hello\n";
 //     fflush(stdout);
 //     fflush(stdin);
	cout<<"hello";
	//getchar();
	string s="";
	for(i=0;i<l;i++)
	{  //cout<<"he"; 
       
       if(line[i]==delim)
       {  cout<<"1";
          v_str.push_back(s);
       	  s="";
          continue;
       	//break;
       }
       s= s+ line[i];
	}
	if(s!="")
		v_str.push_back(s);
	//cout<<"2";
	//getchar();
 //    v_str.push_back(s);
	// i++;
	// s="";
	// int j;
	// for(j=i;j<50;j++)
 //       s=s+line[j];

 //   v_str.push_back(s);
 //   cout<<"in split string\n";
 //   for(i=0;i<2;i++)
   	//cout<<v_str[i]<<" ";
}
bool fileToMap(const string &filename,map < string ,vector < string > > &fileMap)  //Read Map
{
    ifstream ifile;
    ifile.open(filename.c_str());
    if(!ifile)
    {   cout<<"coulnot read file\n";
         return false;   //could not read the file.
    
        
    }
    string line;
    string key;
    vector<string> v_str;
    while(ifile>>line)
    {     //cout<<"before\n";
         string vec;
        splitString(v_str,line,'|');
        // v_str.push_back("sha1");
         //v_str.push_back("127.0.0.1:1010,126.0.0.1:1010,124.0.0.1:1010,");
        //v_str={"sha1","127.0.0.1:1010,126.0.0.1:1010,124.0.0.1:1010,"}
        int l=line.length();
        //cout<<"after\n";
        for(vector<string>::iterator iter = v_str.begin();;++iter)        //First vector element is the key.
        {     //cout<<"in for\n";
            if(iter == v_str.begin())
            {     vector < string > test;
                fileMap[*iter]=test;
                key= *iter;
                continue;
            }
            vec= *iter;
            //fileMap[key]= *iter;
            break;
        }
     cout<<"vec = "<<vec<<"\n"; 
     vector <string> ip;
     splitString(ip,vec,',');
     fileMap[key]=ip;
       
       // cout<<"in while\n";
    }
    return true;
}
// int WriteFile(std::string fname, std::map<std::string, std::string> *m) {
//         int count = 0;
//         if (m->empty())
//                 return 0;

//         FILE *fp = fopen(fname.c_str(), "w");
//         if (!fp)
//                 return -errno;

//         for(std::map<std::string, std::string>::iterator it = m->begin(); it != m->end(); it++) {
//                 fprintf(fp, "%s=%s\n", it->first.c_str(), it->second.c_str());
//                 count++;
//         }

//         fclose(fp);
//         return count;
// }



int main()
{  map < string, vector <string> > m;


   vector < string > v;
   m["sha1"]= v;
   
   m["sha1"].push_back("127.0.0.1:1010");
   m["sha1"].push_back("126.0.0.1:1010");
   m["sha1"].push_back("125.0.0.1:1010");
   m["sha1"].push_back("124.0.0.1:1010");
   
    vector <string> v1;
    m["sha2"]= v1;
   m["sha2"].push_back("127.0.0.1:1010");
   m["sha2"].push_back("126.0.0.1:1010");
   m["sha2"].push_back("125.0.0.1:1010");
   m["sha2"].push_back("124.0.0.1:1010");

   int i;
   
   int l= m["sha1"].size();

   for(i=0;i<l;i++)
   	cout<<m["sha1"][i]<<" ";

   cout<<"\n";

   //m["sha1"].erase(remove(m["sha1"].begin(), m["sha1"].end(), "125.0.0.1:1010"), m["sha1"].end());


   //  l= m["sha1"].size();
   // for(i=0;i<l;i++)
   // 	cout<<m["sha1"][i]<<" ";


  map < string , vector <string> > m2;
   
mapToFile("seeder",m);

// fileToMap("seeder",m);
// cout<<"from file\n";
// //cout<<m2["sha1"];
// int l =m["sha1"].size();
// cout<< "len= "<<l<<"\n";
// cout<<"1st= "<<m["sha1"][0]<<"\n";
// for(int i=0;i<l;i++)
// {
// 	cout<<m["sha1"][i]<<" ";
// }
// cout<<"\ndone";
   
















// json j;

	// j["pi"]="hlo";
	
// j= {
//   "pi": 3.141,
//   "happy": true,
//   "name": "Niels",
//   "nothing": null,
//   "answer": {
//     "everything": 42
//   },
//   "list": [1, 0, 2],
//   "object": 
//   {
//     "currency": "USD",
//     "value": 42.99
//   }
//    };


   //cout<<j["pi"];
   return 0;


}