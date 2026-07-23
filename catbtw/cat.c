#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#define BUF_SIZE 8192

int cat_stream(FILE *fp){
    char buf[BUF_SIZE];
    size_t n;

    while ((n = fread(buf, 1, BUF_SIZE, fp)) > 0){
        if (fwrite(buf, 1, n, stdout) != n){
            perror("write error");
            return 1;
        }
    }

    if (ferror(fp)){
        perror("read error");
        return 1;
    }

    return 0;
}

int main(int argc, char *argv[]){
    int exit_status = 0;
    if (argc == 1){
        if (cat_stream(stdin) != 0) exit_status = 1;
    } else {
        for (int i = 1; i < argc; i++){
            FILE *fp = strcmp(argv[i], "-") == 0 ? stdin : fopen(argv[i], "rb");

            if (!fp) { perror(argv[i]); exit_status = 1; continue; }
            if (cat_stream(fp) != 0) exit_status = 1;
            if (fp != stdin) fclose(fp);
            }
    }
    return exit_status;
}
