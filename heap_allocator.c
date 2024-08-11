#include "heap_allocator.h"

static
void* heap_alloc(isize nbytes, isize align){
	void* data = malloc(nbytes);
	uintptr aligned = align_forward_ptr((uintptr)data, (uintptr)align);
	if(aligned == (uintptr)data){
		return data;
	} else {
		debug_assert(false, "Could not allocate memory with proper alignment");
		free(data);
		return NULL;
	}
}

static
void* heap_allocator_func(
	void* impl,
	enum Allocator_Op op,
	void* old_ptr,
	isize size, isize align,
	i32* capabilities
){
	(void)impl;

	switch(op){
		case Mem_Op_Alloc: {
			return heap_alloc(size, align);
		} break;

		case Mem_Op_Free: {
			free(old_ptr);
		} break;

		case Mem_Op_Resize: {} break;

		case Mem_Op_Free_All: {} break;

		case Mem_Op_Query: {
			*capabilities = Mem_Op_Alloc | Mem_Op_Free;
		} break;
	}

	return NULL;
}

Mem_Allocator heap_allocator(){
	return (Mem_Allocator){
		.func = heap_allocator_func,
		.data = NULL,
	};
}
