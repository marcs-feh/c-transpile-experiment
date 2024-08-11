#include "lexer.h"
#include "assert.h"

#define Op_Token(K_) \
	(Token){ \
		.kind = (K_), \
		.lexeme = {0}, \
	}

static
char lexer_consume(Lexer* lex){
	if(lex->current >= lex->source.len){
		return 0;
	}
	lex->current += 1;
	return lex->source.data[lex->current - 1];
}

static
char lexer_peek(Lexer* lex, isize delta){
	if(lex->current + delta >= lex->source.len || lex->current + delta < 0){
		return 0;
	}
	return lex->source.data[lex->current + delta];
}

// Consume next char if it matches, returns 0 if not matched
static
char lexer_consume_matching(Lexer* lex, char c){
	if(lexer_peek(lex, 0) == c){
		lexer_consume(lex);
		return c;
	}
	return 0;
}

// Get next token
Token lexer_next(Lexer* lex){
	Token tk = { .kind = Tk_End_Of_File };

	char c = lexer_consume(lex);
	if(c == 0){ return tk; }

	switch(c){
		case '.': tk = Op_Token(Tk_Dot); break;
		case ':': tk = Op_Token(Tk_Colon); break;
		case ';': tk = Op_Token(Tk_Semicolon); break;
		case ',': tk = Op_Token(Tk_Comma); break;

		case '+': tk = Op_Token(Tk_Plus); break;
		case '-': tk = Op_Token(Tk_Minus); break;
		case '*': tk = Op_Token(Tk_Star); break;
		case '/': tk = Op_Token(Tk_Slash); break;
		case '%': tk = Op_Token(Tk_Modulo); break;

		case '&': tk = Op_Token(Tk_Plus); break;
		case '|': tk = Op_Token(Tk_Plus); break;
		case '~': tk = Op_Token(Tk_Plus); break;

		case '>': {
			if(lexer_consume_matching(lex, '>')){
				tk = Op_Token(Tk_Shift_Right);
			} else if(lexer_consume_matching(lex, '=')){
				tk = Op_Token(Tk_Greater_Equal);
			} else {
				tk = Op_Token(Tk_Greater);
			}
		} break;

		case '<': {
			if(lexer_consume_matching(lex, '<')){
				tk = Op_Token(Tk_Shift_Left);
			} else if(lexer_consume_matching(lex, '=')){
				tk = Op_Token(Tk_Less_Equal);
			} else {
				tk = Op_Token(Tk_Less);
			}
		} break;

		default:
			panic("Bruh");
		break;
	}

	return tk;
}

// Initialize lexer
void lexer_init(Lexer* lex, String source){
	lex->source   = source;
	lex->current  = 0;
	lex->previous = 0;
}

