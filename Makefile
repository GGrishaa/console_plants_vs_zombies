GCC = gcc
CFLAGS = -std=c11 -Wall -Werror -Wextra
LDFLAGS = -lncurses

all: pvz run

run: pvz
	./$<

pvz: main.o draw.o
	$(GCC) $^ $(LDFLAGS) -o $@

main.o: main.c draw.h 
	$(GCC) $< -c $(CFLAGS) -o $@

draw.o: draw.c draw.h icons.h
	$(GCC) $< -c $(CFLAGS) -o $@

clean:
	rm -f pvz *.o
	clear

clang:
	touch .clang-format
	echo "---" > .clang-format
	echo "BasedOnStyle: Google" >> .clang-format
	clang-format -i *.c *.h
	rm -f .clang-format
	clear

rebuild: clean all

.PHONY: all pvz run clean clang rebuild