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

bool builder_push_bytes(Bytes_Builder* bb, byte* const bytes, isize len){
	if(bb->len + len > bb->cap){
		bool status = builder_resize(bb, bb->cap * 2);
		if(!status){ return false; }
	}
	mem_copy(&bb->data[bb->len], bytes, len);
	return true;
}

bool builder_resize(Bytes_Builder* bb, isize new_size){
	byte* new_data = New(byte, new_size, bb->allocator);
	if(new_data == NULL){ return false; }

	mem_copy(new_data, bb->data, Min(new_size, bb->len));
	mem_free(bb->allocator, bb->data);
	bb->data = new_data;
	bb->cap = new_size;

	return true;
}

void builder_reset(Bytes_Builder* bb){
	bb->len = 0;
	mem_set(bb->data, 0, bb->cap);
}

byte* builder_build(Bytes_Builder* bb, Mem_Allocator allocator){
	byte* buf = New(byte, bb->len, allocator);
	if(buf == NULL){ return NULL; }
	builder_reset(bb);
	return buf;
}

