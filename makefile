dataWriter.exe: dataWriter.c lib/cards.c lib/poker.c
	gcc -o dataWriter.exe dataWriter.c lib/cards.c lib/poker.c -ggdb
