#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char** argv)
{
    if (argc < 3) {
        printf("please provide at least two arguments, like `find . b`");
        exit();
    }

    char* path = argv[1];
    char* target = argv[2];

    int fd;
    fd = open(path, 0);
    if (fd < 0) {
        printf("can't open %s\n", path);
        exit();
    }
    
}
