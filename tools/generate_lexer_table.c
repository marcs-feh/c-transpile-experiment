// Code generation utility
// Compile and run this from the project root with:
// cc -I. -o gen-table && ./gen-table

#define OUTPUT_FILE "lexer_tokens.c.table"
#include "lexer.h"
#include <stdio.h>

static const byte TOKENS1[][1] = {
	[Tk_Paren_Open] = "(",
	[Tk_Paren_Close] = ")",
	[Tk_Square_Open] = "[",
	[Tk_Square_Close] = "]",
	[Tk_Curly_Open] = "{",
	[Tk_Curly_Close] = "}",

	[Tk_Dot] = ".",
	[Tk_Comma] = ",",
	[Tk_Semicolon] = ";",
	[Tk_Colon] = ":",

	[Tk_Bit_Xor] = "~",
};

static const byte TOKENS2[][2] = {
	[Tk_Greater] = ">",
	[Tk_Less] = "<",
	[Tk_Equal] = "=",
	[Tk_Not] = "!",

	[Tk_Not_Equal] = "!=",
	[Tk_Greater_Equal] = ">=",
	[Tk_Less_Equal] = "<=",
	[Tk_Equal_Equal] = "==",
	[Tk_Shift_Left] = "<<",
	[Tk_Shift_Right] = ">>",
	[Tk_Arrow] = "->",

	[Tk_Plus] = "+",
	[Tk_Minus] = "-",
	[Tk_Star] = "*",
	[Tk_Slash] = "/",
	[Tk_Modulo] = "%",

	[Tk_Bit_And] = "&",
	[Tk_Bit_Or] = "|",

	[Tk_And] = "&&",
	[Tk_Or] = "||",

	[Tk__last] = 0,
};

int main(){
	FILE* f = fopen(OUTPUT_FILE, "wb");
	if(f == NULL){
		printf("failed to open file"); abort();
	}
	int written = 0;

	token1: {
		enum TokenKind tk1[0xff];
		for(isize i = 0; i < Tk__last; i += 1){
			i32 key = (i32)TOKENS1[i][0];
			tk1[i] = key;
		}
		written += fprintf(f, "static i32 tokens1_lookup(i32 key){\n");
		written += fprintf(f, "\tswitch(key){\n");
		for(i32 i = 0; i < Tk__last; i += 1){
			if(tk1[i] != 0){
				written += fprintf(f, "\tcase 0x%04x: return %d; /* %.1s */\n", tk1[i], i, TOKENS1[i]);
			}
		}
		written += fprintf(f, "\tdefault: return -1;\n");
		written += fprintf(f, "\t}\n");
		written += fprintf(f, "}\n");
	}

	token2: {
		enum TokenKind tk2[0xff];
		for(isize i = 0; i < Tk__last; i += 1){
			i32 key = 0;
			key |= (i32)(TOKENS2[i][0]) << 8;
			key |= (i32)(TOKENS2[i][1]);
			tk2[i] = key;
		}

		written += fprintf(f, "static i32 tokens2_lookup(i32 key){\n");
		written += fprintf(f, "\tswitch(key){\n");
		for(i32 i = 0; i < Tk__last; i += 1){
			if(tk2[i] != 0){
				written += fprintf(f, "\tcase 0x%04x: return %d; /* %.2s */\n", tk2[i], i, TOKENS2[i]);
			}
		}
		written += fprintf(f, "\tdefault: return -1;\n");
		written += fprintf(f, "\t}\n");
		written += fprintf(f, "}\n");
	}

	printf("Wrote %dB to %s\n", written, OUTPUT_FILE);
	fclose(f);
}
