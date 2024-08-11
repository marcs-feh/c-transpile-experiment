#include <stdio.h>
#include "prelude.h"
#include "allocator.h"
#include "heap_allocator.h"
#include "arena.h"

#define KiB (isize)1024
#define MiB (isize)1024 * KiB

static byte MAIN_MEM[8 * MiB];
static byte TEMP_MEM[1 * MiB];

int main(){
	// Main allocator
	// Mem_Arena main_arena;
	// arena_init(&main_arena, MAIN_MEM, sizeof(MAIN_MEM));
	Mem_Allocator allocator = heap_allocator();

	// Temporary allocator
	Mem_Arena temp_arena;
	arena_init(&temp_arena, TEMP_MEM, sizeof(TEMP_MEM));
	Mem_Allocator temp_allocator = arena_allocator(&temp_arena);
}

