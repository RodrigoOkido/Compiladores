%{
	#include "tokens.h"
	#include "hash.h"

	int lineNumber = 1;
	int running = 1;

%}

%x COMMENT

%%
"char"		{ return KW_CHAR; }
"int"		{ return KW_INT; }
"float"		{ return KW_FLOAT; }
"if"		{ return KW_IF; }
"then"	{ return KW_THEN; }
"else"		{ return KW_ELSE; }
"while"		{ return KW_WHILE; }
"for"		{ return KW_FOR; }
"read"		{ return KW_READ; }
"return"		{ return KW_RETURN; }
"print"		{ return KW_PRINT; }



"<="		{ return OPERATOR_LE; }
">="		{ return OPERATOR_GE; }
"=="		{ return OPERATOR_EQ; }
"!="		{ return OPERATOR_NE; }
"&&"		{ return OPERATOR_AND; }
"\|\|"		{ return OPERATOR_OR; }



[A-Za-z_][A-Za-z_0-9]*	{ hashInsert(TK_IDENTIFIER, yytext); return TK_IDENTIFIER; }
[0-9]+						      { hashInsert(LIT_INTEGER,yytext); return LIT_INTEGER; }
[0-9]+\.[0-9]+					{ hashInsert(LIT_REAL,yytext); return LIT_REAL; }
"'"[a-zA-Z0-9]"'"				{ hashInsert(LIT_CHAR,yytext); return LIT_CHAR; }
\"(\\.|[^\\"])*\"				{ hashInsert(LIT_STRING,yytext); return LIT_STRING; }
[,;:(){}+-/<>=!&$#]			{ return yytext[0]; }
"["								      { return yytext[0]; }
"]"								      { return yytext[0]; }
"*"								      { return yytext[0]; }


"\n"						  { ++lineNumber; }
"//".*
"/*"						  {BEGIN(COMMENT); }

[ \t\r]+

.				          { return TOKEN_ERROR; }

<COMMENT>"\n"		  { ++lineNumber; }
<COMMENT>"*/"		  { BEGIN(INITIAL); }
<COMMENT>.


%%

int getLineNumber() {
	return lineNumber;
}

void initMe() {
	running = 1;
	hashInit();
}

int isRunning() {
	return running;
}

int yywrap(void) {
	running = 0;
	return 1;
}
