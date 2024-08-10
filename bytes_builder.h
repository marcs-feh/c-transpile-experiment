#pragma once

#include "prelude.h"
#include "allocator.h"

typedef struct {
	byte* data;
	isize cap;
	isize len;
	Mem_Allocator allocator;
} Bytes_Builder;

// Init a builder with a capacity, returns success status
bool builder_init(Bytes_Builder* bb, Mem_Allocator allocator, isize initial_cap);

// Destroy a builder
void builder_destroy(Bytes_Builder* bb);

// Push bytes to the end of builder, returns success status
bool builder_push_bytes(Bytes_Builder* bb, byte* const b, isize len);

// Resize builder to have specified capacity, returns success status.
bool builder_resize(Bytes_Builder* bb, isize new_size);

// Resets builder's data, does not de-allocate
void builder_reset(Bytes_Builder* bb);

// Clone builder's current data using provided allocator, then reset. Returns
// NULL on allocation failure and keeps builder as-is.
byte* builder_build(Bytes_Builder* bb, Mem_Allocator allocator);

