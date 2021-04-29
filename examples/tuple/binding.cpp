#include <tuple>
#include <cstdio>

// This structure is here to "store" a sequence of integers in its template
// parameters. There is nothing like that in C++11 but it is already available
// in C++14 @\ref{integer-sequence}@.
template<unsigned... I>
struct integer_sequence {};

// This one is used to create a sequence of N consecutive integers, from 0 to
// N-1, given N.
//
// Remaining is the number of integers that still have to be generated.
// Computed is the sequence we have computed so far.
template<unsigned Remaining, unsigned... Computed>
struct make_integer_sequence;

template<unsigned... Computed>
struct make_integer_sequence<0, Computed...>
{
  using type = integer_sequence<Computed...>;
};

template<unsigned Remaining, unsigned... Computed>
struct make_integer_sequence
{
  using type =
    typename make_integer_sequence
    <
      Remaining - 1,
      Remaining - 1,
      Computed...
    >::type;
};

// The call_helper will help us to get the elements of a tuple, because we
// cannot get them by type.
template<typename IntegerSequence>
struct call_helper;

template<unsigned... I>
struct call_helper<integer_sequence<I...>>
{
  template<typename F, typename... Args>
  static void call(F&& function, std::tuple<Args...>& arguments)
  {
    // Here we unpack I... to get the arguments from the tuple.
    // See @\aref{variadic-template}@.
    function(std::get<I>(arguments)...);
  }
};

// A binding is a function object that can be called with no arguments and that,
// when called, will pass the arguments given to its constructor to the function
// given to its constructor.
template<typename F, typename... Args>
struct binding
{
  binding(F&& f, Args&&... arguments)
    : m_function(std::forward<F>(f)),
      m_arguments(std::forward<Args>(arguments)...)
  {}

  void operator()()
  {
    // Here there is no way to get the elements from the m_arguments tuple by
    // unpacking Args..., so we indirectly build an integer pack that will
    // ultimately be used to call std::get<I>(m_arguments) for each I.
    call_helper
      <
        typename make_integer_sequence<sizeof...(Args)>::type
      >::call
      (m_function, m_arguments);
  }

private:
  F m_function;
  std::tuple<Args...> m_arguments;
};

// This function is just here to build a binding without specifying all its
// template parameters.
template<typename F, typename... Args>
binding<F, Args...> bind(F&& f, Args&&... arguments)
{
  return
    binding<F, Args...>
    (std::forward<F>(f), std::forward<Args>(arguments)...);
}

// The function that will be bound.
void print(int a, int b)
{
  printf("%d, %d\n", a, b);
}

int main()
{
  // This creates the binding. Is it a valid use case of auto @\aref{auto}@?
  auto f(bind(&print, 24, 42));

  // And now we can call print with the provided arguments.
  f();
}
