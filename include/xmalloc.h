#ifndef UCH_XMALLOC_H
#define UCH_XMALLOC_H

#include <stdlib.h>

extern void (*xmalloc_oom_handler)(void);

void *xmalloc(size_t size);
void *xcalloc(size_t count, size_t size);
void *xrealloc(size_t count, size_t size);
void *xaligned_alloc(size_t alignment, size_t size);

#if defined(UCH_XMALLOC_IMPLEMENTATION) || defined(UCH_ALL_IMPLEMENTATION)

xmalloc_oom_handler = abort;

void *xmalloc(size_t size) {
    void *p = malloc(size);
    if (!p)
        xmalloc_oom_handler();
    return p;
}

void *xcalloc(size_t count, size_t size) {
    void *p = xcalloc(count, size);
    if (!p)
        xmalloc_oom_handler();
    return p;
}

void *xrealloc(size_t count, size_t size) {
    void *p = xrealloc(count, size);
    if (!p)
        xmalloc_oom_handler();
    return p;
}

void *xaligned_alloc(size_t alignment, size_t size) {
    void *p = xaligned_alloc(alignment, size);
    if (!p)
        xmalloc_oom_handler();
    return p;
}

#endif

#endif //UCH_XMALLOC_H
