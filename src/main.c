// SPDX-FileCopyrightText: 2026 Minetomba <minetomba@proton.me>
// SPDX-License-Identifier: GPL-3.0-only
/* Includes */
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/* Configuration */
#define MAX_CMD_LENGTH 256
#define PROMPT "> "
#define SLEEP_FAIL_ERROR "Error: Not a number!\n"
#define MAX_PWD_LENGTH 256
#define PWD_FAIL_ERROR "Error: Directory does not exist or directory exceeds the set number of maximum characters for a directory in the shell configuration.\n"
#define COMMAND_NOT_FOUND_ERROR "Error: Command not found.\n"
#define MAX_ARGS 64
#define BINARY_NOT_FOUND_ERROR "Error: Binary not found.\n"
#define HELP_MESSAGE "exit > Make the shell exit\ncd [path] > Make the shell change directory to that path\npwd > Print the shell's current working directory\nexec [path] [args] > Execute the binary at that absolute path with those arguments\nbg [command] [args] > Run that command with those arguments in the background\nexecbg [path] [args] > Execute the binary at that absolute path in the background with the specified arguments\nhelp > Show this message\n[command] [args] > Run that command with those arguments, and wait for it to finish\n"

/* Main function */
int main() {
	while (1) {
		write(1, PROMPT, sizeof PROMPT - 1);
		char cmd[MAX_CMD_LENGTH];
		int n = read(STDIN_FILENO, cmd, sizeof cmd - 1);
		if (n < 1) {
			_exit(1);
		}
		cmd[n] = '\0';
		if (cmd[0] == 'e' && cmd[1] == 'x' && cmd[2] == 'i' && cmd[3] == 't' && (cmd[4] == ' ' || cmd[4] == 0 || cmd[4] == '\n')) {
			_exit(0);
		} else if (cmd[0] == 'c' && cmd[1] == 'd' && cmd[2] == ' ') {
			char *arg = cmd + 3;
			arg[strcspn(arg, "\n")] = '\0';
			chdir(arg);
		} else if (cmd[0] == 'p' && cmd[1] == 'w' && cmd[2] == 'd' && (cmd[3] == ' ' || cmd[3] == 0 || cmd[3] == '\n')) {
			char output[MAX_PWD_LENGTH];
			if (getcwd(output, sizeof(output)) != NULL) {
				write(1, output, strlen(output));
				write(1, "\n", 1);
			} else {
				write(1, PWD_FAIL_ERROR, sizeof PWD_FAIL_ERROR - 1);
			}
		} else if (cmd[0] == 'e' && cmd[1] == 'x' && cmd[2] == 'e' && cmd[3] == 'c' && cmd[4] == ' ') {
			char *argv[MAX_ARGS];
			int argc = 0;
			char *tok = strtok(cmd, " \t\n");
			while (tok && argc < MAX_ARGS - 1) {
				argv[argc++] = tok;
				tok = strtok(NULL, " \t\n");
			}
			argv[argc] = NULL;
			for (int j = 0; j < MAX_ARGS - 1; j++) {
				argv[j] = argv[j + 1];
			}
			int pid = fork();
			if (pid == 0) {
				execve(argv[0], argv, NULL);
				write(1, BINARY_NOT_FOUND_ERROR, sizeof BINARY_NOT_FOUND_ERROR - 1);
				_exit(127);
			}
			waitpid(pid, NULL, 0);
		} else if (cmd[0] == 'b' && cmd[1] == 'g' && cmd[2] == ' ') {
			char *argv[MAX_ARGS];
			int argc = 0;
			char *tok = strtok(cmd, " \t\n");
			while (tok && argc < MAX_ARGS - 1) {
				argv[argc++] = tok;
				tok = strtok(NULL, " \t\n");
			}
			argv[argc] = NULL;
			for (int j = 0; j < MAX_ARGS - 1; j++) {
				argv[j] = argv[j + 1];
			}
			int pid = fork();
			if (pid == 0) {
				execvp(argv[0], argv);
				write(1, COMMAND_NOT_FOUND_ERROR, sizeof COMMAND_NOT_FOUND_ERROR - 1);
				_exit(127);
			}
		} else if (cmd[0] == 'e' && cmd[1] == 'x' && cmd[2] == 'e' && cmd[3] == 'c' && cmd[4] == 'b' && cmd[5] == 'g' && cmd[6] == ' ') {
			char *argv[MAX_ARGS];
			int argc = 0;
			char *tok = strtok(cmd, " \t\n");
			while (tok && argc < MAX_ARGS - 1) {
				argv[argc++] = tok;
				tok = strtok(NULL, " \t\n");
			}
			argv[argc] = NULL;
			for (int j = 0; j < MAX_ARGS - 1; j++) {
				argv[j] = argv[j + 1];
			}
			int pid = fork();
			if (pid == 0) {
				execve(argv[0], argv, NULL);
				write(1, BINARY_NOT_FOUND_ERROR, sizeof BINARY_NOT_FOUND_ERROR - 1);
				_exit(127);
			}
		} else if (cmd[0] == 'h' && cmd[1] == 'e' && cmd[2] == 'l' && cmd[3] == 'p' && (cmd[4] == ' ' || cmd[4] == 0 || cmd[4] == '\n')) {
			write(1, HELP_MESSAGE, sizeof HELP_MESSAGE - 1);
		} else {
			char *argv[MAX_ARGS];
			int argc = 0;
			char *tok = strtok(cmd, " \t\n");
			while (tok && argc < MAX_ARGS - 1) {
				argv[argc++] = tok;
				tok = strtok(NULL, " \t\n");
			}
			argv[argc] = NULL;
			int pid = fork();
			if (pid == 0) {
				execvp(argv[0], argv);
				write(1, COMMAND_NOT_FOUND_ERROR, sizeof COMMAND_NOT_FOUND_ERROR - 1);
				_exit(127);
			}
			waitpid(pid, NULL, 0);
		}
	}
	return 0;
}