#include "testing.h"
#include "string.h"
#include "heap_allocator.h"
#include "bytes_builder.h"

Test_Func test_bytes_builder(){
	Test_Begin("Bytes Builder");
	Bytes_Builder bb;
	builder_init(&bb, heap_allocator(), 64);
	Expect(bb.cap == 64 && bb.len == 0 && bb.data != NULL);

	String msg1 = str_from("Hello, World!");
	Expect(builder_push_bytes(&bb, msg1.data, msg1.len));

	String tmp = str_from_bytes(bb.data, bb.len);
	// printf("[%ld] %*.s\n", tmp.len, (int)tmp.len, tmp.data);
	Expect(str_eq(msg1, tmp));

	String msg2 = str_from(" It's the builder");
	builder_push_bytes(&bb, msg2.data, msg2.len);

	String res = str_concat(msg1, msg2, heap_allocator());
	Expect(str_eq(res, str_from_bytes(bb.data, bb.len)));

	builder_destroy(&bb);
	Test_End();
}
