#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main()
{
  int parent_fd[2];
  int child_fd[2];
  char buf[8];

  pipe(parent_fd);
  pipe(child_fd);

  int n;

  if (fork() == 0) {
    /* process in child */
    while ((n = read(parent_fd[0], buf, sizeof buf)) > 0) {
      printf("%d: received %s\n", getpid(), buf);
      break;
    }
    write(child_fd[1], "pong", 4);
    close(parent_fd[0]);
    close(child_fd[1]);
    exit();
  } else {
    write(parent_fd[1], "ping", 4);
    while ((n = read(child_fd[0], buf, sizeof buf)) > 0) {
      printf("%d: received %s\n", getpid(), buf);
      break;
    }
    close(parent_fd[1]);
    close(child_fd[0]);
    wait();
  }

  exit();
}
