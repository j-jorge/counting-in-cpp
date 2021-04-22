template<unsigned N>
struct count_t;

template<>
struct count_t<0>
{
  enum { value = 0 };
};

template<unsigned N>
struct count_t
{
  enum
    {
      value = 1 + count_t<N - 1>::value
    };
};

void foo()
{
  int array[count_t<900>::value];
  (void)array;
}
