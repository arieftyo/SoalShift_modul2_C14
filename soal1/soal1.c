#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <dirent.h>

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
	DIR *d;
	struct dirent *dir;
	char fname[255][255];
	char fnew[255][255];
	char srcpath[255];
	char destpath[255];
	int i=0,j=0;

	d = opendir("campur2/");
	if (d != NULL){
		while ((dir = readdir(d)) != NULL){
			    strcpy(fname[i],dir->d_name);
			char *a = strrchr(dir->d_name, '.');
			if (strcmp(a, ".png") == 0){		
				strncpy(fnew[j], fname[i], (strlen(fname[i])-4));
				strcat(fnew[j], "_grey.png");			
				strcpy(srcpath,"campur2/");
				strcpy(destpath,"gambar/");
				strcat(srcpath, fname[i]);
				strcat(destpath, fnew[j]);


				rename(srcpath, destpath);		
				memset(srcpath, 0, sizeof srcpath);
				memset(destpath, 0, sizeof destpath);				
				j++;
		}
		i++;
	}
        closedir(d);
    }
    sleep(30);
  }
}
