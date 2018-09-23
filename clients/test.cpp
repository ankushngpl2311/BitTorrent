#include<string>
#include<string.h>
#include<iostream>
#include<fstream>
using namespace std;

// void f(string mtorrentpathstr)
// {
// 	ifstream ifile;
// 	ifile.open(mtorrentpathstr.c_str());
//        if(!ifile)
//     {   cout<<"coulnot read file\n";
//         // return false;   //could not read the file.
    
        
//     }
//       string line;
//       string sha;

//       while(ifile>>line)
//       {
//           sha=line;
//           cout<<"sha in loop ="<<sha<<"\n";

//       }

	
// }
int main()
{   string fname;
	// cout<<"enter filename: ";
	// cin>>fname;
    
	//f(fname);

  // int n = filepath.length();  
      
     
  // char filepatharr[n+1];        

  // strcpy(filepatharr, filepath.c_str()); 
  // fin.open(filepatharr, fstream::binary); 
  // string filepath="a.mp4.mtorrent"; 
	 // int n = filepath.length();  
      
  //  ifstream ifile;  
  // char filepatharr[n+1];        

  // strcpy(filepatharr, filepath.c_str()); 
  // ifile.open(filepatharr);  
    
   ifstream ifile("hj.mtorrent");

	//ifile.open("a.mp4.mtorrent");
       if(!ifile)
    {   cout<<"coulnot read file\n";
        // return false;   //could not read the file.
    
        
    }
      string line;
      string sha;

      while(ifile>>line)
      {
          sha=line;
          cout<<"sha in loop ="<<sha<<"\n";

      }

}


// #include <iostream>
// #include <fstream>
// using namespace std;

// int main () {
//   ofstream myfile;
//   myfile.open ("example.mtorrent");
//   myfile << "Writing this to a file.\n";
//   myfile.close();
//   return 0;
// }