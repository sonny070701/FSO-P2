#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

void sig_handler(int signo)
{
    if (signo == SIGUSR2)
    {
        killpg(getpgrp(), SIGTERM);
		kill(getpid(),SIGTERM);
    }
}
int main() {
	if (signal(SIGUSR2, sig_handler) == SIG_ERR)
    {
        perror("Error al instalar el manejador de señal\n");
    }
	for(int i = 0; i < 6; i++) {
		
		if(fork() == 0) {
			execlp("xterm","xterm","-e","./getty","getty", NULL);
		}
	}
	while (1)
	{
		wait(NULL);
		if(fork() == 0) {
			execlp("xterm","xterm","-e","./getty","getty", NULL);
		}
	}
	
}