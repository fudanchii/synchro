%locations
%{

/*
 * This file is part of synchro Test Suite.
 * Syntax parser for test case extraction
 * from source code comment/documentation
 *
 * Nurahmadie 2011
 */

#define YYERROR_VERBOSE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bstr/utils.h"
#include "bstr/bstrlib.h"
#include <stdarg.h>


struct parse_param {
    bstring includes;
    bstring in_main;
};

struct parse_param pp;

%}

%union {
    bstring s;
}

%token <s> OPERATOR
%token <s> COMMA
%token EQU GT_EQU LT_EQU N_EQU GT LT
%token <s> NUMBER
%token <s> STRING
%token <s> IDENTIFIER
%token <s> OP  <s> CP
%token <s> SENTENCE
%token <s> INCLUDES
%token EOL

%type <s> expr
%type <s> term
%type <s> term_and_function
%type <s> arg_list
%type <s> one_arg_list
%type <s> func_def
%type <s> accept

%%

tmain:
     | tmain line
     | tmain EOL
     ;


line:INCLUDES              { pp.includes = do_concat(3, pp.includes, $1, bfromcstr("\n"));}
    |accept                { pp.in_main  = do_concat(3, pp.in_main, $1, bfromcstr("\n")); }
    ;


accept:SENTENCE
    | expr EQU STRING      { $$ = bformat("assert_mem(%s, %s, %d);", bdata($1), bdata($3), blength($3) - 2); }
    | expr EQU term        { $$ = bformat("assert_eq(%s, %s);", bdata($1), bdata($3)); }
    | expr GT_EQU term     { $$ = bformat("assert_ge(%s, %s);", bdata($1), bdata($3)); }
    | expr LT_EQU term     { $$ = bformat("assert_le(%s, %s);", bdata($1), bdata($3)); }
    | expr N_EQU  term     { $$ = bformat("assert_ne(%s, %s);", bdata($1), bdata($3)); }
    | expr GT     term     { $$ = bformat("assert_gt(%s, %s);", bdata($1), bdata($3)); }
    | expr LT     term     { $$ = bformat("assert_lt(%s, %s);", bdata($1), bdata($3)); }
    ;

expr: term_and_function
    | expr OPERATOR term_and_function   { $$ = do_concat(3, $1, $2, $3); }
    ;

term_and_function: func_def
                 | term
                 | STRING
                 ;

func_def: IDENTIFIER OP arg_list CP     { $$ = do_concat(4, $1, $2, $3, $4); }
        ;

arg_list:                               { $$ = bfromcstr(""); }
        | one_arg_list
        ;

one_arg_list: expr
            | one_arg_list COMMA expr       { $$ = do_concat(3, $1, $2, $3); }
            ;

term: IDENTIFIER
    | NUMBER
    | OP expr CP                         { $$ = do_concat(3, $1, $2, $3); }
    ;

%%


int main(int argc, char **argv) {
    FILE *fin;
    char *fname;
    int len;

    if (!(fin = fopen(argv[1], "r"))) {
        fprintf(stderr, "Error opening file : %s\n", argv[1]);
        abort();
    }

    fname = argv[1];
    len = strlen(fname);

    yyrestart(fin);

    pp.includes = bfromcstr("");
    pp.in_main  = bfromcstr("");

    if (fname[len-1] == 'c')
        fname[len-1] == 'h';

    fprintf(stdout,"#include \"%s\"\n", fname);
    fprintf(stdout,"#include <stdio.h>\n");

    yyparse();
    fclose(fin);

    puts(bdata(pp.includes));
    puts("\n"
         "int main() {\n"
         "test_begin;\n");
    puts(bdata(pp.in_main));
    puts("test_end;\n"
         "return 0;\n}\n");

    return 0;
}

yyerror(char *s) {
    fprintf(stderr, "%d:%d:%s\n", yylloc.last_line, yylloc.first_column, s);
}

