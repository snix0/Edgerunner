#include "fs.h"
#include <glob.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int generate_target_list(char** fileList, int* fileCount) {
    char **found;
    glob_t gstruct;
    int r;

    r = glob(TEST_PATTERN, GLOB_ERR , NULL, &gstruct);
    /* check for errors */
    if( r!=0 )
    {
        if( r==GLOB_NOMATCH )
            fprintf(stderr,"No matches\n");
        else
            fprintf(stderr,"Some kinda glob error\n");
        exit(1);
    }
    
    /* success, output found filenames */
    printf("Found %zu filename matches\n",gstruct.gl_pathc);
    found = gstruct.gl_pathv;
    while(*found)
    {
        printf("%s\n",*found);
        fileList[*fileCount] = malloc(BUFSZ);
        strncpy(fileList[*fileCount], *found, BUFSZ - 1);
        (*fileCount)++;
        found++;
    }
    
    return 0;
}
