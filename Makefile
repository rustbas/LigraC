all: ctags
	clang -o result.out main.c -g3 -lm
clean:
	rm *.out
	rm *.so
ctags:
	ctags --recurse
