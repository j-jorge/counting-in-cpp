#pragma once

template<typename T>
T some_template(T n)
{
  T r = 1;

  for (T i = 1; i <= n; ++i)
    r += r * i;

  return r;
}

extern template int some_template<int>(int);
