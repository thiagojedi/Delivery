all: main.c
	gcc -g -o delivery main.c -export-dynamic `pkg-config --cflags --libs gtk+-2.0`
	./delivery