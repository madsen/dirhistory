//--------------------------------------------------------------------
// $Id$
//--------------------------------------------------------------------
//   Directory History
//
//   Copyright 2004 by Christopher J. Madsen
//
//   Standard header for C++ programs
//
//--------------------------------------------------------------------

#ifndef INCLUDED_STDINC_HPP
#define INCLUDED_STDINC_HPP

#include <algorithm>
#include <list>
#include <fstream>
#include <iostream>
#include <string>

//--------------------------------------------------------------------
using namespace std;

typedef string  String;

typedef String::size_type      StrIdx;
typedef String::iterator       StrItr;
typedef String::const_iterator StrConstItr;

//--------------------------------------------------------------------
// Lists:

typedef list<String>                     StrList;
typedef StrList::iterator                SLItr;
typedef StrList::const_iterator          SLConstItr;
typedef StrList::reverse_iterator        SLRItr;
typedef StrList::const_reverse_iterator  SLConstRItr;

typedef StrList::size_type               ListSize;

#endif // INCLUDED_STDINC_HPP
