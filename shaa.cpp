#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

int main()
{
    unsigned char ibuf[] = "abcdefghijklmnopqrtuvwxyzabcdefghijklmnopqrtuvwxyz";
    unsigned char obuf[20];

    SHA1(ibuf, strlen((const char*)ibuf), obuf);

    int i;
    for (i = 0; i < 20; i++) {
        printf("%02x ", obuf[i]);
    }
    printf("\n");

    return 0;
}