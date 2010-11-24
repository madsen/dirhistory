/*--------------------------------------------------------------------
//   Directory History
//
//   Copyright 2004 by Christopher J. Madsen
//
//   Notify daemon of directory change
//
//   This program is free software; you can redistribute it and/or
//   modify it under the terms of the GNU General Public License as
//   published by the Free Software Foundation; either version 2 of
//   the License, or (at your option) any later version.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public License
//   along with this program.  If not, see <http://www.gnu.org/licenses/>.
//--------------------------------------------------------------------*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char* argv[])
{
  int fd;
  int len;
  int i;

  /* Since this program is non-critical and runs as part of the bash prompt,
   * it doesn't attempt to report errors. */

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
