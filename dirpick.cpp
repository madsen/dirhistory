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

#include <menu.h>

const int
  cmdSelect = MAX_COMMAND + 1,
  cmdCancel = MAX_COMMAND + 2;

//#undef NCURSES_MOUSE_VERSION
typedef ITEM *ITEMPTR;

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

static int
menu_virtualize(int c)
{
  if (c == '\n' || c == KEY_EXIT)
    return cmdSelect;
  else if (c == '\e')
    return cmdCancel;
  else if (c == 'u')
    return (REQ_SCR_ULINE);
  else if (c == 'd')
    return (REQ_SCR_DLINE);
  else if (c == 'b' || c == KEY_NPAGE)
    return (REQ_SCR_UPAGE);
  else if (c == 'f' || c == KEY_PPAGE)
    return (REQ_SCR_DPAGE);
  else if (c == 'n' || c == KEY_DOWN)
    return (REQ_NEXT_ITEM);
  else if (c == 'p' || c == KEY_UP)
    return (REQ_PREV_ITEM);
  else {
//    if (c != KEY_MOUSE)
//      beep();
    return (c);
  }
}

void dir_menu(StrList& history, String& choice)
{
  choice.erase();

  ITEMPTR* items = new ITEMPTR[history.size() + 1];

#ifdef NCURSES_MOUSE_VERSION
  mousemask(ALL_MOUSE_EVENTS, (mmask_t *) 0);
#endif

  ITEMPTR* ip = items;
  for (SLConstItr s = history.begin(); s != history.end(); ++s)
    *(ip++) = new_item(s->c_str(), "");
  *ip = NULL;

  MENU* m = new_menu(items);

  int mrows, mcols;
  set_menu_format(m, 10, 1);
  scale_menu(m, &mrows, &mcols);

  WINDOW* menuwin = newwin(mrows + 2, mcols + 2, 2, 10);
  set_menu_win(m, menuwin);
  keypad(menuwin, TRUE);
  box(menuwin, 0, 0);

  set_menu_sub(m, derwin(menuwin, mrows, mcols, 1, 1));
  set_current_item(m, ip[-1]);
  post_menu(m);

  for (;;) {
    int cmd = menu_virtualize(wgetch(menuwin));
    int result = menu_driver(m, cmd);

    if (result == E_UNKNOWN_COMMAND) {
      if (cmd != cmdCancel)
        choice.assign(item_name(current_item(m)));
      break;
    }
//    else if (result == E_REQUEST_DENIED)
//      beep();
  } // end forever

  unpost_menu(m);
  delwin(menuwin);

  free_menu(m);
  for (ip = items; *ip; ip++)
    free_item(*ip);
  delete[] items;

#ifdef NCURSES_MOUSE_VERSION
  mousemask(0, (mmask_t *) 0);
#endif
} // end dir_menu

int main(int argc, char* argv[])
{
  StrList history;

  if (argc != 3) return(2);

  get_history(history, argv[1], argv[2]);
  if (history.empty()) return(1);

  SCREEN* screen = newterm(NULL, stderr, stdin);
  set_term(screen);
  keypad(stdscr, TRUE);
  nonl();
  cbreak();

  String choice;
  dir_menu(history, choice);

  endwin();

  if (!choice.empty()) {
    cout << choice << endl;
  }

  return 0;
} // end main

// Local Variables:
//  c-file-style: "cjm"
//  compile-command: "g++ -o dirpick dirpick.cpp -lmenu -lncurses"
// End:
