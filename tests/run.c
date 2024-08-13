#include "testing.h"

// #include all your test files here.
#include "bytes_buffer_test.c"
#include "utf8_test.c"

int main(){
	// Run all your tests
	test_bytes_buffer();
	test_utf8();
}
