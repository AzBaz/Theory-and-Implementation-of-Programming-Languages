/*********************************************************************
 Azim Bazarov
 ab4908
 Project: Part 2
 Purpose of File: Creating recursive descent parser for a subset of Ten Instruction Pascal Subset (TIPS). For this code we use corrected
rules.l from Part 1 for the lexical analyzer.
*******************************************************************/

#ifndef PRODUCTIONS_H
#define PRODUCTIONS_H

#include <iostream>

extern set<string> symbolTable;
int nextToken = 0;  // token returned from yylex
int level = 0;  // used to indent output to approximate parse tree


extern "C"
{
	// Instantiate global variables used by flex
	extern char* yytext;       // text of current lexeme
	extern int   yylex();      // the generated lexical analyzer
}

// Forward declarations of production parsing functions
void program();
void Block();
void Statement();
void Assignment();
void Compound();
void If();
void While();
void Read();
void Write();
void Expression();
void SimpleExpression();
void Term();
void Factor();
bool hasIdent();
bool hasSemicolon();
bool hasColon();
bool hasIntegerOrReal();
bool hasAssign();
bool hasEnd();
bool hasThen();
bool hasOpenParen();
bool hasCloseParen();
bool hasStringLit();

// Forward declarations of functions that check whether the current token is
// in the first set of a production rule
bool first_of_program();
bool first_of_block();
bool first_of_statement();
bool first_of_assignment();
bool first_of_compound();
bool first_of_simpleExpression();
bool first_of_term();
bool first_of_factor();

//functions in depth
bool symbolExists(string yytext)
{
    set<string>::iterator it;
    for (it = symbolTable.begin(); it != symbolTable.end(); ++it) {
        if(*it == yytext)
        {
            return true;
        }
    }
    return false;
}

inline void indent() 
{
    for (int i = 0; i<level; i++)
        cout << ("    ");
}

void output() 
{
    indent();
    cout << "-->found " << yytext << endl;
}

void program() 
{
    if (!first_of_program()) // Check for PROGRAM
        throw "3: 'PROGRAM' expected";
    
    indent();
    cout << "enter <program>" << endl;
    ++level;
    output();

    nextToken = yylex();
    if(!hasIdent())                     
        throw "2: identifier expected";
    output();

    nextToken = yylex();
    if(!hasSemicolon())                
        throw "14: ';' expected";
    output();

    nextToken = yylex();
    Block();
    --level;
    indent();
    cout << "exit <program>" << endl;
    
}

void Block() 
{
    if (!first_of_block()) // Check for VAR or BEGIN
        throw "18: error in declaration part OR 17: 'BEGIN' expected";
    
    indent();
    cout << "enter <block>" << endl;
    ++level;
    
    if (nextToken == TOK_VAR) 
    {
        output();
        nextToken = yylex();
        while(true)
        {
            if(!hasIdent())                     
                throw "2: identifier expected";

            //check if symbol exists, if it does throw an error, if not, add to the symbol table.
            if(symbolExists(yytext))
                throw "101: identifier declared twice";
            symbolTable.insert(yytext);
            output();

            nextToken = yylex();
            if(!hasColon())                     
                throw "5: ':' expected"; 
            output();

            nextToken = yylex();
            if(!hasIntegerOrReal())                     
                throw "10: error in type";
            output();

            nextToken = yylex();
            if(!hasSemicolon())                
                throw "14: ';' expected";
            output();

            nextToken = yylex();

            cout << endl;

            if(nextToken == TOK_BEGIN)
            {
                break;
            }
        }
    }

    if (nextToken == TOK_BEGIN) 
    {
        Compound();
    }
    --level;
    indent();
    cout << "exit <block>" << endl;
}

void Statement() 
{
    if (!first_of_statement()) // Check for IDENT, BEGIN, IF, WHILE, READ, or WRITE
        throw "900: illegal type of statement";
    
    indent();
    cout << "enter <statement>" << endl;
    ++level;
    if(nextToken == TOK_IDENT)
    {
        Assignment();
    }
    else if(nextToken == TOK_BEGIN)
    {
        Compound();
    }
    else if(nextToken == TOK_IF)
    {
        If();
    }
    else if(nextToken == TOK_WHILE)
    {
        While();
    }
    else if(nextToken == TOK_READ)
    {
        Read();
    }
    else if(nextToken == TOK_WRITE)
    {
        Write();
    }
    --level;
    indent();
    cout << "exit <statement>" << endl;

}

