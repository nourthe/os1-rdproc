#ifndef _RDFILE_H_
#define _RDFILE_H_

/**
 * Read a specific file line.
 * @param file : Location of the file
 * @param line : line number to read. The first line is 1, not 0
 * @return The specified file line
 */
char* rdfileline( char* file, int line );

/**
 * Read the file from line *from* to *to*
 * @param line : line number to read. The first line is 1, not 0
 * @param from : First line to read.
 * @param to : last line to read.
 */
char* rdfilelines( char* file, int from, int to);

#endif
