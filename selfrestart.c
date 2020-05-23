#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define BUF_SIZE PATH_MAX

static char exe_path[BUF_SIZE];

/**
 * Finds the current's executable path
 */
static void get_dwm_path()
{
	struct stat s;
	ssize_t num_bytes;
	char *arg = "/proc/self/exe";

	if (lstat(arg, &s) == -1) {
		perror("lstat:");
		return;
	}
	if (!S_ISLNK(s.st_mode)) {
		fprintf(stderr, "Error: Is not a symbolic link!\n");
		exit(1);
	}

	num_bytes = readlink("/proc/self/exe", exe_path, BUF_SIZE - 1);
	if (num_bytes < 0) {
		perror("readlink:");
		memset(exe_path, 0, BUF_SIZE);
		return;
	}
	exe_path[num_bytes] = '\0';

	/*
	 * if the executable was deleted (e.g. because of recompile) the readlink
	 * path contains "... (deleted)", cut it from the string to ensure we'll be
	 * able to find the new executable
	 */
	char *tmp;
	if ((tmp = strstr(exe_path, "(deleted)")) != NULL)
		*(tmp-1) = '\0';

	fprintf(stdout, "link path: %s\n", exe_path);

	tmp = strdup(exe_path);
	if (tmp == NULL) {
		perror("strdup:");
		return;
	}

	if (realpath(tmp, exe_path) == NULL) {
		perror("realpath:");
		memset(exe_path, 0, BUF_SIZE);
		free(tmp);
		return;
	}

	free(tmp);
}

/**
 * Restarts the window manager if the path
 * to the exe can be found
 */
void self_restart(const Arg *arg)
{
	memset(exe_path, 0, sizeof(exe_path));
	get_dwm_path();

	if (strlen(exe_path) == 0)
		return;

	char * const argv[2] = { exe_path, NULL };

	execv(argv[0], argv);
}