void Assignment() 
{
    if (!first_of_assignment()) // Check for IDENT
        throw "2: identifier expected";

    indent();
    cout << "enter <assignment>" << endl;
    ++level;
    output();

    nextToken = yylex();
    if(!hasAssign())                     
        throw "51: ':=' expected"; 
    output();

    nextToken = yylex();
    Expression();
    --level;
    indent();
    cout << "exit <assignment>" << endl;
}

void Compound() 
{
    if (!first_of_compound()) // Check for BEGIN
        throw "17: 'BEGIN' expected";
    
    indent();
    cout << "enter <compound_statement>" << endl;
    ++level;
    output();

    nextToken = yylex();
    Statement();

    while(nextToken == TOK_SEMICOLON)
    {
        output();
        
        nextToken = yylex();
        
        Statement();
    }

    if(!hasEnd())                     
        throw "13: 'END' expected"; 
    output();
    nextToken = yylex();
    --level;
    indent();
    cout << "exit <compound_statement>" << endl;
}

void If() 
{  
    indent();
    cout << "enter <if statement>" << endl;
    ++level;
    output();

    nextToken = yylex();
    Expression();

    if(!hasThen())                     
        throw "52: 'THEN' expected"; 
    output();
    
    nextToken = yylex();
    Statement();

    if(nextToken == TOK_ELSE)
    {
        output();

        nextToken = yylex();
        Statement();
    }
    --level;
    indent();
    cout << "exit <if statement>" << endl;
}

void While() 
{
    indent();
    cout << "enter <while statement>" << endl;
    ++level;
    output();

    nextToken = yylex();
    Expression();

    Statement();
    --level;
    indent();
    cout << "exit <while statement>" << endl;
}

void Read() 
{
    indent();
    cout << "enter <read>" << endl;
    ++level;
    output();

    nextToken = yylex();
    if(!hasOpenParen())                     
        throw "9: '(' expected"; 
    output();

    nextToken = yylex();
    if(!hasIdent())                     
        throw "2: identifier expected"; 
    output();

    nextToken = yylex();
    if(!hasCloseParen())                     
        throw "4: ')' expected"; 
    output();

    nextToken = yylex();
    --level;
    indent();
    cout << "exit <read>" << endl;
}

void Write() 
{
    indent();
    cout << "enter <write>" << endl;
    ++level;
    output();

    nextToken = yylex();
    if(!hasOpenParen())                     
        throw "9: '(' expected"; 
    output();

    nextToken = yylex();
    if(!hasIdent() && !hasStringLit())                     
        throw "134: illegal type of operand(s)"; 
    output();

    nextToken = yylex();
    if(!hasCloseParen())                     
        throw "4: ')' expected"; 
    output();

    nextToken = yylex();
    --level;
    indent();
    cout << "exit <write>" << endl;
}

void Expression() 
{
    indent();
    cout << "enter <expression>" << endl;
    ++level;
    SimpleExpression();
    if(nextToken == TOK_EQUALTO || nextToken == TOK_LESSTHAN || nextToken == TOK_GREATERTHAN || nextToken == TOK_NOTEQUALTO)
    {
        output();

        nextToken = yylex();
        SimpleExpression();
    }
    --level;
    indent();
    cout << "exit <expression>" << endl;
}

void SimpleExpression() 
{
    if (!first_of_simpleExpression()) // Check for INTLIT, FLOAT_LIT, IDENT, OPENPAREN, NOT, or MINUS
        throw "901: illegal type of simple expression";
    
    indent();
    cout << "enter <simple expression>" << endl;
    ++level;
    Term();
    while(nextToken == TOK_PLUS || nextToken == TOK_MINUS || nextToken == TOK_OR)
    {
        output();
        
        nextToken = yylex();
        Term();
    }
    --level;
    indent();
    cout << "exit <simple expression>" << endl;
}

