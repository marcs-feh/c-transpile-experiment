#include "string.h"

static const String EMPTY = {0};

String str_from(cstring data){
	String s = {
		.data = data,
		.len = cstring_len(data),
	};
	return s;
}

String str_from_range(cstring data, isize start, isize length){
	String s = {
		.data = &data[start],
		.len = length,
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
	return (String){
		.data = mem,
		.len = s.len,
	};
}

bool str_eq(String a, String b){
	if(a.len != b.len){ return false; }

	for(isize i = 0; i < a.len; i += 1){
		if(a.data[i] != b.data[i]){ return false; }
	}

	return true;
}

void str_destroy(String s, Mem_Allocator allocator){
	mem_free(allocator, s.data);
}
