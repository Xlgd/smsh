/* execute.c - code used by small shell to execute commands */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include "varlib.h"

extern char ** environ;
void redirect(char *, char *);

int execute(char * argv[], char *out, char *in, char * command2[]) {
    /* 
     * purpose: run a program passing it arguments
     * returns: status returned via wait, or -1 on error
     * errors: -1 on fork() or wait() errors
     */
    int pid;
    int child_info = -1;
    int thepipe[2]; /* two file descriptors */
    int pos = 0;

    if (argv[0] == NULL) {
        return 0;
    }

    while (argv[pos] != NULL) {
        printf("argv[%d]: %s\n", pos, argv[pos]);
        ++pos;
    }

    if (command2 != NULL) {
        if (pipe(thepipe) == -1) {
            perror("cannot get a pipe");
        }
        printf("thepipe[0]: %d, thepipe[1]: %d\n", thepipe[0], thepipe[1]);
        pos = 0;
        while (command2[pos] != NULL) {
            printf("command2[%d]: %s\n", pos, command2[pos]);
        ++pos;
        }
    }

    if ((pid = fork()) == -1) {
        perror("fork");
    }
    else if (pid == 0) {
        environ = VLtable2environ();
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        redirect(out, in);
        if (command2 != NULL) {
            close(thepipe[0]);
            if (dup2(thepipe[1], STDOUT_FILENO) == -1) {
                perror("could not duplicate thepipe[1] to STDOUT_FILENO");
            }
            close(thepipe[1]);
        }
        execvp(argv[0], argv);
        perror("cannot execute command");
        exit(1);
    }
    else {
        if (command2 != NULL) {
            close(thepipe[1]);
            if (dup2(thepipe[0], STDIN_FILENO) == -1) {
                perror("could not duplicate thepipe[0] to STDIN_FILENO");
            }
            close(thepipe[0]);
            execvp(command2[0], command2);
            perror("cannot execute command2");
            exit(1);
        }
        else if (wait(&child_info) == -1) {
            perror("wait");
        }
    }
    return child_info;
}