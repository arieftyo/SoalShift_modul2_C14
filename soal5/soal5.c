#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>

int main() {
  pid_t pid, sid,child;
  int status;
  static int  urutan ;
  urutan = 0;
  char a[100];
  char letak[150]="/home/ariefp/praktikum/";
  char file[100];
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  pid = fork();
  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();

  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/home/ariefp/praktikum")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

while(1){
  if(urutan%30==0){
    child= fork();
    if(child==0){
        char a[100];
        time_t now = time(NULL);
        strftime(a, 20, "%d:%m:%Y-%H:%M", localtime(&now));
        char *argv[3] = {"mkdir", a, NULL};
  	execv("/bin/mkdir", argv);
    }
  }
  urutan ++;
  child= fork();
  if(child ==0){
   sprintf(file, "/log%d", urutan);
   strcat(letak, a);
   strcat(letak, file);
   strcat(letak, ".log");
   char *argv[4]= {"cp", "/var/log/syslog", letak, NULL};
   execv("/bin/cp", argv);
  }
  sleep(60);
 }
 exit(EXIT_SUCCESS);
}
