#include <stdlib.h>
#include <stdio.h>
#include "../file_writer.h"
void
produce_matrices(FILE* f, unsigned int nb_lines, unsigned int nb_column_max, unsigned int nb_matrices)
{
    unsigned int nb_columns;
    unsigned int i, j, s;

    if (nb_matrices == 0)
        return ;

    nb_columns = rand() % nb_column_max + 1;
    file_write_matrix_size(f, nb_lines, nb_columns);

    for (i = 0; i < nb_lines; i++)
    {
        for (j = 0; j < nb_columns; j++)
        {
            s = rand() % 2;

            if (s == 0)
                fprintf(f, "-");

            if (j == nb_columns - 1)
                fprintf(f, "%d\n", rand() % 127);

            else
                fprintf(f, "%d ", rand() % 127);
        }
    }

    produce_matrices(f, nb_columns, nb_column_max, nb_matrices - 1);
}

int main(int argc, char** argv)
{
    FILE* f;
    char path[] = "test_files/gen.txt";

    if (argc < 3)
    {
        printf("usage: matrixproducer nb_lines_first nb_column_max nb_matrices\n");
        return -1;
    }

    file_wopen(&f, path);
    produce_matrices(f, atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
    return 1;
}
