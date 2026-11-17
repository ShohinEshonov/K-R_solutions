#ifndef TYPES_H
#define TYPES_H
typedef long Align;

union header { 
	struct {
		union header *ptr;
		unsigned size;	
		unsigned is_free : 1;
	} s;
	Align x;
};

typedef union header Header;

#ifndef MAX_ALLOC
#define MAX_ALLOC 4096
#endif

#endif
