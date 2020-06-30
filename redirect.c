/* redirect.c-code for deal with the IO redirection*/

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "smsh.h"


void redirect(char *reoutfile, char *reinfile) {
    /* 
     * purpose: redirecting input and output
     * errors: If the dup2 function cannot be called properly, an error occurs
     * details: use dup2 to redirect 
     */
    int outfd;
    int newoutfd;
    int infd;
    int innewfd;

    if (reoutfile != NULL) {
        outfd = open(reoutfile, O_CREAT | O_RDWR | O_TRUNC, 0666);
        close(STDOUT_FILENO);
        newoutfd = dup2(outfd, STDOUT_FILENO);
        if (newoutfd != 1) {
            fatal("could not duplicate fd to 1", "", 1);
        }
        close(outfd);
    }
    
    if (reinfile != NULL) {
        infd = open(reinfile, O_RDONLY);
        close(STDIN_FILENO);
        innewfd = dup2(infd, STDIN_FILENO);
        if (innewfd != 0) {
            fatal("could not duplicate fd to 0", "", 1);
        }
        close(infd);
    }
}