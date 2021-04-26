#pragma once

#include "dispatcher_impl.hpp"

#include <vector>

template<typename Arg>
struct dispatcher_impl<Arg, void>
{
  typedef void (*function_type)(Arg);

  void queue(function_type f)
  {
    m_scheduled.push_back(f);
  }

  template<typename A>
  void dispatch(A a)
  {
    const std::size_t count = m_scheduled.size();

    for (std::size_t i(0); i != count; ++i)
      m_scheduled[i](a);
  }

private:
  // The functions that will be called on the next dispatch.
  std::vector<function_type> m_scheduled;
};
