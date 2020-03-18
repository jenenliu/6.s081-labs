#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char** argv)
{
  if (argc <= 1) {
    printf("Please give sleep tick, for example: 'sleep 10'\n");
    exit();
  }

  int tick = atoi(argv[1]);
  if (tick == 0) {
    printf("wrong tick, aborted.\n");
    exit();
  }

  sleep(tick);

  exit();
}
