#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

int main()
{

    char cadena[512];
    printf("sh>");
    fflush(stdout);
    fgets(cadena, 512, stdin);

    char *args[32] = {NULL};
    int i = 0;
    for (char *p = strtok(cadena, " \n"); p; p = strtok(NULL, " \n"), i++)
    {
        args[i] = p;
    }
    bool isamp = false;

    if (strcmp(args[i - 1], "&") == 0)
    {
        isamp = true;
    }
    int pids=0;
    while ((strcmp(cadena, "exit") != 0) && strcmp(cadena, "shutdown") != 0)
    {
        pids = fork();
        if (pids== 0)
        {
            execvp(args[0], args);
            kill(getpid(), SIGKILL);
        }
        if (!isamp)
        {
            wait(NULL);
        }
        printf("sh>");
        fflush(stdout);
        fgets(cadena, 512, stdin);
        int i = 0;
        memset(args, 0, 32 * sizeof(char *));

        for (char *p = strtok(cadena, " \n"); p; p = strtok(NULL, " \n"), i++)
        {
            args[i] = p;
        }
        isamp = false;
        if (strcmp(args[i - 1], "&") == 0)
        {
            isamp = true;
        }
        
    }
    if (strcmp(cadena, "shutdown") == 0)
    {
        kill(getppid(), SIGUSR1);
    }
    if (strcmp(cadena, "exit") == 0)
    {
        kill(pids,SIGKILL);
        //kill(getpgrp(), SIGKILL);
    }
}