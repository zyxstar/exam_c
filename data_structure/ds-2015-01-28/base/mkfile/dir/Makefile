
DIRS  := lib app bin

all:
%:
	for dir in $(DIRS) ; do \
		make -C $$dir $@ ; \
	done

clean:
	for dir in $(DIRS) ; do \
		make -C $$dir $@ ; \
	done
	rm -f *~ main hello
