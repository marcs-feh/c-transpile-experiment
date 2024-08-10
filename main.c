#include <stdio.h>
#include "prelude.h"
#include "allocator.h"
#include "arena.h"

static byte MAIN_MEM[64];

int main(){
	Mem_Arena arena;
	arena_init(&arena, MAIN_MEM, sizeof(MAIN_MEM));
	Mem_Allocator allocator = arena_allocator(&arena);
}

