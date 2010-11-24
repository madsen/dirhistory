Directory History
=================

This collection of programs implements a shared directory history
inspired by the directory history window of
[JP Software's][jp] 4DOS & 4NT shells.

I've never gotten around to making this an easy-to-install utility, so
you'll have to customize the Bash scripts a bit for your system.  The
C & C++ programs should be ok as-is.  I'm currently using dirhistory
on Linux and Cygwin.

The compilation commands are in comments at the end of each program.
You'll need Mike Glover's [Curses Development Kit][cdk] and a curses library.

The programs are:

 * dirhistoryd.cpp

    This is the background daemon that maintains the directory
    history.  I normally leave it running as long as the machine is
    on.  When you log back in, your history is still there.

 * dirchange.c

    This tiny program is used to add directories to the history.  It
    runs automatically by a function added to your Bash prompt by cd.sh.

 * dirpick.cpp

    This Cdk-based program displays the directory history and lets you
    select a directory to change to.

 * startd.sh

    This script starts dirhistoryd in the background.  You'll need to
    customize it for your situation.

 * cd.sh

    This script is intended to be sourced in your .bashrc.  It
    arranges for dirchange to be run when you change directories and
    for dirpick to run when you use the cd_menu command.  It also
    binds Ctrl-PageUp to run cd_menu.  (You may need to change the
    keyboard shortcuts in your terminal emulator in order for
    Ctrl-PageUp to be passed through to Bash.)

 * PuTTY_ctrl_pageup.patch

    If you apply this patch to [PuTTY][pty], it will send the same
    sequence that Gnome Terminal does for Ctrl-PageUp.


Copyright and License
=====================

Copyright 2004 Christopher J. Madsen

These programs are free software; you can redistribute them and/or
modify them under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of
the License, or (at your option) any later version.

These programs are distributed in the hope that they will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with these programs.  If not, see <http://www.gnu.org/licenses/>.


  [cdk]: http://invisible-island.net/cdk/cdk.html
   [jp]: http://www.jpsoft.com/
  [pty]: http://www.chiark.greenend.org.uk/~sgtatham/putty/
