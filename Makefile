CC=gcc
YY=bison -d
LEX=flex
O=chouchou

ALL: test_parser lex.yy.c
	$(CC) -o $(O) bstr/bstrlib.c lex.yy.c test_parser.tab.c

test_parser: test_parser.y
	$(YY) test_parser.y

lex.yy.c: test_lexicon.l
	$(LEX) test_lexicon.l

clean:
	rm test_parser.tab.* lex.yy.c chouchou
