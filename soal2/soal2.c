#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>


int main() {
  pid_t pid, sid;

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

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while(1) {
	struct stat status;
	struct group *group;
	struct passwd *pass;
	char fname[255][255];
	int i;

	stat("elen.ku",&status);
	chmod("elen.ku", S_IRWXU | S_IRWXG | S_IRWXO);

	uid_t userid = status.st_uid;
	gid_t groupid = status.st_gid;
	group = getgrgid(groupid);
	pass = getpwuid(userid);

	if(strcmp(group->gr_name,"www-data") == 0 && strcmp(pass->pw_name,"www-data") == 0){
		remove("elen.ku");
		}
	}
	sleep(3);
}


