#include <stdio.h>
#include <unistd.h>



int main(int argc, char *argv[]) {
    int opt;
    char *filename = NULL;
    int verbose = 0;

    while ((opt = getopt(argc, argv, "f:v")) != -1) {
        switch (opt) {
            case 'f':
                filename = optarg;
                break;
            case 'v':
                verbose = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-v] [-f filename]\n", argv[0]);
                return 1;
        }
    }

    if (filename) printf("Файл: %s\n", filename);
    if (verbose) printf("Включён подробный режим\n");

    return 0;
}
