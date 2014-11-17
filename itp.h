#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <locale.h>
#include <langinfo.h>
#include <limits.h>
#include <sys/stat.h>

#define SIZE 1000;

typedef FILE *files;

int Cat(int argc, char* argv[]) {
	//files *mFiles;
	int *mFiles;
	char *s, *pch, *pch1;
	char *buffer = NULL, *finalString = NULL;
	int size = 100;
	int sz, finalStringLen = 0;
	int c;
	int i, j, nrFiles;
	int bf = 0, Ef = 0, nf = 0, sf = 0;
	int lineNumber = 0, x;

	//flags for each valid option
	while ((c = getopt(argc, argv, "bEns")) != -1) {
		switch (c) {
			case 'b':
				bf = 1;
				break;
			case 'E':
				Ef = 1;
				break;
			case 'n':
				break;
			case 's':
				sf = 1;
				break;
			case '?':
				optind =1;
				return(2);
			default :
				optind =1;
				return(2);
		}
	}

	if ((nrFiles = argc-optind) == 0) {	//in case no files are given as arguments
		s = (char*) malloc(sizeof(char)*size);
		//necessary modifications depending on the flag followed by a print
		while(!feof(stdin)) {
			while ( (sz = read(0, buffer, size)) != 0) {

				buffer[sz-1] = '\0';

				if (sf) {
						if(strlen(buffer) < 1 && sf > 1)
							continue;
						if(strlen(buffer) < 1)
							sf++;
						else
							sf = 1;
					}

					if (nf) {
						lineNumber++;
						printf("%d\t", lineNumber);
					} else if (bf) {
						if (strlen(buffer) > 1) {
							lineNumber++;
							printf("%d\t", lineNumber);
						} else {
							printf("\t");
						}
					}

					printf("%s", buffer);

					if (Ef)
						printf("$");

					printf("\n");
			}
		}
	} else { //if there are no files
		//mFiles = (files*) malloc(sizeof(files)*nrFiles);
		mFiles = (int*) malloc(sizeof(int)*nrFiles);
		//deschide fiecare fisier
		for(i=0; i<nrFiles; i++) {
			//mFiles[i] = (files) malloc(sizeof(files));
			if ((mFiles[i] = open(argv[optind+i], O_RDONLY)) == -1) {
				printf("Can't open file: %s\n", argv[optind+i]);
				optind =1;
				return(3);
			}
		}

		s = (char*) malloc(sizeof(char)*size+1);
		for (i=0; i<nrFiles; i++) { //reads from files, modifies depending on flag then prints

			while ( (sz = read(mFiles[i], s, size)) != 0 ) {
				int sLen = 0;
				s[sz] = '\0';

				sLen = strlen(s);
				if (finalString == NULL) {
					finalString = (char *) malloc (sizeof(char) * (sLen + 1));
				} else {
					finalString = (char *) realloc (finalString, sizeof(char) * (sLen + finalStringLen + 1));
				}

				strcpy(finalString+finalStringLen, s);
				finalStringLen += sLen;
			}

			pch=finalString;
			pch1=finalString;
			while ((pch1=strchr(pch1+1,'\n')) !=NULL) {

				if (buffer == NULL) {
					buffer = (char *) malloc (sizeof(char) * (pch1-pch+1));
				} else {
					buffer = (char *) realloc (buffer, sizeof(char) * (pch1-pch+1));
				}

				strncpy(buffer, pch, pch1-pch);
				buffer[pch1-pch] = '\0';
				pch += pch1-pch+1;

				if (sf) {
					if(strlen(buffer) < 1 && sf > 1)
						continue;
					if(strlen(buffer) < 1)
						sf++;
					else
						sf = 1;
				}

				if (nf) {
					lineNumber++;
					printf("%d\t", lineNumber);
				} else if (bf) {
					if (strlen(buffer) > 1) {
						lineNumber++;
						printf("%d\t", lineNumber);
					} else {
						printf("\t");
					}
				}

				printf("%s", buffer);

				if (Ef)
					printf("$");

				printf("\n");

			}
		}
	}
	//frees allocated space
	printf("\n");
	free(s);
	free(finalString);
	free(buffer);
	for(i=0; i<nrFiles; i++)
		close(mFiles[i]);
	free(mFiles);
	optind =1;
	return 0;
}

