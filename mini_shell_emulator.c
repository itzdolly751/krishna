#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_CMD_LENGTH 1024
#define MAX_ARGS 100
void execute_command(char *cmd);
void parse_and_execute(char *input);
void cd_command(char *path);
int main() {
    char input[MAX_CMD_LENGTH];

    while (1) {
        printf("$ ");
        if (!fgets(input, sizeof(input), stdin)) {
            break;
        }
        input[strcspn(input, "\n")] = 0;
        parse_and_execute(input);
    }

    return 0;
}
void parse_and_execute(char *input) {
    char *args[MAX_ARGS];
    char *cmd = strtok(input, " "); 
    int arg_count = 0;
    while (cmd != NULL && arg_count < MAX_ARGS) {
        args[arg_count++] = cmd;
        cmd = strtok(NULL, " ");
    }
    args[arg_count] = NULL; 
    if (args[0] != NULL) {
        if (strcmp(args[0], "exit") == 0) {
            exit(0);
        } else if (strcmp(args[0], "cd") == 0) {
            if (arg_count > 1) {
                cd_command(args[1]);
            } else {
                fprintf(stderr, "cd: missing argument\n");
            }
        } else {
            execute_command(args);
        }
    }
}
void execute_command(char *args[]) {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork failed");
        return;
    }

    if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            perror("command execution failed");
            exit(1);
        }
    } else {
        wait(NULL);
    }
}
void cd_command(char *path) {
    if (chdir(path) != 0) {
        perror("cd failed");
    }
}
