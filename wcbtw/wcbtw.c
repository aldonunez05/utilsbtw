#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 

#define MAX_FILENAME 256
#define IN  1  
#define OUT 0  

int main() {
    FILE *fp;
    char filename[MAX_FILENAME];
    int ch;
    
    unsigned long lines = 0;
    unsigned long words = 0;
    unsigned long bytes = 0;
    
    int state = OUT;

    printf("Enter the filename: ");
    if (fgets(filename, sizeof(filename), stdin) == NULL) {
        printf("Error reading input.\n");
        return EXIT_FAILURE;
    }
    filename[strcspn(filename, "\n")] = '\0';

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: Could not open file '%s'\n", filename);
        return EXIT_FAILURE;
    }

    while ((ch = fgetc(fp)) != EOF) {
        bytes++; 

        if (ch == '\n') {
            lines++;
        }

        if (isspace(ch)) {
            state = OUT;
        } 
        else if (state == OUT) {
            state = IN;
            words++;
        }
    }

    fclose(fp);

    printf(" %lu  %lu %lu %s\n", lines, words, bytes, filename);

    return EXIT_SUCCESS;
}

