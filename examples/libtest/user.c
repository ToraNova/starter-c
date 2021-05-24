#include <stdio.h>
#include "hello.h"

// compile this separately
// if shared lib: gcc user.c -L. -lhello
// no need to indicate -L if installed in standard dir. (/usr/lib/)
//
// if static lib: gcc user.c libhello.a

int main(int argc, char *argv[], char *envp[]){
	test();
}
