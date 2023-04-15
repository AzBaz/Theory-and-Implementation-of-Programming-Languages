/*********************************************************************
  Name: Azim Bazarov           NetID: ab4908
  Course: CSE 4714              
  Lab: 02 - Part 1 
  Purpose of File: Using flex programming laguage to generate lexical analyzer with given table of tokens

*******************************************************************/
%option yylineno
%option noyywrap
%{
#include "lexer.h"

// declare global variables for current line number to read
int line_number = 1;

%}

/*writing given table of tokens*/
%%

"BEGIN"       { return TOK_BEGIN; }
"BREAK"       { return TOK_BREAK; }
"CONTINUE"    { return TOK_CONTINUE; }
"ELSE"      { return TOK_ELSE; }
"END"       { return TOK_END; }
"FOR"       { return TOK_FOR; }
"IF"      { return TOK_IF; }
"LET"       { return TOK_LET; }
"PROGRAM"       { return TOK_PROGRAM; }
"READ"      { return TOK_READ; }
"THEN"      { return TOK_THEN; }
"TO"      { return TOK_TO; }
"VAR"       { return TOK_VAR; }
"WHILE"       { return TOK_WHILE; }
"WRITE"       { return TOK_WRITE; }
"DOWNTO"      {return TOK_DOWNTO; }

"INTEGER"       { return TOK_INTEGER; }
"REAL"      { return TOK_REAL; }

;       {return TOK_SEMICOLON; }
:       {return TOK_COLON; } 
\)      { return TOK_CLOSEPAREN; }
\(      { return TOK_OPENPAREN; }
"{"       { return TOK_OPENBRACE; }
"}"       { return TOK_CLOSEBRACE; }

\+      {return TOK_PLUS; }
\-      {return TOK_MINUS; }
\*      { return TOK_MULTIPLY; }
\/      { return TOK_DIVIDE; }
\:\=      { return TOK_ASSIGN; }
\=      {return TOK_EQUALTO; }
\<      { return TOK_LESSTHAN; }
\>      { return TOK_GREATERTHAN; }
\<\>      { return TOK_NOTEQUALTO;}; 
"MOD"       { return TOK_MOD; }
"NOT"       { return TOK_NOT; }
"OR"      { return TOK_OR; }
"AND"       { return TOK_AND; }

[A-Z][0-9A-Z]* { if ( strlen(yytext) <= 8  ) { return TOK_IDENT; } else { return TOK_UNKNOWN; } }
[0-9]+ { return TOK_INTLIT; }
[0-9]+\.[0-9]+  { return TOK_FLOATLIT; }
\'[^\n']*\' { if ( strlen(yytext) <= 80  ) { return TOK_STRINGLIT; } else { return TOK_UNKNOWN; } }
 

 /* line count */
\n        { line_number++; }

 /* omit whitespace*/
[ \t\r]+

.         { return TOK_UNKNOWN; }

 /* define EOF */
<<EOF>>   { return TOK_EOF; }
%%
