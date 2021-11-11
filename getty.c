#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

void sig_handler(int signo)
{
    if (signo == SIGUSR1)
    {
        int pidinit = 0;
        char buffer[2048];
        sprintf(buffer, "/proc/%d/stat", getppid());
        FILE *pidfile = fopen(buffer, "r");
        if (pidfile)
        {
            size_t size = fread(buffer, sizeof(char), sizeof(buffer), pidfile);
            if (size > 0)
            {
                strtok(buffer, " ");
                strtok(NULL, " "); 
                strtok(NULL, " "); 
                char *pidin = strtok(NULL, " ");
                pidinit = atoi(pidin);
            }
            killpg(pidinit, SIGUSR2);
        }

        //
    }
}

int main()
{
    if (signal(SIGUSR1, sig_handler) == SIG_ERR)
    {
        perror("Error al instalar el manejador de señal\n");
    }
    char usr[50];
    char psswd[50];

    char *contenido_arch = NULL;
    size_t len = 0;
    bool correcto = false;
    while (true)
    {

        FILE *passwd = fopen("passwd.txt", "r");
        printf("User: "); 
        scanf("%s", usr);
        printf("Password:");
        scanf("%s", psswd); 
        strcat(usr, ":");
        strcat(usr, psswd); 

        while (getline(&contenido_arch, &len, passwd) != -1)
        {
            strtok(contenido_arch, "\n");
            
            if (strcmp(usr, contenido_arch) == 0)
            {
                correcto = true;
                break;
            }
        }

        if (correcto == true)
        {

            if (fork() == 0)
            {
                execlp("./sh", "./sh", NULL);
            }
            wait(NULL);
            correcto = false;
        }
        fclose(passwd);
    }
}