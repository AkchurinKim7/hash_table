#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void *
xmalloc(size_t sz)
{
	void *res;
	res = malloc(sz);
	if (sz != 0 && res == NULL) {
		perror("malloc()");
		exit(EXIT_FAILURE);
	}
	return res;

}

void*
xrealloc(void *ptr, size_t size)
{
	void *res;

	res = realloc(ptr, size);
	if (size != 0 && res == NULL) {
		perror("realloc()");
		exit(EXIT_FAILURE);
	}

	return res;
}

void
xfree(void *ptr)
{
	if (ptr)
		free(ptr);
}

void
xerror(int rc, char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);

	exit(rc);
}