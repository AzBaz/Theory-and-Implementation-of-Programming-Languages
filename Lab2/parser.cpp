/*
Name: Azim Bazarov            NetID: ab4908
  Course: CSE 4714              
  Lab: 02 - Parsing 
  Purpose of File: Create a recursive descent parser for a subset of English sentences.
*/

#include <stdio.h>
#include <iostream>
#include "lexer.h"
#include "parser.h"

using namespace std;

extern "C"{
  extern int   yylex();                 // the generated lexical analyzer
  extern char *yytext;                  // text of current lexeme
}

int nextToken = 0;

// Production functions

bool firstOf_sentence();
bool first_noun_phrase();
bool first_adjective_phrase();
bool first_verb_phrase();
void noun_phrase();
void adjective_phrase();
void verb_phrase();
string addSpace(int n);

//*****************************************************************************
// Get the next lexeme (word in sentence)

int lex() {
  nextToken = yylex();
  if( nextToken == TOK_EOF ) {
    yytext[0] = 'E'; yytext[1] = 'O'; yytext[2] = 'F'; yytext[3] = 0;   
  }

  printf("Next token: %d, lexeme: |%s|\n", nextToken, yytext);
  return nextToken;
}
//*****************************************************************************
// Report what we found
void output( string what ) 
{
  cout << "===> Accepted " << what << ": |" << yytext << "| <===" << endl;
}
//*****************************************************************************
// <sentence> -> <noun phrase> <verb phrase> <noun phrase>
void sentence() {
  if( firstOf_sentence() == false )
    throw( "<sentence> did not start with an article or possessive." );

  cout << "Enter <sentence>" << endl;

  //Check for next token
  noun_phrase();
  verb_phrase();
  noun_phrase();

  cout << "Exit <sentence>" << endl;
}

// Addding Space based on the phrase count
string addSpace(int n){
	string space_num;
	n = n * 2;                             
  space_num = string(n, ' ');           //Adds the spaces
  return space_num; 
}

bool firstOf_sentence() {
  return nextToken == ARTICLE || nextToken == POSSESSIVE; 
}

// Error check for first word of noun
bool first_noun_phrase()
{
  return nextToken == ARTICLE || nextToken == POSSESSIVE;  
}

// Error check first word of adjective
bool first_adjective_phrase()
{
  return nextToken == ARTICLE || nextToken == POSSESSIVE; 
}

// Error check first word of verb phrase
bool first_verb_phrase()
{
  return nextToken == VERB || nextToken == ADVERB;  
}

//noun phrase
void noun_phrase()
{
  static int NPcount = 1; // A static variable to restart count
  int np_count = NPcount++; // Add the count based on the text.

  if( first_noun_phrase() == false ) 
  {
    throw( "<noun phrase> did not start with an article or possessive." );
  }

  cout << addSpace(np_count) << "Enter <noun phrase> " << np_count << endl;

  //Next token
  adjective_phrase(); 

  if (nextToken == NOUN)
  {
    output("NOUN");
    lex();
  }
  else
  {
    throw "<noun phrase> did not have a noun.";
  }

  cout << addSpace(np_count) << "Exit <noun phrase> " << np_count << endl;
}

// adjective phrase
void adjective_phrase()
{
  // Current count and a static count of the phrases.
  static int APcount = 1; 
  int ap_count = APcount++;

  if( first_adjective_phrase() == false ) 
  {
    throw( "<adjective phrase> did not start with an article or possessive." ); 
  }
    
  cout << addSpace(ap_count) << "Enter <adjective phrase> " << ap_count <<endl; 

  if (nextToken == ARTICLE || nextToken == POSSESSIVE)
  {
    if (nextToken == ARTICLE) 
      output("ARTICLE"); 

    if (nextToken == POSSESSIVE) 
      output("POSSESSIVE");
    
    lex();
  }

  if (nextToken == ADJECTIVE)
  {
    output("ADJECTIVE");
    lex();
  }
  else
  {
    throw "<adjective phrase> did not have an adjective."; 
  }

  cout << addSpace(ap_count) << "Exit <adjective phrase> " << ap_count << endl; 
}

void verb_phrase()
{
  // Current count and a static count of the phrases.
  static int VPcount = 1; 
  int vp_count = VPcount++; 

  if (first_verb_phrase() == false)  
    throw "<verb phrase> did not start with a verb or an adverb."; 

  cout << addSpace(vp_count) << "Enter <verb phrase> " << vp_count << endl;

  if (nextToken == VERB) 
  {
    output("VERB");
    lex();
  }
  
  else if (nextToken == ADVERB)
  {
    output("ADVERB");
    lex();
    verb_phrase();
  }

  cout << addSpace(vp_count) << "Exit <verb phrase> " << vp_count << endl; 
}
