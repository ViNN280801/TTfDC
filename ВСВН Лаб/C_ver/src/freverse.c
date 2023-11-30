#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "../include/freverse.h"

void remove_char(char *str, char c)
{
    char *src = NULL, *dst = NULL;
    for (src = dst = str; *src != '\0'; src++)
    {
        *dst = *src;
        if (*dst != c)
            dst++;
    }
    *dst = '\0';
}

void reverse_pchar(int *pchar, size_t size)
{
    int temp = 0;
    for (size_t i = 0; i < size / 2; i++)
    {
        temp = pchar[i];
        pchar[i] = pchar[size - i - 1];
        pchar[size - i - 1] = temp;
    }
}

long get_filesize(FILE *fd)
{
    fseek(fd, 0L, SEEK_END);
    return ftell(fd);
}

char *read_content_from_file(const char *fname)
{
    FILE *file = fopen(fname, "rb");
    if (!file)
    {
        fprintf(stderr, "Error: Can't open file");
        return NULL;
    }

    // +1 -> for nil termination symbol
    long size = get_filesize(file);

    // Returning seek to the beginning of the file
    fseek(file, 0L, SEEK_SET);

    // Allocate memory for the buffer
    char *buffer = (char *)calloc(size, sizeof(char));
    if (!buffer)
    {
        fprintf(stderr, "Error: Can't allocate the memory");
        fclose(file);
        return NULL;
    }
    fread(buffer, 1, size, file);
    return buffer;
}

#ifdef WIN32
#include <io.h> // For "access()" func
#endif

#ifdef __linux__
#include <unistd.h> // For "access()" func
#endif

bool exists(const char *fname)
{
    if (access(fname, F_OK) == 0)
        return true;
    return false;
}

bool create_file(const char *fname)
{
    FILE *file = fopen(fname, "wb");
    if (file)
    {
        fclose(file);
        return true;
    }
    return false;
}

bool change_fname(const char *oldfname, const char *newfname)
{
    if (!exists(oldfname))
        return false;
    if (rename(oldfname, newfname) != 0)
        return false;
    return true;
}

char *reverse_buffer(const char *buffer)
{
    char *token = NULL, *copy = strdup(buffer), *tokens[TOKENSSIZE];
    int num_tokens = 0;

    // 1) Split the input buffer into individual tokens based on the comma and space separators
    token = strtok(copy, ", ");
    while (token != NULL)
    {
        tokens[num_tokens++] = strdup(token);
        token = strtok(NULL, ", ");
    }
    free(copy);

    // 2) Store the tokens in an array and reverse the order of the tokens
    for (int i = 0; i < num_tokens / 2; i++)
    {
        char *temp = tokens[i];
        tokens[i] = tokens[num_tokens - 1 - i];
        tokens[num_tokens - 1 - i] = temp;
    }

    // 3) Create a new buffer to hold the reversed content by concatenating
    // the reversed tokens with commas and spaces
    char *reversed_buffer = (char *)calloc(10 * num_tokens, sizeof(char));
    if (!reversed_buffer)
    {
        fprintf(stderr, "Can't allocate memory");
        return NULL;
    }

    // Emptying string
    reversed_buffer[0UL] = 0x00;

    for (int i = 0; i < num_tokens; i++)
    {
        strcat(reversed_buffer, tokens[i]);
        if (i != num_tokens - 1)
            strcat(reversed_buffer, ", ");
        free(tokens[i]);
    }

    return reversed_buffer;
}

void write_data_to_file(const char *data, FILE *fd)
{
    for (size_t i = 0; i < strlen(data); i++)
        fputc(data[i], fd);
    fputc('\n', fd);
}

void reverse(const char *inf, const char *outf)
{
    FILE *ifd = fopen(inf, "rb");
    if (!ifd)
    {
        fprintf(stderr, "Can't open file '%s' in the binary mode. Exiting...", inf);
        return;
    }

    FILE *ofd = fopen(outf, "wb");
    if (!ofd)
    {
        fprintf(stderr, "Can't open file '%s' in the binary mode. Exiting...", outf);
        fclose(ifd);
        return;
    }

    // Allocating memory for the buffer
    // and check for properly allocation
    char *buffer = read_content_from_file(inf);
    if (!buffer)
    {
        fprintf(stderr, "Can't read from the file \'%s\'", inf);
        return;
    }

    buffer = reverse_buffer(buffer);
    remove_char(buffer, '\n');
    if (!buffer)
    {
        fprintf(stderr, "Can't reverse buffer. Exiting...");
        return;
    }
    write_data_to_file(buffer, ofd);

    free(buffer);

    // Closing inoput and output file streams
    fclose(ifd);
    fclose(ofd);

#ifdef LOG
    fprintf(stdout, "Successfully reversed bytes from input file '%s' to output file '%s'\n", inf, outf);
#endif
}
