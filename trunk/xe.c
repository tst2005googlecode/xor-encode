#include <time.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int xor_encode(int key, FILE *in, FILE *out);


int main(int argc, char *argv[])
{
    clock_t start, finish;
    FILE *in, *out;

    if (argc != 4) {
        fprintf(stderr,
                "Usage: xe <key> <input file name> <output file name>\n");
        return EXIT_FAILURE;
    }

    in = fopen(argv[2], "rb");
    out = fopen(argv[3], "wb");
    if (in == NULL || out == NULL) {
        if (in != NULL)
            fclose(in);
        if (out != NULL) {
            fclose(out);
            remove(argv[3]);
        }
        fprintf(stderr, "One or more files can't be opened.\n");
        return EXIT_FAILURE;
    }

    fprintf(stderr, "Encrypting...\t");
    start = clock();
    if (!xor_encode(atoi(argv[1]), in, out)) {
        perror("Unexpected error occured.\n" \
               "Details of the last error (if any)");
        return errno;
    }
    finish = clock();

    fprintf(stderr, "done! (%g seconds)\n",
           (float)(finish - start) / CLOCKS_PER_SEC);

    return EXIT_SUCCESS;
}
