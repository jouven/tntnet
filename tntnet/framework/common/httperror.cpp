/* httperror.cpp
   Copyright (C) 2003-2005 Tommi Maekitalo

This file is part of tntnet.

Tntnet is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

Tntnet is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with tntnet; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330,
Boston, MA  02111-1307  USA
*/

#include <tnt/httperror.h>

namespace tnt
{
  ////////////////////////////////////////////////////////////////////////
  // HttpError
  //

  static std::string httpErrorFormat(unsigned errcode, const std::string& msg)
  {
    char d[3];
    d[2] = '0' + errcode % 10;
    errcode /= 10;
    d[1] = '0' + errcode % 10;
    errcode /= 10;
    d[0] = '0' + errcode % 10;
    std::string ret(d, 3);
    ret += ' ';
    ret += msg;
    return ret;
  }

  HttpError::HttpError(unsigned errcode, const std::string& msg)
    : msg(httpErrorFormat(errcode, msg))
  {
  }

  std::string HttpError::getErrmsg() const
  {
    std::string::size_type p = msg.find('\n', 4);
    return p == std::string::npos ? msg.substr(4) : msg.substr(4, p - 4);
  }
}
