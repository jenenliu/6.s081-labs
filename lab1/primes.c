#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main()
{
  int numbers[34] = {2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,
                     22,23,24,25,26,27,28,29,30,21,32,33,34,35};
  int buf;
  int first_pipe_fd[2];
  int n;
  pipe(first_pipe_fd);

  if (fork() > 0) {
    /* process in child */
    close(first_pipe_fd[0]);
    for (int i = 0; i < 34; i++) {
      write(first_pipe_fd[1], &numbers[i], 4);
    }
    wait();
  } else {
      close(first_pipe_fd[1]);
      int my_prime = 0;
      while((n = read(first_pipe_fd[0], &buf, sizeof buf)) > 0) {
          if (my_prime == 0) {
              my_prime = buf;
          } else if (my_prime == buf) {
              printf("prime %d\n", buf);
          } else if (buf % my_prime != 0) {
              fork();
          }
      }
      exit();
  }
  exit();
}
