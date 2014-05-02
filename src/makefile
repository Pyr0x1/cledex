all: *.c *.h
	gcc *.c `pkg-config --cflags --libs glib-2.0` -l sqlite3 -o cledex

install: 
	cp cledex /usr/local/bin
	mkdir -p /usr/local/share/cledex
	cp -r ../Database/ /usr/local/share/cledex
	rm cledex

uninstall:
	rm /usr/local/bin/cledex
	rm -r /usr/local/share/cledex

