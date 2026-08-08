GCW=gcc -std=c11 -Wall -Werror -Wextra



s21_cat:
	 $(GCW) s21_cat.c s21_cat_main.c -c
	 $(GCW) s21_cat.o s21_cat_main.o -o s21_cat


test:
	bash test.sh


clean:
	rm s21_cat.o s21_cat_main.o s21_cat
	
