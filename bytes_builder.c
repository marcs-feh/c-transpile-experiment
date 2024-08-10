#include "bytes_builder.h"

bool builder_init(Bytes_Builder* bb, Mem_Allocator allocator, isize initial_cap){
	bb->allocator = allocator;
	bb->data = New(byte, initial_cap, allocator);

	if(bb->data != NULL){
		bb->cap = initial_cap;
		bb->len = 0;
		return true;
	} else {
		return false;
	}
}

void builder_destroy(Bytes_Builder* bb){
	mem_free(bb->allocator, bb->data);
	bb->data = 0;
}

bool builder_push_bytes(Bytes_Builder* bb, byte* const b, isize len){
}

bool builder_resize(Bytes_Builder* bb, isize new_size){}

void builder_reset(Bytes_Builder* bb){
	mem_set(bb->data, 0, bb->len);
	bb->len = 0;
}

byte* builder_build(Bytes_Builder* bb, Mem_Allocator allocator){}

