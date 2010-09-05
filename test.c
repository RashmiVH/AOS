#include <stdio.h>
#include <unistd.h>

void main()
{
pid_t p;
p=getpid();
printf("I am here %d\n",p);
fork();
p=getpid();
printf("I am here %d\n",p);
}
