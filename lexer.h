#pragma once

#include "prelude.h"
#include "string.h"
// #include "allocator.h"

enum TokenKind {
	Tk_Identifier = 0,
	Tk_Integer,

	Tk_Paren_Open,
	Tk_Paren_Close,
	Tk_Square_Open,
	Tk_Square_Close,
	Tk_Curly_Open,
	Tk_Curly_Close,

	Tk_Equal,
	Tk_Dot,
	Tk_Comma,
	Tk_Semicolon,
	Tk_Colon,

	Tk_Plus,
	Tk_Minus,
	Tk_Star,
	Tk_Slash,
	Tk_Modulo,

	Tk_Greater, Tk_Less,
	Tk_Greater_Equal, Tk_Less_Equal,
	Tk_Equal_Equal, Tk_Not_Equal,

	Tk_Bit_And,
	Tk_Bit_Or,
	Tk_Bit_Xor,
	Tk_Shift_Left,
	Tk_Shift_Right,

	Tk_And,
	Tk_Or,
	Tk_Not,

	Tk_End_Of_File = -1,
	Tk_Error = -2,
};

typedef struct {
	enum TokenKind kind;
	String lexeme;
} Token;

typedef struct {
	isize current;
	isize previous;
	String source;

	Mem_Allocator scratch_alloc;
} Lexer;

// Get next token
Token lexer_next(Lexer* lex);

// Initialize lexer
void lexer_init(Lexer* lex, String source);

