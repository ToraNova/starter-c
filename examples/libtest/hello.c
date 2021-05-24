#include <stdio.h>
#include <math.h> //example usage of other libs in our lib
#include "hello.h"

// shared lib: gcc -c -fPIC hello.c -o hello.o
// gcc -shared -o libhello.so hello.o -lm

// static lib: gcc -c hello.c -o hello.o
// ar -rsc hello.o -lm

void test(void){
	printf("hello world! %.5f\n", sqrt(2));
}
