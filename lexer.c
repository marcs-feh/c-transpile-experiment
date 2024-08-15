#include "lexer.h"
#include "assert.h"
#include "bytes_buffer.h"

#define Op_Token(K_) \
	(Token){ \
		.kind = (K_), \
		.lexeme = {0}, \
	}

#include "lexer_tokens.c.table"

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

static
bool is_binary(char c){
	return c == '0' || c == '1';
}

static
bool is_octal(char c){
	return c >= '0' && c <= '7';
}

static
bool is_decimal(char c){
	return c >= '0' && c <= '9';
}

static
bool is_hexadecimal(char c){
	return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
}

static
Token consume_number(Lexer* lex){
	Token tk = { .kind = Tk_Error };
	Bytes_Buffer buf;
	bool ok = buffer_init(&buf, lex->scratch_alloc, 64);
	if(!ok){ return tk; }

	unimplemented();

	return tk;
}

// Get next token
Token lexer_next(Lexer* lex){
	Token tk = { .kind = Tk_End_Of_File };
	i32 key = 0;

	char c = lexer_consume(lex);
	if(c == 0){ return tk; }

	/* Tokens 1 */ {
		key = (i32)c;
		tk.kind = tokens1_lookup(key);
		if(tk.kind > 0){ // One byte token
			return tk;
		}
	}

	/* Tokens 2 */ {
		i32 buf[2] = {c, lexer_peek(lex, 0)};
		key = (buf[0] << 8) | buf[1];
		tk.kind = tokens2_lookup(key);

		if(tk.kind > 0){ // Two byte token
			lex->current += 1;
			return tk;
		}

		// Ignore 2nd char and try again
		key = buf[0] << 8;
		tk.kind = tokens2_lookup(key);
		if(tk.kind > 0){ // One byte token
			return tk;
		}
	}

	tk.kind = Tk_Error;
	return tk;
}


// Initialize lexer
void lexer_init(Lexer* lex, String source){
	lex->source   = source;
	lex->current  = 0;
	lex->previous = 0;
}

