#pragma once

#include "dispatcher_impl_0.hpp"
#include "dispatcher_impl_1.hpp"
#include "dispatcher_impl_2.hpp"

template<typename Arg1 = void, typename Arg2 = void>
struct dispatcher: dispatcher_impl<Arg1, Arg2>
{};
