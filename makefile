dataWriter.exe: dataWriter.c lib/cards.c lib/poker.c
	gcc -o dataWriter.exe dataWriter.c lib/cards.c lib/poker.c -ggdb

test.exe: test.c lib/cards.c lib/poker.c
	gcc -o test.exe test.c lib/cards.c lib/poker.c -ggdb