int Tac(int argc, char * argv[]) {
	//files *mFiles;
	int *mFiles;
	char *s, *pch1;
	char *finalString = NULL, *buffer = NULL;
	int size = 100;
	int sz, finalStringLen = 0;
	int c;
	int i, j, nrFiles;
	int bf = 0, Ef = 0, nf = 0, sf = 0;
	int lineNumber = 0, x;

	//flags for each valid option
	while ((c = getopt(argc, argv, "b")) != -1) {
		switch (c) {
			case 'b':
				bf = 1;
				break;
			default :
				optind =1;
				return(2);
		}
	}

	if ((nrFiles = argc-optind) == 0) { //in case there are no files given as arguments
		s = (char*) malloc(sizeof(char)*size);
		//necessary modifications depending on flag, followed by a print
		while(!feof(stdin)) {
			while ( (sz = read(0, s, size)) != 0) {

			}
		}
	} else { //in case there are no files
		//mFiles = (files*) malloc(sizeof(files)*nrFiles);
		mFiles = (int*) malloc(sizeof(int)*nrFiles);
		//opens each file
		for(i=0; i<nrFiles; i++) {
			//mFiles[i] = (files) malloc(sizeof(files));
			if ((mFiles[i] = open(argv[optind+i], O_RDONLY)) == -1) {
				printf("Could not open file: %s\n", argv[optind+i]);
				optind =1;
				return(3);
			}
		}

		s = (char*) malloc(sizeof(char)*size+1);
		for (i=0; i<nrFiles; i++) { //reads from files, modifies depending on flag then prints

			while ( (sz = read(mFiles[i], s, size)) != 0 ) {
				int sLen = 0;
				s[sz] = '\0';

				sLen = strlen(s);
				if (finalString == NULL) {
					finalString = (char *) malloc (sizeof(char) * (sLen + 1));
				} else {
					finalString = (char *) realloc (finalString, sizeof(char) * (sLen + finalStringLen + 1));
				}

				strcpy(finalString+finalStringLen, s);
				finalStringLen += sLen;
			}

			while ((pch1=strrchr(finalString, '\n')) !=NULL) {
				if (bf)
					printf("\n");

				printf("%s", pch1+1);

				if (!bf)
					printf("\n");
				finalString[pch1-finalString] = '\0';
			}

			printf("%s", finalString);
			printf("\n");
		}
	}
	//frees allocated space
	printf("\n");
	free(s);
	free(finalString);
	for(i=0; i<nrFiles; i++)
		close(mFiles[i]);
	free(mFiles);
	optind =1;
	return 0;
}

int Tee(int argc, char * argv[]) {
	int *mFiles;
	int nrFiles;
	int c,i,j;
	int aflag=0;
	char* sstr;

	while((c = getopt(argc, argv, "a")) != -1) { 	//sets flags 
		switch(c) {
			case 'a':
				aflag=1;
				break;
			case '?':
				printf("Argument error %c\n",c);
				optind = 1;
			return 1;
		}
	}

	nrFiles = argc-optind;
	mFiles = (int*) malloc(sizeof(int) * nrFiles);

	if (aflag != 1) //if flag a isn't set, open each file in mode 'w' to delete any information found within
		for(j=0; j<nrFiles; j++) {
			if ((mFiles[j] = open(argv[j+optind],O_WRONLY | O_CREAT | O_TRUNC,S_IRWXU)) == -1) {
				printf("Could not open file: %s\n", argv[j+optind]);
				optind = 1;
				return 2;
			}
			//write(mFiles[j], " ", 1);
			//printf("%s\n", argv[j+optind]);
			close(mFiles[j]);
		}

	while(!feof(stdin)) { 	//reads stdin up to infinity then writes into files
		sstr = malloc(sizeof(char)*1000);
		//fgets(string(sstr), sizeof(sstr), stdin);
		gets(sstr);	//fgets(string sstr, sizeof(sstr), stdin)

		for(j=0; j<nrFiles; j++) {
			if ((mFiles[j] = open(argv[j+optind],O_WRONLY | O_APPEND)) == -1) {
				printf("Could not open file: %s\n", argv[j+optind]);
				optind =1;
				return 3;
			}
			write(mFiles[j], sstr, strlen(sstr));
			write(mFiles[j], "\n", 1);
			close(mFiles[j]);
		}

		printf("%s\n",sstr);
	}

	optind = 1;
	return 0;
}

