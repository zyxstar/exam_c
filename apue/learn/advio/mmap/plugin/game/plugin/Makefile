OBJ := add.plugin sub.plugin mul.plugin div.plugin

all: $(OBJ)

%.plugin: %.c
	gcc -fpic -shared -o $@ $<
