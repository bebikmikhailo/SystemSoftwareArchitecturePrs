FLAGS = -Wall
FLAGS_O2 = -O2 -Wall
FLAGS_O3 = -O3 -Wall

MATH_LIB = -lm

mainO2: main.o erf_module.o
	gcc $(FLAGS_O2) main.o erf_module.o -o mainO2 $(MATH_LIB)


mainO3: main.o erf_module.o
	gcc $(FLAGS_O3) main.o erf_module.o -o mainO3 $(MATH_LIB)



main: main.o erf_module.o
	gcc $(FLAGS) main.o erf_module.o -o main $(MATH_LIB)

main.o: main.c
	gcc -c $(FLAGS) main.c

erf_module.o: erf_module.c erf_module.h
	gcc -c $(FLAGS) erf_module.c

clean:
	rm -f *.o main mainO2 mainO3