void Term() 
{
    if (!first_of_term()) // Check for INTLIT, FLOAT_LIT, IDENT, OPENPAREN, NOT, or MINUS
        throw "902: illegal type of term";
    
    indent();
    cout << "enter <term>" << endl;
    ++level;
    Factor();

    nextToken = yylex();
    while(nextToken == TOK_MULTIPLY || nextToken == TOK_DIVIDE || nextToken == TOK_AND)
    {
        output();
        
        nextToken = yylex();
        Factor();

        nextToken = yylex();
    }
    --level;
    indent();
    cout << "exit <term>" << endl;
}

void Factor() 
{
    if (!first_of_factor()) // Check for INTLIT, FLOAT_LIT, IDENT, OPENPAREN, NOT, or MINUS
        throw "903: illegal type of factor";
    
    indent();
    cout << "enter <factor>" << endl;
    ++level;
    //check if symbol has been declared (if it exists)
    if(nextToken == TOK_IDENT && !symbolExists(yytext))
    {
        throw "104: identifier not declared";
    }

    output();

    if(nextToken == TOK_OPENPAREN)
    {
        nextToken = yylex();
        Expression();

        if(!hasCloseParen())                     
            throw "4: ')' expected"; 
        output();
    }
    else if(nextToken == TOK_NOT || nextToken == TOK_MINUS)
    {
        nextToken = yylex();
        Factor();
    }
    --level;
    indent();
    cout << "exit <factor>" << endl;
}

//********************************************************************************************
bool first_of_program() 
{
    return nextToken == TOK_PROGRAM;
}
bool first_of_block() 
{
    if(nextToken == TOK_VAR || nextToken == TOK_BEGIN)
    {
        return true;
    }
    return false;
}
bool first_of_statement() 
{
    if(nextToken == TOK_IDENT || nextToken == TOK_BEGIN || nextToken == TOK_IF || nextToken == TOK_WHILE || nextToken == TOK_READ || nextToken == TOK_WRITE)
    {
        return true;
    }
    return false;
}
bool first_of_assignment() 
{
    return nextToken == TOK_IDENT;
}
bool first_of_compound() 
{
    return nextToken == TOK_BEGIN;
}
bool first_of_simpleExpression() 
{
    if(nextToken == TOK_INTLIT || nextToken == TOK_FLOATLIT || nextToken == TOK_IDENT || nextToken == TOK_OPENPAREN || nextToken == TOK_NOT || nextToken == TOK_MINUS)
    {
        return true;
    }
    return false;
}
bool first_of_term() 
{
    if(nextToken == TOK_INTLIT || nextToken == TOK_FLOATLIT || nextToken == TOK_IDENT || nextToken == TOK_OPENPAREN || nextToken == TOK_NOT || nextToken == TOK_MINUS)
    {
        return true;
    }
    return false;
}
bool first_of_factor() 
{
    if(nextToken == TOK_INTLIT || nextToken == TOK_FLOATLIT || nextToken == TOK_IDENT || nextToken == TOK_OPENPAREN || nextToken == TOK_NOT || nextToken == TOK_MINUS)
    {
        return true;
    }
    return false;
}
bool hasIdent() 
{
    return nextToken == TOK_IDENT;
}
bool hasSemicolon() 
{
    return nextToken == TOK_SEMICOLON;
}
bool hasColon() 
{
    return nextToken == TOK_COLON;
}
bool hasIntegerOrReal() 
{
    if(nextToken == TOK_INTEGER || nextToken == TOK_REAL)
    {
        return true;
    }
    return false;
}
bool hasAssign() 
{
    return nextToken == TOK_ASSIGN;
}
bool hasEnd() 
{
    return nextToken == TOK_END;
}
bool hasThen() 
{
    return nextToken == TOK_THEN;
}
bool hasOpenParen() 
{
    return nextToken == TOK_OPENPAREN;
}
bool hasCloseParen() 
{
    return nextToken == TOK_CLOSEPAREN;
}
bool hasStringLit() 
{
    return nextToken == TOK_STRINGLIT;
}

#endif