#pragma once

#define ARRSZ(arr) (sizeof(arr) / sizeof(*arr))

#define SWAP(a, b, type) do {					\
	type tmp;						\
	tmp = a;						\
	a = b;							\
	b = tmp;						\
} while(0)


#define ARR_FOREACH(arr, item) \
	for (item = arr; item != arr + ARRSZ(arr) *  sizeof(*item); item++)
	