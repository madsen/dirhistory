//--------------------------------------------------------------------
// $Id$
//--------------------------------------------------------------------
//   Directory History
//
//   Copyright 2004 by Christopher J. Madsen
//
//   Display the history list so the user can pick one
//
//--------------------------------------------------------------------

#include "stdinc.hpp"

#include <cdk/cdk.h>

#ifdef HAVE_XCURSES
char *XCursesProgramName="dirpick";
#endif

void get_history(StrList& history, const char* cmdFifo, const char* listFifo)
{
  char  current[256];
  if (!getcwd(current, sizeof(current)-1))
    current[0] = '\0';

  String buf(":list:");
  buf += current;
  buf += '\n';

  ofstream  daemon(cmdFifo);
  daemon << buf;
  daemon.close();

  ifstream  in(listFifo);

  while (getline(in, buf).good()) {
    history.push_back(buf);
  }
} // end get_history

//--------------------------------------------------------------------
static int myPreProcess(EObjectType cdkType GCC_UNUSED, void *object,
                        void *clientData GCC_UNUSED, chtype input)
{
  chtype  newChar = 0;

  switch (input) {
   case 'p':
   case 'P':
   case CONTROL('P'):  newChar = KEY_UP;    break;

   case 'n':
   case 'N':
   case CONTROL('N'):  newChar = KEY_DOWN;  break;
  } // end switch input

  if (newChar) {
    injectCDKScroll(reinterpret_cast<CDKSCROLL*>(object), newChar);
    return 0;
  }

  return 1;
} // end myPreProcess

//--------------------------------------------------------------------
void dir_menu(CDKSCREEN* cdkscreen, StrList& history, String& choice)
{
  choice.erase();

  // Create the scrolling list:
  int count = history.size();
  const char** item = new const char*[count];
  const char** d = item;

  for (SLConstItr s = history.begin(); s != history.end(); ++s, ++d)
    *d = s->c_str();

  CDKSCROLL *scrollList	= newCDKScroll(cdkscreen, CENTER, CENTER, RIGHT,
                                       -1, -2, "<C></5>Directory History",
                                       const_cast<char**>(item), count,
                                       false, A_REVERSE, true, false);
  if (!scrollList) return;
  setCDKScrollPreProcess(scrollList, myPreProcess, 0);

  // Activate the scrolling list:
  setCDKScrollCurrent(scrollList, count-1);
//  setCDKScrollBackgroundColor(scrollList, "</5>");
  int selection = activateCDKScroll(scrollList, 0);

  // Get the selected directory (if any):
  if (scrollList->exitType == vNORMAL)
    choice.assign(item[selection]);

  // Clean up:
  destroyCDKScroll(scrollList);
  delete[] item;
} // end dir_menu

//--------------------------------------------------------------------
int main(int argc, char* argv[])
{
  StrList history;

  if (argc != 3) return(2);

  get_history(history, argv[1], argv[2]);
  if (history.empty()) return(1);

  /* Set up CDK. */
  SCREEN* screen = newterm(NULL, stderr, stdin);
  set_term(screen);
//  keypad(stdscr, TRUE);
//  nonl();
//  cbreak();

  WINDOW*     cursesWin = newwin(0,0,0,0);
  CDKSCREEN*  cdkscreen = initCDKScreen(cursesWin);

  /* Set up CDK Colors. */
  initCDKColor();
  use_default_colors();
  curs_set(0);

  String choice;
  dir_menu(cdkscreen, history, choice);

  destroyCDKScreen(cdkscreen);
  delwin(cursesWin);
  endCDK();

  if (!choice.empty()) {
    cout << choice << endl;
  }

  return 0;
} // end main

// Local Variables:
//  c-file-style: "cjm"
//  compile-command: "g++ -o dirpick dirpick.cpp -lcdk -lncurses"
// End:
