#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "itp.h"

int Cat(int argc, char* argv[]);
int Tac(int argc, char* argv[]);
int Yes(int argc, char* argv[]);
int Tee(int argc, char* argv[]);
int Ls(int argc, char* argv[]);
int Dir(int argc, char * argv[]);
int Help(int argc, char* argv[]);
int Version(int argc, char *argv[]);

int main(int argc, char* argv[]) {
	char *s, *pch, *pch1;
	char **cmds = NULL;
	int i = 0, j, sz;
	int charsSoFar, sameString = 0;

	s = (char *) malloc(sizeof(char)*101);
	
	while (!feof(stdin)) {
	
		printf("$user@robshell->");
		//fgets(string s, sizeof(s), stdin);
		gets(s);	//fgets(string s, sizeof(s), stdin)
		s[strlen(s)] = '\0';
		//fgets (mystring , 100 , pFile)
		pch = strtok(s, " ");
		while (pch != NULL) {
			if (!sameString) {
				i++;
				charsSoFar = 0;
			}
				
			if (cmds == NULL)
				cmds = (char **) malloc (sizeof(char *));
			else 
				cmds = (char **) realloc (cmds, sizeof(char *) * i);
				
			if (!sameString)
				cmds[i-1] = (char *) malloc (sizeof(char) * 100);
			
			if (pch[0] == '"') {
				sameString = 1;
			}
			
			if (sameString && charsSoFar != 0) {
				strcpy(cmds[i-1]+charsSoFar, " ");
				strcpy(cmds[i-1]+ (++charsSoFar), pch);
				charsSoFar += strlen(pch);
			} else if (sameString && charsSoFar == 0) {
				strcpy(cmds[i-1], pch+1);
				charsSoFar += strlen(pch)-1;
			} else
				strcpy(cmds[i-1], pch);
			
			
			
			if (pch[strlen(pch)-1] == '"') {
				sameString = 0;
				cmds[i-1][strlen(cmds[i-1])-1] = '\0';
			}
			
			pch = strtok(NULL, " ");
		}
		
		if(strcmp("cat", cmds[0]) == 0)
			Cat(i, cmds);
		else if(strcmp("yes", cmds[0]) == 0)
			Yes(i, cmds);
		else if(strcmp("tac", cmds[0]) == 0)
			Tac(i, cmds);
		else if(strcmp("tee", cmds[0]) == 0)
			Tee(i, cmds);
		else if(strcmp("ls", cmds[0]) == 0)
			Ls(i, cmds);
		else if(strcmp("dir", cmds[0]) == 0)
			Dir(i, cmds);
		else if(strcmp("help", cmds[0]) == 0)
			Help(i, cmds);
		else if(strcmp("version", cmds[0]) == 0)
			Version(i, cmds);
		else
			printf("Unknown cmd: %s\n", cmds[0]);
		
		for (j=0; j<i; j++) {
			free(cmds[j]);
			cmds[j] = NULL;
		}
		
		if(cmds != NULL) {
			free(cmds);
			cmds = NULL;
		}
		i=0;
	}

	return 0;
}
