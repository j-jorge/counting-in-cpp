// The third template argument is expected to receive a flag
// telling if N is even (i.e. valid).
template<typename T, unsigned N, bool IsEven>
struct even_sized_array_impl;

// And we implement this type only if the flag is true.
template<typename T, unsigned N>
struct even_sized_array_impl<T, N, true>
{
  typedef T type[N];
};

template<typename T, unsigned N>
struct even_sized_array
{
  // Now we trigger the check by actually instantiating the
  // helper type, hoping that the flag will be true.
  typedef
  typename even_sized_array_impl<T, N, N % 2 == 0>::type
  type;
};

void test()
{
  even_sized_array<int, 8>::type ok;
  even_sized_array<int, 9>::type nok;
}
