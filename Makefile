CC=gcc
YY=bison -d
LEX=flex
O=chouchou
lbstr = bstrlib.o bstrutils.o

ALL: test_parser lex.yy.c
	cd bstr; make
	$(CC) -o $(O) $(lbstr) lex.yy.c test_parser.tab.c

test_parser: test_parser.y
	$(YY) test_parser.y

lex.yy.c: test_lexicon.l
	$(LEX) test_lexicon.l

clean:
	rm test_parser.tab.* *.o lex.yy.c chouchou
