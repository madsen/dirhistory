//--------------------------------------------------------------------
//   Directory History
//
//   Copyright 2004 by Christopher J. Madsen
//
//   Standard header for C++ programs
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
