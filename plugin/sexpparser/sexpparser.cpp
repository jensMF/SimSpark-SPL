/* -*- mode: c++; c-basic-offset: 4; indent-tabs-mode: nil -*-

   this file is part of rcssserver3D
   Fri May 9 2003
   Copyright (C) 2002,2003 Koblenz University
   Copyright (C) 2003 RoboCup Soccer Server 3D Maintenance Group
   $Id: sexpparser.cpp,v 1.1.2.1 2003/12/03 22:39:38 fruit Exp $

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; version 2 of the License.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/
#include "sexpparser.h"

using namespace oxygen;
using namespace std;

bool
SexpParser::IsString(const boost::any & operand)
{
    return boost::any_cast<std::string>(&operand);
}

BaseParser::TPredicateList
SexpParser::Parse(const std::string& input)
{
    size_t len = input.length();

    TPredicateList pList;
    if (len == 0) return pList;

    char* c = new char[len+1];
    input.copy(c,len);
    c[len] = '\0';

    pcont_t* pcont = init_continuation(c);
    sexp_t* sexp = iparse_sexp(c,len,pcont);

    TPredicate predicate;

    while (sexp != 0)
    {
        predicate = SexpToPlist(sexp);
        if (!predicate.name.empty())
        {
            pList.push_back(predicate);
        }
        destroy_sexp(sexp);
        sexp = iparse_sexp(c,len,pcont);
    }
    destroy_continuation(pcont);
    delete [] c;
    return pList;
}

std::string
SexpParser::Generate(const TPredicateList& input)
{
    string s;
    TPredicateList::const_iterator i = input.begin();

    while (i != input.end())
    {
        s += '(' + i->name +  " ";
        s += ListToString(i->parameter) + ')';
        ++i;
    }
    return s;
}

BaseParser::TParameterList
SexpParser::SexpToList(const sexp_t* const sexp)
{
    sexp_t* s = const_cast<sexp_t*>(sexp);

    TParameterList arguments;

    while (s != 0)
    {
        if (s->ty == SEXP_VALUE)
        {
            string elem(s->val);
            arguments.push_back(elem);
        } else {
            TParameterList elem = SexpToList(s->list);
            arguments.push_back(elem);
        }
        s = s->next;
    }
    return arguments;
}

BaseParser::TPredicate
SexpParser::SexpToPlist(const sexp_t* const sexp)
{
    TPredicate predicate;

    // throw away outer brackets (i.e. we have a list at the top level)
    if (sexp->ty == SEXP_LIST)
    {
        sexp_t* s = const_cast<sexp_t*>(sexp->list);

        if (s != 0 && s->ty == SEXP_VALUE)
        {
            predicate.name = string(s->val);
            predicate.parameter = SexpToList(s->next);
        }
    }
    return predicate;
}

std::string
SexpParser::ListToString(const TParameterList& lst)
{
    string s;
    string space;
    bool round1 = true;

    for (TParameterList::const_iterator i = lst.begin(); i != lst.end(); ++i)
    {
        if (IsString(*i))
        {
            s += space + boost::any_cast<string>(*i);
        } else {
            string t = ListToString(boost::any_cast<TParameterList>(*i));
            s += space + '(' + t + ')';
        }
        if (round1) space = " ";
    }
    return s;
}

std::string
SexpParser::PlistToString(const TPredicate& plist)
{
    string s = '(' + plist.name +  " ";
    s += ListToString(plist.parameter);
    return s + ')';
}

#if 0
int
main(int argc, char** argv)
{
    parse(argv[1]);
    return 0;
}
#endif

