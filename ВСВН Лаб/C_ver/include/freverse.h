#ifndef FREVERSE_H
#define FREVERSE_H

#include <stdbool.h>

#define BUFSIZE 256
#define TOKENSSIZE 100

/**
 * @brief Removes specified character from the string (all of them)
 * @param str string to remove character from it
 * @param c character to remove from string
 */
void remove_char(char *str, char c);

/**
 * @brief Reversing number
 * @param pchar array of chars to reverse them
 * @param size size of array 'pchar'
 */
void reverse_pchar(int *pchar, size_t size);

/**
 * @brief Gets size of the file by it's descriptor
 * @param fd file descriptor
 * @return Size of the file
 */
long get_filesize(FILE *fd);

/**
 * @brief Reads content from the file
 * @param fname name of the file
 * @return Content of the file as "char*"
 */
char *read_content_from_file(const char *fname);

/**
 * @brief Checker of existence of specified file
 * @param fname name of the file to do existence check
 * @return "true" if file exists, "false" otherwise
 */
bool exists(const char *fname);

/**
 * @brief Creates file in the current directory
 * @param fname name of the file to create
 * @return "true" if the file was created successfully, "false" otherwise
 */
bool create_file(const char *fname);

/**
 * @brief Renames a file with the name 'm_fname'
 * @param oldfname old file name
 * @param newfname new file name to rename the file
 * @return "true" if the renaming was successful, "false" otherwise
 */
bool change_fname(const char *oldfname, const char *newfname);

/**
 * @brief Reversing buffer this way:
 * "0x0A, 0x00, 0x20, 0xFF" -> "0xFF, 0x20, 0x00, 0x0A"
 * @param buffer buffer to reverse it
 * @return Reversed buffer
 */
char *reverse_buffer(const char *buffer);

/**
 * @brief Writes specified data to a file
 * @param data data to write into a file
 * @param fd output file stream
 */
void write_data_to_file(const char *data, FILE *fd);

/**
 * @brief Gets all bytes from the input file, reverse them and put into the output file
 * @param inf name of the input file
 * @param outf name of the output file
 */
void reverse(const char *inf, const char *outf);

#endif // !FREVERSE_H
