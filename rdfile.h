#ifndef _RDFILE_H_
#define _RDFILE_H_
#include<sys/stat.h>

/**
 * Read a specific file line.
 * @param file : the absolute path of the file to read.
 * @param line_number : the line starting from 1 to read
 * @param buffer : the bufer to store the file
 * @param buf_size : the size of the buffer
 */
void sfileline( char* file, int line_number, char* buffer, long buf_size);

/**
 * Reads the entire file
 * @param file : the absolute path of the file to read.
 * @param buffer : the bufer to store the file
 * @param buf_size : the size of the buffer
 */
void swholefile( char* file, char* buffer, long buf_size);

void sdirlist( char* directory, char* buffer, long buf_size);

void filestat_perm_string( struct stat fileStat, char* buffer, long buf_size);

void d_type_string(mode_t d_type, char* buffer, long buf_size);

/**
 * @param filename: file to count lines from
 * @return: the number of files or -1 if file not found
*/
int get_lines_number(const char* const filename);

#endif
