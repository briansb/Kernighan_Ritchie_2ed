/**** FILE structure ****/
#define NULL 0
#define EOF (-1)
#define BUFSIZE 1024
#define OPEN_MAX 20		/* max files open at once */

typedef struct _iobuf {
	int cnt;			/* characters left */
	char *ptr;			/* next character position */
	char *base;			/* location of buffer */
	int flag;			/* mode of file access */
	int fd;				/* file descriptor */
} FILE;
extern FILE _iob[OPEN_MAX];

#define stdin (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

enum flags { _READ = 01, _WRITE = 02, _UNBUF = 04, _EOF = 010, _ERR = 020 };

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

#define feof(p) (((p)->flag & _EOF) != 0)
#define ferror(p) (((p)->flag & _ERR) != 0)
#define fileno(p) ((p)->fd)

#define getc(p) (--(p)->cnt >= 0 ? (unsigned char)*(p)->ptr++ : _fillbuf(p))
#define putc(x, p) (--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuf((x), p))

#define getchar() getc(stdin)
#define putchar(x) putc(x, stdout)


/**** fopen ****/
#include <fcntl.h>
#include <unistd.h>
#define PERMS 0666
/* fopen:  open file, return file ptr */
FILE *fopen(char *name, char *mode)
{
	int fd;
	FILE *fp;

	if (*mode != 'r' && *mode != 'w' && *mode != 'a')
		return NULL;
	for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
		if ((fp->flag & (_READ | _WRITE)) == 0)
			break;
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
	fp->flag = (*mode == 'r') ? _READ : _WRITE;
	return fp;
}


/**** _fillbuf ****/
#include <stdlib.h>
/* _fillbuf:  allocate and fill input buffer */
int _fillbuf(FILE *fp)
{
	int bufsize;

	if ((fp->flag & (_READ | _EOF | _ERR)) != _READ)
		return EOF;
	bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZE;
	if (fp->base == NULL)		/* no buffer yet */
		if ((fp->base = (char *)malloc(bufsize)) == NULL)
			return EOF;			/* can't get buffer */
	fp->ptr = fp->base;
	fp->cnt = read(fp->fd, fp->ptr, bufsize);
	if (--fp->cnt < 0) {
		if (fp->cnt == -1)
			fp->flag |= _EOF;
		else
			fp->flag |= _ERR;
		fp->cnt = 0;
		return EOF;
	}
	return (unsigned char)*fp->ptr++;
}

/**** stdin, stdout, stderr ****/
FILE _iob[OPEN_MAX] = { { 0, (char *)0, (char *)0, _READ, 0 }, /* stdin, stdout, stderr */
			{ 0, (char *)0, (char *)0, _WRITE, 1 },
			{ 0, (char *)0, (char *)0, _WRITE | _UNBUF, 2 } };


/* main routine */
int main(int argc, char *argv[])
{
	FILE *fp;
	char buf[1];

	while (--argc > 0) {
		if ((fp = fopen(*++argv, "r")) == NULL)
			return 1;
		else
			while ((buf[0] = getc(fp)) != EOF)
				write(1, buf, 1);
		buf[0] = '\n';
		write(1, buf, 1);
	}
	return 0;
}
