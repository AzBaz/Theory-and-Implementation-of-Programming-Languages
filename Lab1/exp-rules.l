/*********************************************************************
       Name: Azim bazarov            
       NetID: ab4908
       Course: CSE 4714
       Lab: 01 - Lexical Analyzer
       Purpose of File: Contains the expression used to write the given tokens for the lab using FLEX format
     *********************************************************************/

%option noyywrap
%{
#include "lexer.h"
// global variable holds while current line number is read
int line_number = 1;
%}

%%

\,                                                    { return SEPARATOR; }
 /*writing generic data below*/
[0-9]{4}\/[0-9]{2}\/[0-9]{2}                          { return DATE; }

[Yy]es                                                { return YES;}
[Nn]o                                                 { return NO; }
[Uu]nknown                                            { return UNKNOWN_VALUE; }
[Mm]issing                                            { return MISSING; }

 /*writing data values below*/
[Ll]aboratory-[Cc]onfirmed\ [Cc]ase	              { return LABORATORY; }
[Pp]robable\ [Cc]ase                                  { return PROBABLE; }
[Mm]ale			                              { return MALE; }
[Ff]emale		                              { return FEMALE; }
[Oo]ther	        	                      { return OTHER; }
0\ \-\ 9\ [Yy]ears                                    { return AGE_0X; }
10\ \-\ 19\ [Yy]ears                                  { return AGE_1X; }
20\ \-\ 39\ [Yy]ears                                  { return AGE_2X; }
40\ \-\ 49\ [Yy]ears                                  { return AGE_4X; }
50\ \-\ 59\ [Yy]ears                                  { return AGE_5X; }
60\ \-\ 69\ [Yy]ears                                  { return AGE_6X; }
70\ \-\ 79\ [Yy]ears                                  { return AGE_7X; }
80\+\ [Yy]ears                                        { return AGE_8X; }
\"[Hh]ispanic\/[Ll]atino\"                            { return HISPANIC; }
\"[Aa]merican\ [Ii]ndian\ \/\ [aA]laska\ [Nn]ative,\ [Nn]on-[Hh]ispanic\"                  			      { return NATIVE_AMERICAN; }
\"[Aa]sian,\ [Nn]on-[Hh]ispanic\"                     { return ASIAN; }
\"[Bb]lack,\ [Nn]on-[Hh]ispanic\"                     { return BLACK; }
\"[Nn]ative\ [Hh]awaiian\ \/\ [Oo]ther\ [Pp]acific\ [Ii]slander,\ [Nn]on-[Hh]ispanic\"     { return PACIFIC_ISLANDER; }
\"[Ww]hite,\ [Nn]on-[Hh]ispanic\"                     { return WHITE; }
\"[Mm]ultiple\/[Oo]ther,\ [Nn]on-[Hh]ispanic\"        { return MULTIPLE_OTHER; }

[\r\n]           {line_number++;}
[ \t]+             /* nop */


.         { return UNKNOWN_TOKEN; }

 /* read eof */

<<EOF>>   { return EOF_TOKEN; }


