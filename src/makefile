all: *.c *.h
	gcc -O *.c `pkg-config --cflags --libs glib-2.0` -l sqlite3 -lpthread -o cledex

install: 
	mv cledex /usr/local/bin
	mkdir -p /usr/local/share/cledex
	cp -r ../database/ /usr/local/share/cledex

uninstall:
	rm /usr/local/bin/cledex
	rm -r /usr/local/share/cledex

