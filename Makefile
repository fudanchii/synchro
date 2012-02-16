CC=gcc
YY=bison -d
LEX=flex
O=chouchou
lbstr = bstrlib.o bstrutils.o

ALL: chouchou

chouchou: test_parser lex.yy.c
	cd bstr; make -s
	$(CC) -g -o $(O) $(lbstr) lex.yy.c test_parser.tab.c

test_parser: test_parser.y
	$(YY) test_parser.y

lex.yy.c: test_lexicon.l
	$(LEX) test_lexicon.l

sample: test_fwx.h chouchou
	./$(O) test_fwx.h > sample.c
	$(CC) -g -o sample sample.c
	./sample

clean:
	rm test_parser.tab.* *.o lex.yy.c chouchou sample sample.c
