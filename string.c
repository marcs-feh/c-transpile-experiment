#include "string.h"

static const String EMPTY = {0};

String str_from(char* const data, isize len){
	String s = {
		.data = data,
		.len = data != NULL ? len : 0,
	};
	return s;
}

String str_sub(String s, isize start, isize length){
	if(start >= s.len || start < 0 || start + length > s.len){ return EMPTY; }

	String sub = {
		.data = &s.data[start],
		.len = length,
	};

	return sub;
}

String str_clone(String s, Mem_Allocator allocator){
	char* mem = New(char, s.len, allocator);
	if(mem == NULL){ return EMPTY; }
	return str_from(mem, s.len);
}

void str_destroy(String s, Mem_Allocator allocator){
	mem_free(allocator, s.data);
}
