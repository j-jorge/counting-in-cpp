template<typename T, unsigned N>
struct even_sized_array
{
  // We can also put a message to repeat the condition, like
  // professionals. Don't forget the exclamation mark to
  // show it is serious.
  static_assert(N % 2 == 0, "The size must be even!");
  typedef T type[N];
};

// So much less code <3
void test()
{
  even_sized_array<int, 8>::type ok;
  even_sized_array<int, 9>::type nok;
}
