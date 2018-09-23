#include "tracker.h"
#include<iostream>
using namespace std;


bool fileToMap(const string &filename,map < string ,vector < string > > &fileMap)  //Read Map
{
    ifstream ifile;
    ifile.open(filename.c_str(),ios::binary);
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
    ifile.close();
    return true;
}



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


void share(vector < string > &commandvec)
{
      string sha =commandvec[1];
      string filename= commandvec[2];
      string clientaddr=commandvec[3];

       vector < string > toaddvec; 
      //ofstream ofile;
      //ofile.open("seeder.txt",ios::app|ios::out);
      map < string, vector < string > > filemap;

      fileToMap("seederlist",filemap);
      
      if (filemap.count(sha) > 0)
      {
         toaddvec = filemap[sha];
         toaddvec.push_back(filename);
         toaddvec.push_back(clientaddr);
         cout << "hash found" <<endl;
      }


      else
      {
        
        toaddvec.push_back(filename);
        toaddvec.push_back(clientaddr);

        cout<<"not found"<<"\n";
      }

      filemap[sha] = toaddvec;
    
      mapToFile("seederlist",filemap);




}




void splitString(vector <string> &v_str  , string line  , char delim)
{   
  v_str.clear();


  int i;
  int l= line.length();
  
  
  string s="";
  
  for(i=0;i<l;i++)
  {   
       
       if(line[i]==delim)
       {  if(s!="")
          v_str.push_back(s);
          s="";
          continue;
       }

       s= s + line[i];
  
  }


  if(s!="")
    v_str.push_back(s);
  
}
