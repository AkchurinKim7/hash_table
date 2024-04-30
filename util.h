#pragma once

void *xmalloc(size_t sz);

void* xrealloc(void *ptr, size_t size);

void xfree(void *ptr);

void xerror(int rc, char *fmt, ...);