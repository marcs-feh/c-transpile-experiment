#pragma once

#include "prelude.h"
#include "string.h"
// #include "allocator.h"

enum TokenKind {
	Tk_Unkown = 0,

	Tk_Paren_Open,
	Tk_Paren_Close,
	Tk_Square_Open,
	Tk_Square_Close,
	Tk_Curly_Open,
	Tk_Curly_Close,

	Tk_Dot, Tk_Comma,
	Tk_Semicolon, Tk_Colon,

	Tk_Plus,
	Tk_Minus,
	Tk_Star,
	Tk_Slash,
	Tk_Modulo,

	Tk_Bit_And,
	Tk_Bit_Or,
	Tk_Bit_Xor,
	Tk_Shift_Left,
	Tk_Shift_Right,

	Tk_Identifier,
	Tk_Integer,
};

typedef struct {
	enum TokenKind kind;
	String lexeme;
} Token;

typedef struct {

} Lexer;
