#include <stdio.h>
#include <assert.h>
#include "sstring.h"

typedef sstring sstringview;

sstringview sv_cstr(char* cstr)
{
	sstringview out = {.data = cstr, .length = 0};
	while (out.data[out.length]) ++out.length;
	return out;
}

sstringview sv_ss(sstring* str, size_t i, size_t len)
{
	assert(i >= 0 && i < str->length);
	assert(len >= 0 && i + len <= str->length);
	sstringview sv = {.data = str->data + i, .length = len};
	return sv; 
}

char ssat(sstring* str, size_t i)
{
	assert(i >= 0 || i < str->length);
	return str->data[i];
}

size_t ssfind(sstring* sample, sstring* input, size_t start_index)
{
	for (size_t i = start_index; i < input->length - sample->length + 1; ++i)
	{
		int matching = 1;
		for (size_t ii = 0; ii < sample->length && matching; ++ii)
			matching = ssat(input, i + ii) == ssat(sample, ii);
		if (matching) return i;
	}
	return input->length;
}

void putss(sstring* str)
{
	fwrite(str->data, 1, str->length, stdout);
	putc('\n', stdout);
}