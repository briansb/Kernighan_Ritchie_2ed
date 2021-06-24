#include <stdio.h>
// #include <stddef.h>                    /* for NULL */

#define NALLOC 1024                    /* minimum #units to request */
#define SIZE 10
// #define LENGTH 21

typedef long Align;                    /* for alignment to long boundary */

union header {                         /* block header: */
	struct {
		union header *ptr;             /* next block if on free list */
		unsigned size;                 /* size of this block */
	} s;
	Align x;                           /* force alignment of blocks */
} temp;

typedef union header Header;

static Header base;                    /* empty list to get started */
static Header *freep = NULL;           /* start of free list */

void *GenStorAlloc(unsigned nbytes);
static Header *morecore_bb(unsigned);
void free_bb(void *);

int main(void)
{
	int *array, i;
	char *s;
	
    array = (int *)GenStorAlloc(SIZE);
	for (i = 0; i < SIZE; i++) printf("%i ", array[i]);
	printf("\n");

    s = (char *)GenStorAlloc(SIZE);
    s[4] = 'm';
    for (i = 0; i < SIZE; i++) printf("%c ", s[i]);
	printf("\n");

	array = (int *)GenStorAlloc(SIZE+10);
	for (i = 0; i < SIZE+10; i++) printf("%i ", array[i]);
	printf("\n");

	return 0;
}


/* GenStorAlloc: General-purpose Storage Allocator */
void *GenStorAlloc(unsigned nbytes)
{
	Header *p;                         /* pointer to current block */
	Header *prevp;                     /* pointer to previous block */
    Header *morecore_bb(unsigned nu);
	unsigned nunits;

	/* round up to allocate in units of sizeof(Header) */
	nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;
	if ((prevp = freep) == NULL) {     /* no free list yet */
		base.s.ptr = freep = prevp = &base;         /* point all to base */
		base.s.size = 0;
	}

	for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {    /* search free linked-list */
		if (p->s.size >= nunits) {     /* big enough */
			if (p->s.size == nunits)   /* exactly */
				prevp->s.ptr = p->s.ptr;
			else {                      /* allocate at tail-end */
				p->s.size -= nunits;
				p += p->s.size;        
				p->s.size = nunits;
			}
			freep = prevp;
			return (void *) (p + 1);
		}
		if (p == freep)                /* wrapped around free list */
			if ((p = morecore_bb(nunits)) == NULL)            /* request more memory */
				return NULL;           /* none left */
	}
}

/* morecore_bb: ask system for more memory */
static Header *morecore_bb(unsigned nu)
{
	char *cp;                          /* pointer to chunk of memory */
	char *sbrk(int);
	Header *up;

	if (nu < NALLOC)
		nu = NALLOC;
	cp = sbrk(nu * sizeof(Header));
	if (cp == (char *) -1)             /* no space at all */
		return NULL;
	up = (Header *) cp;
	up->s.size = nu;
	free_bb((void *)(up + 1));
	return freep;
}

/* free_bb: put block ap in free list */
void free_bb(void *ap)
{
	Header *bp, *p;

	bp = (Header *) ap - 1;            /* point to block header */
	for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
		if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
			break;                     /* free block at start or end of arena */

	if (bp + bp->s.size == p->s.ptr) { /* join to upper nbr */
		bp->s.size += p->s.ptr->s.size;
		bp->s.ptr = p->s.ptr->s.ptr;
	} else
		bp->s.ptr = p->s.ptr;
	if (p + p->s.size == bp) {          /* join to lower nbr */
		p->s.size += bp->s.size;
		p->s.ptr = bp->s.ptr;
	} else
		p->s.ptr = bp;
	freep = p;
}
