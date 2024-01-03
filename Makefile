all: ctags
	gcc -o result.out main.c -O3 -lm -fopenmp
test: ctags
	gcc -o result.out main.c -g3 -lm -fopenmp
clean:
	rm *.out
ctags:
	ctags --recurse
