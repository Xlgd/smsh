# smsh
## a simple and small shell



- smsh.c: main

- builtin.c: deal with the builtin commands

- controlflow.c: deal with the if command

- execute.c: execute the commands

- process.c: detect the builtin commands, IO redirection and pipe

- redirect.c: deal with the IO redirection

- splitline.c: parse and separate the input string

- varlib.c: a simple storage system to store name=value pairs

use gcc smsh.c splitline.c execute.c process.c controlflow.c builtin.c varlib.c redirect.c -o smsh to make it