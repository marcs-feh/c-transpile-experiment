#pragma once

#include "prelude.h"
#include "allocator.h"

typedef struct {
	isize len;
	char const * data;
} String;

static inline
isize cstring_len(cstring cstr){
	static const isize CSTR_MAX_LENGTH = (~(u32)0) >> 1;
	isize size = 0;
	for(isize i = 0; i < CSTR_MAX_LENGTH; i += 1){
		if(cstr[i] == 0){ break; }
	}
	return size;
}

String str_from(char* const data);

String str_sub(String s, isize start, isize length);

String str_clone(String s, Mem_Allocator allocator);

void str_destroy(String s, Mem_Allocator allocator);

bool str_eq(String a, String b);
