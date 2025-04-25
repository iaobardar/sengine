#include <stdlib.h>

typedef struct {
	void* data;
	size_t length;
	size_t units_alloc;
	size_t unit_size;
} general_array;

// length * unit size <= allocated;

void resize_gen_array(general_array* g, size_t new_alloc_len)
{
	g->units_alloc = new_alloc_len;

	if (g->length > g->units_alloc) g->length = g->units_alloc; // cap the length so we don't go out of bounds once shrinking.

	size_t mem_needed = g->unit_size * g->units_alloc;
	g->data = realloc(g->data, mem_needed);

	assert(g->data);
}

general_array new_gen_array(size_t unit_size, size_t num_allocate)
{
	// time for some realloc
	general_array g = {.unit_size = unit_size};
	resize_gen_array(&g, num_allocate);
	return g;
}

void free_gen_array(general_array* g)
{
	free(g->data);
}

void* at_gen_array(general_array* g, size_t i)
{
	assert(i >= 0 && i < g->length);
	return &g->data[i * g->unit_size];
}