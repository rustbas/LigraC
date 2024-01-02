all:
	clang -o result.out main.c -g3
clean:
	rm *.out
	rm *.so
