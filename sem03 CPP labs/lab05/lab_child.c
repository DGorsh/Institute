#include <signal.h>
#include <sys/types.h>
#include <sys/tty.h>

#define TTYHOG 4096

int main (int argc,char *argv[])
{
    int n;
    char buffer[TTYHOG];
    for(;;)
    {
        n = read(0,buffer,TTYHOG);
        if(n == 0)
        { /* сброс из основной задачи */
            kill (atoi(argv[1]), SIGFPE);
            close(1);
            exit(0);
        }
        kill(atoi(argv[1]),SIGTERM);
        write(1, buffer, n);
    }
}
