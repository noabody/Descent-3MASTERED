/* 
* Descent 3 
* Copyright (C) 2024 Parallax Software
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _MACROS_H
#define _MACROS_H

#ifdef __cplusplus
  #include <algorithm>
  #include <cmath>
  #include <type_traits>

  #ifdef min
    #undef min
  #endif
  #ifdef max
    #undef max
  #endif

  using std::min;
  using std::max;
  template <typename T, typename U, typename std::enable_if<!std::is_same<T, U>::value, int>::type = 0>
  constexpr auto min(const T& a, const U& b) -> typename std::common_type<T, U>::type {return (a < b) ? a : b;}
  template <typename T, typename U, typename std::enable_if<!std::is_same<T, U>::value, int>::type = 0>
  constexpr auto max(const T& a, const U& b) -> typename std::common_type<T, U>::type {return (a > b) ? a : b;}
#else
  #ifndef max
  #define max(a,b) (((a) > (b)) ? (a) : (b))
  #endif
  #ifndef min
  #define min(a,b) (((a) < (b)) ? (a) : (b))
  #endif
#endif

#define SWAP(a,b) do { int _swap_var_=(a); (a)=(b); (b)=_swap_var_; } while (0)

#define CHECK_FLAG(_var, _flag) ((_var) & (_flag))


#define makeword(_h,_l) (((_h)<<16) + ((_l)&0xffff))
#define hiword(_v) ((_v)>>16)
#define loword(_v) ((_v)& 0x0000ffff)
#define makeshort(_h, _l) (((_h)<<8) + ((_l)&0x00ff))
#define hibyte(_w) ((_w)>> 8)
#define lobyte(_w) ((_w)& 0x00ff)
#define kb_to_bytes(_kb) ((_kb) * 1024)
#define _min(a,b) (((a) < (b)) ? (a) : (b))
#define _max(a,b) (((a) > (b)) ? (a) : (b))
#define ABS(a) ((a<0)?(-a):(a))

#ifndef WIN32
#define __min(a,b) (((a) < (b)) ? (a) : (b))
#define __max(a,b) (((a) > (b)) ? (a) : (b))
#endif

#ifdef LINUX
#define stricmp(a,b) strcasecmp(a,b)
#define _fstat32 fstat
#define _stat stat
#endif

#endif
