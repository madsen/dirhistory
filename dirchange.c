//--------------------------------------------------------------------
// $Id$
//--------------------------------------------------------------------
//   Directory History
//
//   Copyright 2004 by Christopher J. Madsen
//
//   Notify daemon of directory change
//
//--------------------------------------------------------------------

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char* argv[])
{
  int fd;
  int len;
  int i;

  if (argc < 3) return 2;

  fd = open(argv[1], O_WRONLY | O_NONBLOCK);

  if (fd == -1) return 3;

  for (i = 2; i < argc; ++i) {
    len = strlen(argv[i]);
    argv[i][len] = '\n';

    write(fd, argv[i], len+1);
  } /* end for each argument */

  close(fd);

  return 0;
} /* end main */

/* Local Variables: */
/* compile-command: "gcc -o dirchange dirchange.c" */
/* End: */
