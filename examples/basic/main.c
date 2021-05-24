/*
 * sample program with arg/env inputs
 *
 */

#include <stdio.h>
extern char **environ;

int main(int argc, char *argv[]){

	for(int i=0;i<argc;i++){
		fprintf(stdout, "arg: %s\n", argv[i]);
	}

	for(int i=0;environ[i] != NULL;i++){
		fprintf(stdout, "env: %s\n", environ[i]);
	}
}
