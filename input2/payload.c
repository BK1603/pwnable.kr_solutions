#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>

int main() {
  int in_fd = open("/tmp/bk/temp2", O_RDONLY);
  int err_fd = open("/tmp/bk/temp3", O_RDONLY);

  dup2(in_fd, 0);
  dup2(err_fd, 2);
  close(in_fd);
  close(err_fd);

  char *argv[101];
  for(int i = 0; i < 101; i++)
    argv[i] = "A";
  argv[0] = "/home/input2/input";
  argv['A'] = "\x00";
  argv['B'] = "\x20\x0a\x0d";
  argv['C'] = "2020";
  argv[100] = 0;
  char *envp[] = {"\xde\xad\xbe\xef=\xca\xfe\xba\xbe", 0};

  FILE *fp = fopen("\x0a", "w");
  fwrite("\x00\x00\x00\x00", 4, 1, fp);
  fclose(fp);
  execve(argv[0], argv, envp);
  return -1;
}
