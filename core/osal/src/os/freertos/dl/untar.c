/*
 * This file is in the public domain.  Use it as you see fit.
 */

/*
 * "untar" is an extremely simple tar extractor:
 *  * A single C source file, so it should be easy to compile
 *    and run on any system with a C compiler.
 *  * Extremely portable standard C.  The only non-ANSI function
 *    used is mkdir().
 *  * Reads basic ustar tar archives.
 *  * Does not require libarchive or any other special library.
 *
 * To compile: cc -o untar untar.c
 *
 * Usage:  untar <archive>
 *
 * In particular, this program should be sufficient to extract the
 * distribution for libarchive, allowing people to bootstrap
 * libarchive on systems that do not already have a tar program.
 *
 * To unpack libarchive-x.y.z.tar.gz:
 *    * gunzip libarchive-x.y.z.tar.gz
 *    * untar libarchive-x.y.z.tar
 *
 * Written by Tim Kientzle, March 2009.
 *
 * Released into the public domain.
 */

/* These are all highly standard and portable headers. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ff.h"



int filesize;
unsigned int readCursor;

/* This is for mkdir(); this may need to be changed for some platforms. */
#include <sys/stat.h>  /* For mkdir() */

/* Parse an octal number, ignoring leading and trailing nonsense. */
int parseoct(const char *p, size_t n)
{
	int i = 0;

	while ((*p < '0' || *p > '7') && n > 0) {
		++p;
		--n;
	}
	while (*p >= '0' && *p <= '7' && n > 0) {
		i *= 8;
		i += *p - '0';
		++p;
		--n;
	}
	return (i);
}

/* Returns true if this is 512 zero bytes. */
int is_end_of_archive(const char *p)
{
	int n;
	for (n = 511; n >= 0; --n)
		if (p[n] != '\0')
			return (0);
	return (1);
}

/* Create a directory, including parent directories as necessary. */
void create_dir(char *pathname)
{
	char *p;
	int r;

	/* Strip trailing '/' */
	if (pathname[strlen(pathname) - 1] == '/')
		pathname[strlen(pathname) - 1] = '\0';

	/* Try creating the directory. */
	r = f_mkdir(pathname);

	if (r != 0) {
		/* On failure, try creating parent directory. */
		p = strrchr(pathname, '/');
		if (p != NULL) {
			*p = '\0';
			create_dir(pathname);
			*p = '/';
			r = f_mkdir(pathname);
		}
	}
	if (r != 0)
		fprintf(stderr, "Could not create directory %s\n", pathname);
}

/* Create a file, including parent directory as necessary. */
void create_file(char *srcBuf, char *pathname)
{
    int status;
	static FIL fil;
    status = f_open(&fil, pathname, FA_CREATE_ALWAYS | FA_WRITE);
	if (status != FR_OK)
	{
		/* Try creating parent dir and then creating file. */
		char *p = strrchr(pathname, '/');
		if (p != NULL) {
			*p = '\0';
			create_dir(pathname);
			*p = '/';
			f_open(&fil, pathname, FA_CREATE_ALWAYS | FA_WRITE);
		}
	}

	while(filesize > 0)
	{
		unsigned int bytesToWrite = 512;
		unsigned int bytesWritten = 0;

		if (filesize < 512)
		{
			bytesToWrite = filesize;
		}

		filesize -= bytesToWrite;

		status = f_write(&fil, &srcBuf[readCursor], bytesToWrite, &bytesWritten);
		if (status != FR_OK)
		{
			fprintf(stderr, "Failed write\n");
			filesize = 0;
		}

		readCursor += 512;
	}

	f_close(&fil);
}

/* Verify the tar checksum. */
int verify_checksum(const char *p)
{
	int n, u = 0;
	for (n = 0; n < 512; ++n) {
		if (n < 148 || n > 155)
			/* Standard tar checksum adds unsigned bytes. */
			u += ((unsigned char *)p)[n];
		else
			u += 0x20;

	}
	return (u == parseoct(p + 148, 8));
}

/* Extract a tar archive. */
void untar(char *srcBuf, unsigned int srcSize, const char *path)
{
	char buff[512];
	FIL  f;
	size_t bytes_read;
    int status;
    readCursor = 0;

	printf("Extracting from %s\n", path);
	for (;;) {
		unsigned int remainingBytes = srcSize - readCursor;
		if(remainingBytes < 512)
		{
			fprintf(stderr,
			    "Short read on %s: expected 512, got %d\n",
			    path, (int)remainingBytes);
			return;
		}

		memcpy(buff, &srcBuf[readCursor], 512);
		readCursor += 512;

		if (is_end_of_archive(buff)) {
			printf("End of %s\n", path);
			return;
		}
		if (!verify_checksum(buff)) {
			fprintf(stderr, "Checksum failure\n");
			return;
		}
		filesize = parseoct(buff + 124, 12);
		switch (buff[156]) {
		case '1':
			printf(" Ignoring hardlink %s\n", buff);
			break;
		case '2':
			printf(" Ignoring symlink %s\n", buff);
			break;
		case '3':
			printf(" Ignoring character device %s\n", buff);
				break;
		case '4':
			printf(" Ignoring block device %s\n", buff);
			break;
		case '5':
			printf(" Extracting dir %s\n", buff);
			create_dir(buff);
			filesize = 0;
			break;
		case '6':
			printf(" Ignoring FIFO %s\n", buff);
			break;
		default:
			printf(" Extracting file %s\n", buff);
			create_file(srcBuf, buff);
			break;
		}
	}
}

