#include <signal.h>
#include <stdio.h>
#include <sys/tty.h>
#include <sys/types.h>

#define TTYHOG 4096

int fd[2];
char pids[TTYHOG];
int slave_count;
/*
 * программа обработки сигнала SIGTERM
 */
void service() 
{
  int n;
  char buffer[TTYHOG];
  signal(SIGTERM, service);
  n = read(fd[0], buffer, TTYHOG);
  write(1, buffer, n);
}
/*
 * программа завершения по сигналу SIGFPE
 */
void sdrop() 
{
  signal(SIGFPE, sdrop);
  if (--slave_count == 0)
    exit(0);
}
/*
 * программа инициализации потомка
 */
void slave(char *tty) 
{
  int id = fork();
//  id = fork();
  if(id) printf("My PID: %d\n", id);
  if (id == 0) 
  { /* переназначение стандартного ввода на терминал */
    int tfd;
    close(0);
    tfd = open(tty, 0);
    if (tfd != 0) 
    {
      printf("bad tty %S\n", tty);
      exit(1);
    }
    
    
    /* переназначение стандартного вывода на канал */
    dup(fd[1]);
    close(fd[0]);
    close(fd[1]);
    /* вызов потомка */

    execl("./child", "child", pids, 0);
    printf("can't exec slave on %S\n", tty);
    exit(1);
  }
}

/*
 * основная программа
 */
int main(int argc,char  *argv[]) 
{
  int i;
  signal(SIGTERM, service);
  signal(SIGFPE, sdrop);
  sprintf(pids, "%06d", getpid());
  pipe(fd);
  slave_count = argc - 1;
  for (i = 1; i < argc; i++)
    slave(argv[i]);
  close(fd[1]);
  for (;;)
    pause();
}