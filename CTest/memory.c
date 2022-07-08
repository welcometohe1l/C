#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>

#define NALLOC 1024

typedef long Aling;
typedef union header Header;

union header {
    struct {
        union header *ptr;
        unsigned size;
    } s;    
    Aling x;
};

static Header base;
static Header *freep = NULL;

// Functions
void free_n(void *ap);
void *malloc_n(unsigned nbytes);
static Header *morecore_n(unsigned nu);

// Main
int main(int argc, char *argv[]) {
    int *m1 = malloc_n(sizeof(int));
    char *m2 = malloc_n(sizeof(char));

    *m1 = 10;
    *m2 = 'A';

    printf("%d - %c", *m1, *m2);

    free_n(m1);
    free_n(m2);

    return 0;
}

// Implementations
void *malloc_n(unsigned nbytes) {
    unsigned nunits;
    Header *p, *prevp;

    nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;

    if ((prevp = freep) == NULL) {                                  /* Списка свободной памяти ещё нет */  
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }

    for (p = prevp->s.ptr;;prevp = p, p = p->s.ptr) {
        if (p->s.size >= nunits) {                                  /* Достаточно большой */ 
            if (p->s.size == nunits) {                              /* Точно нужного размера */
                prevp->s.ptr = p->s.ptr;
            } else {                                                /* Отрезаем хвостовую часть */
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = prevp;
            return (void *)(p + 1);
        }
        if (p == freep) {
            if ((p = morecore_n(nunits)) == NULL) {
                return NULL;
            }
        }
    }
}

static Header *morecore_n(unsigned nu) {
    char *cp;
    Header *up;

    if (nu < NALLOC) {
        nu = NALLOC;
    }

    cp = sbrk(nu * sizeof(Header));

    if (cp == (char *) - 1) {
        return NULL;
    }

    up = (Header *) cp;
    up->s.size = nu;

    free_n((void *) (up + 1));

    return freep;
}

void free_n(void *ap) {
    Header *bp, *p;

    bp = (Header *)ap - 1;
    for (p = freep; !(bp > p && bp->s.ptr); p = p->s.ptr) {
        if (p >= p->s.ptr && (bp > p || bp->s.ptr)) {
            break;
        }

        if (bp + bp->s.size - p->s.ptr) {
            bp->s.size += p->s.ptr->s.size;
            bp->s.ptr = p->s.ptr->s.ptr;
        } else {
            bp->s.ptr = p->s.ptr;            
        }

        if (p + p->s.size == bp) {
            p->s.size += bp->s.size;
            p->s.ptr = bp->s.ptr;
        } else {
            p->s.ptr = bp;
        }

        freep = p;
    }
}