int Yes(int argc, char*argv[]) {
    char *s;
	int i=1, j=0;

	if(argc<2) { //in case there are no arguments print 'y' infinitely
        while (1)
            printf("y\n");
    } else { //if there are arguments on the command line
        for (i; i<argc; i++)
            j += strlen(argv[i]);
	    s = (char*) malloc(sizeof(char)*j + argc);
	    j=0;
		for(i=1; i<argc; i++) { //concatenate all strings into one
            strcpy(&s[j], argv[i]);
            j = strlen(s);
            strcpy(&s[j], " ");
            j = strlen(s);
		}
	}

	while (!feof(stdin))
        printf("%s\n", s);
    free(s);
	return 0;
}

int Ls(int argc, char* argv[]) {
	int c;
	int lf=0,sf=0,af=0,Ff=0;
	int i=0,sum=0;
	int counter = 0;
	char * mRootPath;
	char ** paths;
	char * buffer;
	struct dirent *dptr;

	while ((c = getopt(argc, argv, "lsaF")) != -1) {
		switch(c) {
			case 'l':
				lf = 1;
				break;
			case 's':
				sf = 1;
				break;
			case 'a':
				af = 1;
				break;
			case 'F':
				Ff = 1;
				break;
			case '?':
				optind =1;
				return(2);
			default :
				optind =1;
	            return(2);
		}
	}

	mRootPath = getcwd(NULL, 0);

	if((argc-optind)==0) {
		paths =(char**)malloc(sizeof(char*));
		paths[0] = getcwd(NULL, 0);
		counter++;
	} else {
		paths = (char **) malloc (sizeof(char*) * argc);

		for(i = optind; i < argc; i++) {

			if((buffer = realpath(argv[i],NULL))== NULL) {
				printf("Entered wrong path!");
				exit(0);
			}

			struct stat * p_stat = (struct stat*)malloc(sizeof(struct stat));
			if(stat(buffer, p_stat) != 0) {
				printf("Error!");
				exit(1);
			}
			if(!S_ISDIR(p_stat->st_mode)) {
				printf("Error abs_path not directory!");
				exit(2);
			}

			paths[counter] = (char *) malloc(sizeof(char) *(strlen(buffer)+1 ) );
			strcpy (paths[counter],buffer);
			++counter;

			free(buffer);
		}
	}

	for(i=0;i<counter;++i) {

				DIR *dir;
				struct stat     statbuf;
				struct passwd  *pwd;
				struct group   *grp;
				struct tm      *tm;
				char            datestring[256];

				if((dir=opendir(paths[i]))==NULL) {
					printf("Error at launch");
					exit(3);
				}
				chdir(paths[i]);
				while((dptr=readdir(dir))!=NULL) {
					if(dptr->d_name[0] == '.' && af==0)
						continue;
					stat(dptr->d_name, &statbuf);


					if(sf==1) {

					  		printf("%5jd ",(statbuf.st_blocks)/2);
							sum=sum+(statbuf.st_blocks)/2;

					}

					if(lf==1) {

						if(S_ISDIR(statbuf.st_mode)) printf("d"); else printf("-");
						if(statbuf.st_mode & S_IRUSR) printf("r"); else printf("-");
						if(statbuf.st_mode & S_IWUSR) printf("w"); else printf("-");
						if(statbuf.st_mode & S_IXUSR) printf("x"); else printf("-");
						if(statbuf.st_mode & S_IRGRP) printf("r"); else printf("-");
						if(statbuf.st_mode & S_IWGRP) printf("w"); else printf("-");
						if(statbuf.st_mode & S_IXGRP) printf("x"); else printf("-");
						if(statbuf.st_mode & S_IROTH) printf("r"); else printf("-");
						if(statbuf.st_mode & S_IWOTH) printf("w"); else printf("-");
						if(statbuf.st_mode & S_IXOTH) printf("x"); else printf("-");

    					printf(" %ld", statbuf.st_nlink);

    					if ((pwd = getpwuid(statbuf.st_uid)) != NULL)
        					printf(" %s", pwd->pw_name);
    					else
        					printf(" %d", statbuf.st_uid);

    					if ((grp = getgrgid(statbuf.st_gid)) != NULL)
        					printf(" %s", grp->gr_name);
    					else
        					printf(" %d", statbuf.st_gid);


						printf(" %3jd",statbuf.st_size);

						// or printf(" %s",ctime(&statbuf.st_mtime));
           				tm = localtime(&statbuf.st_mtime);
         				strftime(datestring, sizeof(datestring), nl_langinfo(D_T_FMT), tm);
         				printf(" %s", datestring);

					}


					printf(" %s",dptr->d_name);

					if(Ff==1) {
						if(S_ISDIR(statbuf.st_mode))
							printf("/");
						if(S_ISFIFO(statbuf.st_mode))
							printf("|");
						if(S_ISLNK(statbuf.st_mode))
							printf("@");
						if(S_ISSOCK(statbuf.st_mode))
							printf("=");
						if(statbuf.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH)) {
							if(S_ISDIR(statbuf.st_mode)) {}
							else
								printf("*");
						}

					}
					printf("\n");

				}

				closedir(dir);
	}

	if(lf==1)
	printf("Total %d\n",sum);

	chdir(mRootPath);
	free(mRootPath);
	free(paths);
	optind =1;
	return 0;
}

