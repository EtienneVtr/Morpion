run : compil
	./Main

compil : Main clean

Main : Main.o Morpion.o
	clang -Wall -Wextra -pedantic -O0 -g3 -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls Morpion.o Main.o -o Main

Main.o : ./src/Main.c
	clang -c -Wall -Wextra -pedantic -O0 -g3 -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls ./src/Main.c 

Morpion.o : ./src/Morpion.c ./src/Morpion.h
	clang -c -Wall -Wextra -pedantic -O0 -g3 -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls ./src/Morpion.c

clean :
	rm -f *.o Morpion
