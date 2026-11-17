#include "types.h"
#include <unistd.h>
#include <stdint.h>
#include <limits.h>

#define NALOC 1024

void *_malloc(unsigned nbytes);
void _free(void *ap);
static Header *morecore(unsigned nu);

static Header base;
static Header *freep = NULL;

void *_calloc(unsigned num, unsigned size)
{
	if(size != 0 && num > UINT_MAX/size)
		return NULL;

	unsigned total =  num*size;
	char *mem =  (char *) _malloc(total);

	if(mem == NULL)
		return NULL;
	char *p = mem;

	for(unsigned i = 0; i < total; i++)
		*p++ = 0;

	return mem;
}

void *_malloc(unsigned nbytes)
{
	if(nbytes > MAX_ALLOC)
		return NULL;
	if(nbytes == 0)
		return NULL;

	Header *p, *prevp;
	Header *moreroce(unsigned);
	unsigned nunits;

	nunits = (nbytes + sizeof(Header)-1)/sizeof(Header)+1;
	
	if((prevp = freep) == NULL) {
		base.s.ptr = freep = prevp = &base;
		base.s.size = 0;
	}	
	for(p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
		if(p->s.size >= nunits) {
			if(p->s.size == nunits) 
				prevp->s.ptr = p->s.ptr;
			else {
				p->s.size -= nunits;
				p += p->s.size;
				p->s.size = nunits;
			}
			freep = prevp;
			p->s.is_free = 0;
			return (void*) (p+1);
		}
		if(p == freep)
			if((p = morecore(nunits)) == NULL)
				return NULL;
	}
}

void bfree(void* p, unsigned n)
{
	if(p == NULL)
		return;
	if(n == 0)
		return;
	if(n < (sizeof(Header)*2))
		return;

	Header *ap = (Header*) p;

	if((uintptr_t) ap % _Alignof(Header) != 0)
		return;

	ap->s.size = n/sizeof(Header);
       	ap->s.is_free = 0;

 	if (freep == NULL) {
        	base.s.ptr = freep = &base;
        	base.s.size = 0;
    	}	


	_free(ap+1);	

}


void _free(void *ap)
{
	if(ap == NULL)
		return;

	Header *bp, *p;
	bp = (Header *)ap - 1;

	if((uintptr_t) bp % _Alignof(Header) != 0)
		return;
	
	if(bp->s.size == 0 || bp->s.is_free == 1)
		return;

	for(p = freep; !(bp>p && bp < p->s.ptr); p = p->s.ptr)
		if(p >= p->s.ptr && (bp > p || bp < p->s.ptr))
			break;

	Header* block = bp;

	if(bp + bp->s.size == p->s.ptr) {
		bp->s.size += p->s.ptr->s.size;
		bp->s.ptr  = p->s.ptr->s.ptr;
	} else 
		bp->s.ptr = p->s.ptr;
	if(p + p->s.size == bp) {
		p->s.size += bp->s.size;
		p->s.ptr  =  bp->s.ptr; 
	} else 
		p->s.ptr = bp;
	block->s.is_free = 1;
	freep = p;
}

static Header *morecore(unsigned nu) 
{
	char *cp;
	Header *up;

	if(nu <  NALOC) 
		nu = NALOC;
	cp = sbrk(nu*sizeof(Header));
	if(cp == (char*) -1)
		return NULL;

	up = (Header *) cp;
	up->s.size = nu;
	up->s.is_free = 0;
	_free((void*) (up+1));
	return freep;
}
