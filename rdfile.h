#ifndef _RDFILE_H_
#define _RDFILE_H_

/**
 * Read a specific file line.
 * @param file : Location of the file
 * @param line : line number to read.
 */
char* rdfileline( char* file, int line );

/**
 * Read the file from line *from* to *to*
 * @param file : Location of the file
 * @param from : First line to read.
 * @param to : last line to read.
 */
char* rdfilelines( char* file, int from, int to);

#endif
