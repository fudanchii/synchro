%option noyywrap
%option yylineno
%{

/*
 * This file is part of synchro Test Suite.
 * Lexical analyzer for test case extraction
 * from source code comment/documentation
 *
 * Nurahmadie 2011
 */

#include "bstr/bstrlib.h"
#include "bstr/utils.h"
#include "test_parser.tab.h"

int get_operator(char *input);

/* handle locations */
int yycolumn  = 1;
int last_line = 1;
int nlineflag = 0;
static bstring in_text;

#define YY_USER_ACTION { \
    if (nlineflag) {\
        yylineno +=1; yycolumn = 1;\
        nlineflag = 0;\
    }\
    if (yytext[0] == '\n') {\
        nlineflag = 1;\
    } \
    yylloc.last_line    = yylineno; \
    yylloc.first_column = yycolumn; \
    yylloc.last_column  = yycolumn + yyleng - 1; \
    yycolumn += yyleng; \
}

%}

%x AT_COMMENT
%x AT_COPY
%x AT_COPY_AND_TEST
%x AT_STRING
%x AT_QUOTE

%%

<INITIAL>"/*" {
    BEGIN AT_COMMENT;
}

<AT_COMMENT>"*/" {
    BEGIN INITIAL;
}

<AT_COMMENT>"#=" {
    BEGIN AT_COPY;
}

<AT_COPY,AT_COPY_AND_TEST>\n {
    BEGIN AT_COMMENT;
    return EOL;
}

<AT_COPY>[\(a-zA-Z0-9_].*; {
    return get_set(SENTENCE, yytext);
}

<AT_COMMENT>"#!" {
    BEGIN AT_COPY_AND_TEST;
}

<INITIAL>^"#"[ \t]*include[ \t]*["<][^ \t\n\">]+[">] {
    return get_set(INCLUDES, yytext);
}

<AT_COPY_AND_TEST>".==" {
    return EQU;
}

<AT_COPY_AND_TEST>".>=" {
    return GT_EQU;
}

<AT_COPY_AND_TEST>".<=" {
    return LT_EQU;
}

<AT_COPY_AND_TEST>".!=" {
    return N_EQU;
}

<AT_COPY_AND_TEST>".>" {
    return GT;
}

<AT_COPY_AND_TEST>".<" {
    return LT;
}

<AT_COPY_AND_TEST>\" {
    in_text = bfromcstr("");
    in_text = do_concat(2, in_text, bfromcstr(yytext));
    BEGIN AT_STRING;
}


<AT_STRING>\\ {
    in_text = do_concat(2, in_text, bfromcstr(yytext));
    BEGIN AT_QUOTE;
}

<AT_STRING>\" {
    in_text = do_concat(2, in_text, bfromcstr(yytext));
    BEGIN AT_COPY_AND_TEST;
    return get_set(STRING, bdata(in_text));
}

<AT_STRING>. {
    in_text = do_concat(2, in_text, bfromcstr(yytext));
}

<AT_QUOTE>. {
    in_text = do_concat(2, in_text, bfromcstr(yytext));
    BEGIN AT_STRING;
}

<AT_COPY_AND_TEST>[a-zA-Z_][a-zA-Z0-9_]* {
    return get_set(IDENTIFIER, yytext);
}

<AT_COPY_AND_TEST>0|(\-|\+)?[1-9][0-9]* {
    return get_set(NUMBER, yytext);
}


<AT_COPY_AND_TEST>"(" {
    return get_set(OP, yytext);
}

<AT_COPY_AND_TEST>")" {
    return get_set(CP, yytext);
}

<AT_COPY_AND_TEST>"+"|"-"|"*"|"/"|"%"   {
    return get_set(OPERATOR, yytext);
}

<AT_COPY_AND_TEST>"," {
    return get_set(COMMA, yytext);
}


<INITIAL,AT_COMMENT>\n {
    return EOL;
}

<INITIAL,AT_COMMENT,AT_COPY_AND_TEST,AT_COPY>[ \t] { }
<INITIAL,AT_COMMENT,AT_COPY_AND_TEST,AT_COPY>. { }
%%

int get_set(int state, char *input) {
    yylval.s = bfromcstr(input);
    return state;
}

