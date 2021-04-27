#pragma once

#include <vector>

// The template accepts any number of arguments.
template<typename... Args>
struct dispatcher
{
  // We can list the template parameters by appending '...'.
  typedef void (*function_type)(Args...);

  void queue(function_type f)
  {
    m_scheduled.push_back(f);
  }

  // args represent any sequence of arguments here.
  template<typename... A>
  void dispatch(A&&... args)
  {
    const std::size_t count = m_scheduled.size();

    // Then we can list the arguments by appending '...'
    // to the function argument.
    for (std::size_t i(0); i != count; ++i)
      m_scheduled[i](args...);
  }

private:
  std::vector<function_type> m_scheduled;
};
