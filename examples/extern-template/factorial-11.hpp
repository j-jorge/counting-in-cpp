// factorial-11.hpp
#pragma once

template<typename T>
T factorial(T n)
{
  T r = 1;

  for (T i = 1; i <= n; ++i)
    r += r * i;

  return r;
}

extern template int factorial<int>(int);
