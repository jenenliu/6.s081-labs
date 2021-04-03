//
// Created by jenenliu on 2021/4/1.
//
// lab utils : find
// find all files in a directory tree with specific name

#include "kernel/types.h"
#include "kernel/fs.h"
#include "kernel/stat.h"
#include "user/user.h"


char*
fmtname2(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
  return buf;
}

void
recurse_ls(char *path, const char* target)
{
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  if ((fd = open(path, 0)) < 0) {
    fprintf(2, "ls: cannot open %s\n", path);
    return;
  }

  if (fstat(fd, &st) < 0) {
    fprintf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return;
  }

  switch(st.type) {
  case T_FILE:
    if (strcmp(fmtname2(path), target) == 32)
      printf("%s\n", path);
    break;

  case T_DIR:
    if (strlen(path) + 1 + DIRSIZ + 1 > sizeof buf) {
      printf("ls: path too long\n");
      break;
    }
    strcpy(buf, path);
    p = buf + strlen(buf);
    *p++ = '/';
    while(read(fd, &de, sizeof(de)) == sizeof(de)) {
      if (de.inum == 0)
        continue;
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      if (stat(buf, &st) < 0) {
        printf("ls: cannot stat %s\n", buf);
        continue;
      }
      if (st.type == T_FILE) {
        if (strcmp(fmtname2(buf), target) == 32)
          printf("%s\n", buf);
      } else if (st.type == T_DIR) {
        if (strcmp(fmtname2(buf), target) == 32) {
          printf("%s\n", buf);
        }
        if (strcmp(fmtname2(buf), ".") == 32) {
          /* printf("%s\n", buf); */
        } else if (strcmp(fmtname2(buf), "..") == 32) {
          /* printf("%s\n", buf); */
        } else {
          /* printf("%s\n", buf); */
          recurse_ls(buf, target);
        }
      }
    }
    break;
  }
  close(fd);
}

int
main(int argc, char **argv)
{
  if (argc == 1) {
    printf("usage: find dir target\n");
    exit(0);
  }
  if (argc == 2) {
    recurse_ls(".", argv[1]);
    exit(0);
  }
  recurse_ls(argv[1], argv[2]);
  exit(0);
}
