/**** FILE structure ****/
#define BUFSIZE 1024
#define NULL 0
#define EOF (-1)
#define OPEN_MAX 20		/* max files open at once */

typedef struct _iobuf {
	int cnt;			/* characters left */
	char *ptr;			/* next character position */
	char *base;			/* location of buffer */
	int read_mode;
	int write_mode;
	int unbuf_mode;
	int eof_present;
	int err_present;
	int fd;				/* file descriptor */
} FILE;
extern FILE _iob[OPEN_MAX];

#define stdin (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

enum flags { _READ = 01, _WRITE = 02, _UNBUF = 04, _EOF = 010, _ERR = 020 };

/**** stdin, stdout, stderr ****/
FILE _iob[OPEN_MAX] = { { 0, (char *)0, (char *)0,    1, 0,     0, 0, 0,           0 },
			            { 0, (char *)0, (char *)0,    0, 1,     0, 0, 0,           1 },
			            { 0, (char *)0, (char *)0,    0, 1,     1, 0, 0,           2 } };

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);
int fflush(FILE *);
int fclose(FILE *);

#define feof(p) (((p)->flag & _EOF) != 0)
#define ferror(p) (((p)->flag & _ERR) != 0)
#define fileno(p) ((p)->fd)

//#define getc(p) (--(p)->cnt >= 0 ? (unsigned char)*(p)->ptr++ : _fillbuf(p))
int getc(FILE *);

//#define putc(x, p) (--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuf((x), p))
int putc(int, FILE *);

#define getchar() getc(stdin)
#define putchar(x) putc(x, stdout)


/* fopen:  open file, return file ptr */
#include <fcntl.h>
#include <unistd.h>
#define PERMS 0666
FILE *fopen(char *name, char *mode)
{
	int fd;
	FILE *fp;

	if (*mode != 'r' && *mode != 'w' && *mode != 'a')
		return NULL;

	for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
		if ((fp->read_mode || fp->write_mode) == 0)
			break;  /* found next available 'slot' */

	if (fp >= _iob + OPEN_MAX)		/* no free slots */
		return NULL;

	if (*mode == 'w')
		fd = creat(name, PERMS);
	else if (*mode == 'a') {
		if ((fd = open(name, O_WRONLY, 0)) == -1)
			fd = creat(name, PERMS);
		lseek(fd, 0L, 2);
	} else
		fd = open(name, O_RDONLY, 0);
	if (fd == -1)    /* couldn't access name */
		return NULL;

	fp->fd = fd;
	fp->cnt = 0;
	fp->base = NULL;
	/* assign read/write based on mode value */
	fp->read_mode = (*mode == 'r');
	fp->write_mode = !fp->read_mode;
	fp->unbuf_mode = fp->eof_present = fp->err_present = 0;
	
	return fp;
}


/* _fillbuf:  allocate and fill input buffer */
#include <stdlib.h>
int _fillbuf(FILE *fp)
{
	int bufsize;

	if (fp->read_mode && (fp->eof_present || fp->err_present))
		return EOF;
	bufsize = (fp->unbuf_mode) ? 1 : BUFSIZE;
	if (fp->base == NULL)		/* no buffer yet */
		if ((fp->base = (char *)malloc(bufsize)) == NULL)
			return EOF;			/* can't get buffer */
	fp->ptr = fp->base;
	fp->cnt = read(fp->fd, fp->ptr, bufsize);
	if (--fp->cnt < 0) {
		if (fp->cnt == -1) {
			fp->eof_present = 1;
		}
		else {
			fp->err_present = 1;
		}
		fp->cnt = 0;
		return EOF;
	}
	return (unsigned char)*fp->ptr++;
}
int _flushbuf(int c, FILE *fp) {
    int bufsize;
    int out;

	if (fp->write_mode && (fp->eof_present || fp->err_present))
		return EOF;
	bufsize = (fp->unbuf_mode) ? 1 : BUFSIZE;
    if (fp->base == NULL) {		/* no buffer yet */
		if ((fp->base = (char *)malloc(bufsize)) == NULL)
			return EOF;			/* can't get buffer */
        fp->ptr = fp->base;
        *(fp)->ptr++ = c;
        fp->cnt = bufsize - 1;
        return 0;
    } else { /* buffer is full */
        out = write(fp->fd, fp->base, bufsize);
        fp->ptr = fp->base;
        *(fp)->ptr++ = c;
        fp->cnt = bufsize - 1;
        return out;
    }
}
int fflush(FILE *fp) {
    int bufsize, out;

    bufsize = fp->ptr - fp->base;
    out = write(fp->fd, fp->base, bufsize);

    free(fp->base);
    bufsize = (fp->unbuf_mode) ? 1 : BUFSIZE;
    if ((fp->base = (char *)malloc(bufsize)) == NULL)
		return EOF;			/* can't get buffer */
    fp->ptr = fp->base;
    fp->cnt = bufsize;
    return 0;
}
int fclose(FILE *fp) {

    free(fp->base);
    fp->cnt = 0;
    fp->base = (char *)0;
    fp->ptr = (char *)0;

    return 0;
}

int fseek(FILE *, long offset, int origin);
int get(FILE *, long pos, char *buf, int n);

/* main routine */
int main(int argc, char *argv[])
{
	FILE *fin;
    char buf[BUFSIZE];

	while (--argc > 0) {
		if ((fin = fopen(*++argv, "r")) == NULL)
			return 1;
		else {
            get(fin, 10, buf, 3);
            write(1, buf, 3);
        }
        buf[0] = '\n';
        write(1,buf,1);
        fclose(fin);
	}
	return 0;
}

/* get:  read n bytes from position pos */
int get(FILE *fp, long pos, char *buf, int n) {
    if (fseek(fp, pos, 0) == 0)  /* get to pos */
        return read(fp->fd, buf, n);
    else
        return -1;
}
int fseek(FILE *fp, long offset, int origin) {
	if (lseek(fp->fd, offset, origin) >= 0) 
		return 0;
	else
		return -1;
}
int putc(int c, FILE *p) {
	if (--(p)->cnt >= 0)
		return *(p)->ptr++ = c;
	else
		return _flushbuf(c, p);
}
int getc(FILE *p) {
	if (--(p)->cnt >= 0) 
		return (unsigned char)*(p)->ptr++;
	else 
		return _fillbuf(p);
}