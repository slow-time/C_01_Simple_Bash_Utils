GCW=gcc -std=c11 -Wall -Werror -Wextra



s21_grep:
	 $(GCW) s21_grep.c s21_grep_main.c -c
	 $(GCW) s21_grep.o s21_grep_main.o -o s21_grep


test:
	bash test.sh 

clean:
	rm s21_grep s21_grep.o s21_grep_main.o 
