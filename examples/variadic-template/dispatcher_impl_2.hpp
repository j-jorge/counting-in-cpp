#pragma once

#include "dispatcher_impl.hpp"

#include <vector>

template<typename Arg1, typename Arg2>
struct dispatcher_impl
{
  typedef void (*function_type)(Arg1, Arg2);

  void queue(function_type f)
  {
    m_scheduled.push_back(f);
  }

  template<typename A1, typename A2>
  void dispatch(A1 a1, A2 a2)
  {
    const std::size_t count = m_scheduled.size();

    for (std::size_t i(0); i != count; ++i)
      m_scheduled[i](a1, a2);
  }

private:
  // The functions that will be called on the next dispatch.
  std::vector<function_type> m_scheduled;
};
