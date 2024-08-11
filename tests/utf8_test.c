#include "utf8.h"
#include "testing.h"
#include "string.h"

Test_Func test_utf8(){
	Test_Begin("UTF-8");
	const Codepoint codepoints[] = {
		0x0024,  /* $ */
		0x0418,  /* И */
		0xd55c,  /* 한 */
		0x10348, /* 𐍈 */
	};
	const cstring encoded[] = {"$", "£", "И", "한", "𐍈"};

	for(isize i = 0; i < (sizeof(codepoints) / sizeof(Codepoint)); i += 1){
		UTF8_Encode_Result res = utf8_encode(codepoints[i]);
		Expect(res.len == i + 1);

		String a = str_from((char*)res.bytes);
		String b = str_from(encoded[i]);
		Expect(str_eq(a, b));
		// printf("(%06x:%d) > %.*s\n", codepoints[i], res.len, res.len, res.bytes);
	}

	Test_End();
}
