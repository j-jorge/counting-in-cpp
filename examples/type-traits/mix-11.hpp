#include <type_traits>

template<typename T>
typename std::enable_if<std::is_floating_point<T>::value, T>::type
mix(T a, T b, T r)
{
  return r * a + (1 - r) * b;
}

