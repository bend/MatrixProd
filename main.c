#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include "multiplier.h"


void
usage(void)
{
    printf("Usage: [matrixprod -o OUTPUT_FILE -n NUM_THREADS>1 INPUT_FILE]\n");
}

void check_params(char* file, char* nflag, char* oflag)
{
    int n;

    if (file == NULL)
    {
        usage();
        exit(0);
    }

    if (nflag != NULL)
    {
        n = strtol(nflag, NULL, 10);

        if (n < 2)
        {
            usage();
            exit(0);
        }
    }

    if (oflag == NULL)
    {
        usage();
        exit(0);
    }
}


int main(int argc, char** argv)
{
    int c;
    char* input_file;
    char* nflag;
    char* oflag;
    int n;

    if (argc < 2)
    {
        usage();
        return EXIT_FAILURE;
    }

    while ((c = getopt (argc, argv, "n:o:")) != -1)    /*Parse arguments*/
    {
        switch (c)
        {
            case 'n':
                nflag = (char*)optarg;
                break;

            case 'o':
                oflag = (char*)optarg;
                break;

            default:
                usage();
                break;
        }
    }

    input_file = argv[argc - 1];
    check_params(input_file, nflag, oflag);

    if (nflag == NULL)
        n = 2;

    else
        n = (int)strtol(nflag, NULL, 10);

    if (multiplier_start(n, input_file, oflag ) == -1)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

