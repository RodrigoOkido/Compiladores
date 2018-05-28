etapa5: y.tab.o lex.yy.o hash.o main.o ast.o semantic.o tac.o
	gcc y.tab.o lex.yy.o hash.o main.o ast.o semantic.o tac.o  -o etapa5
lex.yy.o: lex.yy.c
	gcc lex.yy.c -c
y.tab.o: y.tab.c
	gcc -c y.tab.c
y.tab.c: parser.y
	yacc -d -r solved parser.y
hash.o: hash.c
	gcc hash.c -c
ast.o: ast.c
	gcc -c ast.c
semantic.o: semantic.c
	gcc -c semantic.c
tac.o: tac.c
	gcc -c tac.c
main.o: main.c
	gcc main.c -c
lex.yy.c: scanner.l
	lex scanner.l
clean:
	rm etapa5 lex.yy.c *.o y.tab.c y.tab.h y.output
