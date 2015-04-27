all: add.plugin sub.plugin mul.plugin div.plugin

%.plugin: %.c
	gcc -shared -fpic -o $@ $<

clean:
	rm -f *~ *.plugin
