//--------------------------------------------------------------------
// $Id$
//--------------------------------------------------------------------
//   Directory History
//
//   Copyright 2004 by Christopher J. Madsen
//
//   Daemon that maintains a shared directory history
//
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
