#pragma once

#include <stdio.h>
#include <stdlib.h>

static
void debug_assert(int pred, char* const msg){
	#ifdef NDEBUG
		(void)pred; (void)msg;
	#else
	if(!pred){
		fprintf(stderr, "Failed assert: %s\n", msg);
		abort();
	}
	#endif
}

