#pragma once

#include "dispatcher_impl.hpp"

#include <vector>

template<>
struct dispatcher_impl<void, void>
{
  typedef void (*function_type)();

  void queue(function_type f)
  {
    m_scheduled.push_back(f);
  }

  void dispatch()
  {
    const std::size_t count = m_scheduled.size();

    for (std::size_t i(0); i != count; ++i)
      m_scheduled[i]();
  }

private:
  // The functions that will be called on the next dispatch.
  std::vector<function_type> m_scheduled;
};
