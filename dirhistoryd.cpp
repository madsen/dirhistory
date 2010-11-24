//--------------------------------------------------------------------
//   Directory History
//
//   Copyright 2004 by Christopher J. Madsen
//
//   Daemon that maintains a shared directory history
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
//--------------------------------------------------------------------

#include "stdinc.hpp"

//--------------------------------------------------------------------
const ListSize  maxHistory = 500;

//====================================================================
int main(int argc, char* argv[])
{
  if (argc != 3) {
    cerr << "Usage:  dirhistoryd INFIFO OUTFIFO\n";
    return 1;
  }

  const char *const  inFifoName  = argv[1];
  const char *const  outFifoName = argv[2];
  ifstream  inFifo;

  String  input;
  StrList history;

  for (;;) {
    inFifo.open(inFifoName);

//    cerr << "Opened inFifo\n";

    while (getline(inFifo, input).good()) {
      if (input.empty()) continue;

      if (input[0] == ':') {
        // Command
        if (input.compare(0, 6, ":list:") == 0) {
          const String current(input, 6, String::npos);
          ofstream  out(outFifoName);
          for (SLConstItr s = history.end(); s != history.begin(); ) {
            if (*(--s) != current)
              out << *s << '\n';
          }
        } // end if :list:
      } else {
        SLItr  old = find(history.begin(), history.end(), input);
        if (old != history.end())
          history.erase(old);
        else while (history.size() >= maxHistory)
          history.pop_back();
        history.push_front(input);
      }
    } // end while getline

    inFifo.close();
    inFifo.clear();
  } // end forever

  return 0;
} // end main

// Local Variables:
//  c-file-style: "cjm"
//  compile-command: "g++ -o dirhistoryd dirhistoryd.cpp"
// End:
