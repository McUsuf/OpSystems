#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <getopt.h>

#include <sys/types.h>
#include <unistd.h>

#include <ulimit.h>

#include <sys/time.h>
#include <sys/resource.h>

int main(int argc, char* argv[], char* envp[]) {
	if (argc == 1) {
		printf("No options\n");
		exit(0);
	}

	const char valid_options[] = "ispuU:cC:dvV:";

	int result = 0;

	struct rlimit rlim;

	char buffer[1024];

	char* env_opt;

	int i;

	long value;

	while ((result = getopt(argc, argv, valid_options)) != -1) {
		switch (result) {
		case 'i':
			printf("Real UID\t= %d\n", getuid());
			printf("Effective UID\t= %d\n", geteuid());
			printf("Real GID\t= %d\n", getgid());
			printf("Effective GID\t= %d\n", getegid());
			break;
		case 's':
			setpgid(0, 0);
			break;
		case 'p':
			printf("PID\t= %d\n", getpid());
			printf("PPID\t= %d\n", getppid());
			printf("PGID\t= %d\n", getpgid(0));
			break;
		case 'u':
			printf("Ulimit size\t %ld\n", ulimit(UL_GETFSIZE));
			break;
		case 'U':
			value = atol(optarg);
			if (value == 0) printf("Wrong value\n");
			else ulimit(UL_SETFSIZE, atol(optarg));
			break;
		case 'c':
			getrlimit(RLIMIT_CORE, &rlim);
			printf("rlim_cur\t= %d\n", rlim.rlim_cur);
			printf("rlim_max\t= %d\n", rlim.rlim_max);
			break;
		case 'C':
			value = atol(optarg);
			if (value == 0) printf("Wrong value\n");
			else {
				rlim.rlim_cur = atol(optarg);
				rlim.rlim_max = atol(optarg);
				setrlimit(RLIMIT_CORE, &rlim);
			}
			break;
		case 'd':
			getcwd(buffer, 1024);
			printf("Current working directory\t=  %s\n", buffer);
			break;
		case 'v':
			for (i = 0; envp[i] != NULL; i++)
				printf("\n%s", envp[i]);
			break;
		case 'V':
			env_opt = optarg;
			putenv(env_opt);
			
			/*char* tmp = getenv(strtok(env_opt," ="));
			if (tmp == NULL)
			{
				printf("\n!!!%s is not set!!!\n", strtok(env_opt, " ="));
				return;
			}
			printf("\n!!!%s=%s!!!\n", strtok(env_opt, " ="), tmp);
			*/
			break;
		}
	}
	return 0;
}