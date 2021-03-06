#include "file_reader.h"

int
file_ropen(FILE** f, char* path)
{
    /* open file in ro mode */
    if ((*f = fopen(path, "r")) == NULL)
        return -1;

    return 0;
}

int
file_close(FILE* f)
{
    return fclose(f);
}

int
file_read_matrix_size(FILE* f, unsigned int* l, unsigned int* c)
{
    char x;
    char a;
    int r;

    if (fscanf(f, "%c", &a) == EOF)			/* Tests the end of file */
        return 2;

    /* while the next char is \n or EOF or a space, we skip them */
    while (a == '\n' || a == ' ' || a == EOF)
    {
        r = fscanf(f, "%c", &a);

        if (r == EOF)
            return 2;
    }

    /* seek -1 because we read a char that is not a blank */
    fseek(f, -1, SEEK_CUR);
    /* We read the matrix header */
    r = fscanf(f, "%u%c%u", l, &x, c);

    if (r != 3 || r == EOF)
        return -1;

    if (x != 'x')
        return -1;

    return 0;
}

int
file_read_line(FILE* f, int tab[], unsigned int size)
{
    unsigned int i;
    char t;
    int r;

    /* Read the whole line */
    for (i = 0; i < size; i++)
        r = fscanf(f, "%d", &tab[i]);

    if (r == 0 || r == EOF )
        return -1;

    /* read a character and see if its a \n"*/
    do
    {
        t = getc(f);

        if (t != ' ' && t != '\n')
            return -1;
    }
    while (t != '\n');

    if (t != '\n')
        return -1;/* If not the matrix is not valid */

    return 0;
}

int
file_read_next_matrix(FILE* f, matrix** matr)
{
    unsigned int l, c, i;
    int tab[3000];
    int r;

    if ((r = file_read_matrix_size(f, &l, &c)) == -1 || r == 2)
        return r;

    if (matrix_alloc(matr, l, c) == -1)
        return -1;

    for (i = 0; i < l; i++)
    {
        if (file_read_line(f, tab, c) == -1)
        {
            return -1;
        }

        else
        {
            if (matrix_fill_line(*matr, i, tab) == -1)
                return -1;
        }
    }

    return 0;
}