int Dir(int argc, char * argv[]) {
	int i=0;
	int counter = 0;
	char ** paths;
	char * buffer;
	struct dirent *dptr;

	if(argc==1) {
		paths =(char**)malloc(sizeof(char*));
		paths[0] = getcwd(NULL, 0);
		counter++;
	} else {
		paths = (char **) malloc (sizeof(char*) * argc);

		for(i = 1; i < argc; i++) {

			if((buffer = realpath(argv[i], NULL))== NULL) {
				printf("Entered wrong path!");
				exit(0);
			}

			struct stat * p_stat = (struct stat*)malloc(sizeof(struct stat));
			if(stat(buffer, p_stat) != 0) {
				printf("Error!");
				exit(1);
			}
			if(!S_ISDIR(p_stat->st_mode)) {
				printf("Error abs_path not directory!");
				exit(2);
			}

			paths[counter] = (char *) malloc(sizeof(char) *(strlen(buffer)+1 ) );
			strcpy (paths[counter],buffer);
			++counter;

		}

		free(buffer);
	}

	for(i=0;i<counter;++i) {

				DIR *dir;

				if((dir=opendir(paths[i]))==NULL) {
					printf("Error at launch");
					exit(3);
				}
				while((dptr=readdir(dir))!=NULL) {
					if (dptr->d_name[0] != '.')
						printf("%s\n",dptr->d_name);
				}
				closedir(dir);
	}

	free(paths);

	return 0;

}

int Help(int argc, char *argv[]) {

	if (argc < 2) {
		printf("\nThe following commands are defined. Type \"help\" to get this message.\n");
		printf("\ncat [-b] [-n] [-E] [-s] [FILE]..");
		printf("\ntee [-a] [FILE]..");
		printf("\nyes [ARGS]..\n");
		printf("\ndir [FILE]");
		printf("\nls  [-l] [-a] [-s] [-F] [FILE]..");
		printf("\ntac [-b]  [FILE]..");
        printf("\nUse help [command] for more information about a specific command.\n\n");
	} else {
		if (strcmp("cat", argv[1]) == 0) {
			printf("\nSyntax\n\tcat [Options] [File]...\n\nConcatenate FILE(s), or standard input, to standard output.\n");
			printf("\n-b\tnumber nonblank output lines\n");
			printf("-E\tdisplay $ at end of each line\n");
			printf("-n\tnumber all output lines\n");
			printf("-s\tnever more than one single blank line\n\n");
		} else if (strcmp("tee", argv[1]) == 0) {
		    printf("\nSyntax\n\ttee [Options] [File]...\n\nRedirect output to multiple files, copies standard input to standard output and also to any files given as arguments.\n");
			printf("-a\tAppend standard input to the given files rather than overwriting them.\n\n");
		} else if (strcmp("yes", argv[1]) == 0) {
			printf("\nSyntax\n\tyes [Args]\n\nPrints the arguments separated by spaces and followed by a newline, forever until it is killed.\nIf no arguments are given, it prints `y' followed by a newline forever until killed.\n\n");
		}
          else if(strcmp("dir", argv[1]) == 0) {
            printf("\nSyntax\n\tdir [File]... \n\nList directory contents\n");
        }
          else if(strcmp("ls", argv[1]) == 0) {
            printf("\nSyntax\n\tls [Options] [File]... \n\nList directory contents\n");
            printf("-a\tDo not hide entries starting with\n");
            printf("-s\tPrints size of each file, in blocks\n");
            printf("-l\tUses a long listing format\n");
            printf("-F\tAppends indicator (one of */=@|) to entries\n");
        }
          else if(strcmp("tac", argv[1]) == 0) {
            printf("\nSyntax\n\ttac [Options][File]... \n\nConcatenate and print files in reverse\n");
            printf("-b\tAttach the separator before instead of after\n");
        }
	}
	return 0;
}

int Version(int argc, char *argv[]) {
	printf("\nVersion 0.7c\nWritten by Robert Muschong\n\n");
	return 0;
}
