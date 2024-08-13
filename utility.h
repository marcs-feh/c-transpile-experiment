#pragma once

#include "prelude.h"
#include "string.h"
#include "lexer.h"
#include "bytes_buffer.h"

void print_bytes(byte const* buf, isize count);

String format_tokens(Mem_Allocator allocator, Token* tokens, isize count);

/* Implementation */
#ifdef UTILITY_IMPL

#define MAX_TOKEN_LEN 512

void print_bytes(byte const* buf, isize count){
	printf("> ");
	for(isize i = 0; i < count; i += 1){
		printf("(%c) %02x ", buf[i], buf[i]);
	}
	printf("\n");
}

static const cstring TOKEN_MAP[] = {
	[Tk_Paren_Open]   = "(",
	[Tk_Paren_Close]  = ")",
	[Tk_Square_Open]  = "[",
	[Tk_Square_Close] = "]",
	[Tk_Curly_Open]   = "{",
	[Tk_Curly_Close]  = "}",

	[Tk_Equal]     = "=",
	[Tk_Dot]       = ".",
	[Tk_Comma]     = ",",
	[Tk_Semicolon] = ";",
	[Tk_Colon]     = ":",

	[Tk_Plus]   = "+",
	[Tk_Minus]  = "-",
	[Tk_Star]   = "*",
	[Tk_Slash]  = "/",
	[Tk_Modulo] = "%",

	[Tk_Greater]       = ">",
	[Tk_Less]          = "<",
	[Tk_Greater_Equal] = ">=",
	[Tk_Less_Equal]    = "<=",
	[Tk_Equal_Equal]   = "==",
	[Tk_Not_Equal]     = "!=",

	[Tk_Bit_And]     = "&",
	[Tk_Bit_Or]      = "|",
	[Tk_Bit_Xor]     = "~",
	[Tk_Shift_Left]  = "<<",
	[Tk_Shift_Right] = ">>",

	[Tk_And] = "&&",
	[Tk_Or]  = "||",
	[Tk_Not] = "!",

	[Tk__last] = 0, /* Padding */
};


String format_tokens(Mem_Allocator allocator, Token* tokens, isize count){
	String s = {0};
	if(count == 0){ return s; }

	Bytes_Buffer buf;
	if(!buffer_init(&buf, allocator, MAX_TOKEN_LEN)){ return s; }

	for(isize i = 0; i < count; i += 1){
		Token tk = tokens[i];
		if(buffer_remaining(&buf) <= MAX_TOKEN_LEN){
			if(!buffer_resize(&buf, buf.cap + MAX_TOKEN_LEN)){ return s; }
		}

		int n = 0;
		if(tk.kind == Tk_Identifier){
			n = snprintf((char*) &buffer_bytes(&buf)[buf.len], buffer_remaining(&buf), "Id(%.*s) ", FMT_STRING(tk.lexeme));
		}
		else if(tk.kind == Tk_Integer){
			n = snprintf((char*) &buffer_bytes(&buf)[buf.len], buffer_remaining(&buf), "Int(%ld) ", tk.payload.integer);
		}
		else if(tk.kind == Tk_String){
			n = snprintf((char*) &buffer_bytes(&buf)[buf.len], buffer_remaining(&buf), "String(%.*s) ", FMT_STRING(tk.payload.string));
		}
		else if(TOKEN_MAP[tk.kind]){
			n = snprintf((char*) &buffer_bytes(&buf)[buf.len], buffer_remaining(&buf), "%s ", TOKEN_MAP[tk.kind]);
		}
		buf.len += n;

		// printf("Wrote %d. (last:%d len:%d)\n", n, buf.last_read, buf.len);
		print_bytes(buffer_bytes(&buf), buf.len);
	}

	if(!buffer_resize(&buf, buf.len + 1)){ return s; }
	s = str_from_bytes(buffer_bytes(&buf), buf.len);
	return s;
}
#endif

