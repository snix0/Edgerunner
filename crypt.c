#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "crypt.h"

long fsize(FILE* fp) {
    long size;

    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    return size;
}

int encrypt(char* filepath) {
    long size;
    FILE* fp;
    char* body;
    char ch;

    fp = fopen(filepath, "r+");

    size = fsize(fp);
    body = malloc(size);
    fread(body, 1, size, fp);

    // Basic cipher. TODO
    for(int i = 0; body[i] != '\0'; ++i){
        ch = body[i];
        if(ch >= 'a' && ch <= 'z'){
            ch = ch + TEST_KEY;
            if(ch > 'z'){
                ch = ch - 'z' + 'a' - 1;
            }
            body[i] = ch;
        }
        else if(ch >= 'A' && ch <= 'Z'){
            ch = ch + TEST_KEY;
            if(ch > 'Z'){
                ch = ch - 'Z' + 'A' - 1;
            }
            body[i] = ch;
        }
    }
    fseek(fp, 0, SEEK_SET);
    fwrite(body, size, sizeof(char), fp);
    fclose(fp);

    return 0;
}

