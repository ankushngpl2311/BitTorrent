
//g++ -o shaa shaa.cpp -lssl -lcrypto
#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include<string>
#include<iostream>
using namespace std;

std::string hexStr(unsigned char *data, int len)
{


	constexpr char hexmap[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                           '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

  std::string s(len * 2, ' ');
  for (int i = 0; i < len; ++i) {
    s[2 * i]     = hexmap[(data[i] & 0xF0) >> 4];
    s[2 * i + 1] = hexmap[data[i] & 0x0F];
  }
  return s;
}
int main()
{
    unsigned char ibuf[] = "abcdefghijklmnopqrtuvwxyzabcdefghijklmnopqrtuvwxyz";
    unsigned char obuf[20];

    SHA1(ibuf, strlen((const char*)ibuf), obuf);

    int i;
    for (i = 0; i < 20; i++) {
        printf("%02x", obuf[i]);
    }
    cout<<"\n\n";
    string s;
    s=hexStr(obuf,20);
    cout<<s;
    //printf("\n");

    return 0;

//     if( __cplusplus == 201103L ) std::cout << "C++11\n" ;
// else if( __cplusplus == 199711L ) std::cout << "C++98\n" ;
// else std::cout << "pre-standard C++\n" ;
}


//share <local file path> <filename>.mtorrent