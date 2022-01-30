cmake_minimum_required(VERSION 3.16)

project(
  counting-in-c++
  LANGUAGES CXX
  VERSION 1
  )

set(
  CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake/modules/"
  )

include(UseLATEX)
find_package(Threads)

set(latex_example_files)

function(add_example)
  cmake_parse_arguments(
    example
    ""
    "ROOT;STANDARD;TARGET"
    "FILES;LINKS"
    ${ARGN}
    )

  set(source_root "examples/${example_ROOT}")
  set(examples)

  foreach(file ${example_FILES})
    set(file_path "${source_root}/${file}")
    set(examples ${examples} "${file_path}")
    set(files ${files} ${file_path})
  endforeach()

  set(latex_example_files ${latex_example_files} ${examples} PARENT_SCOPE)

  if(example_TARGET)
    set(target_name "${example_TARGET}")
  else()
    set(target_name ${example_ROOT}-${example_STANDARD})
  endif()

  add_executable(${target_name} ${files})
  set_property(TARGET ${target_name} PROPERTY CXX_STANDARD ${example_STANDARD})
  target_include_directories(${target_name} PRIVATE ${source_root})

  if(example_LINKS)
    target_link_libraries(${target_name} PRIVATE ${example_LINKS})
  endif()
endfunction()

add_example(
  ROOT constexpr
  FILES constexpr-98.cpp
  STANDARD 98
  )
add_example(
  ROOT constexpr
  FILES constexpr-11.cpp
  STANDARD 11
  )
add_example(
  ROOT constexpr
  FILES constexpr-14.cpp
  STANDARD 14
  )
add_example(
  ROOT extern-template
  FILES main.cpp bar-98.cpp foo-98.cpp
  STANDARD 98
  )
add_example(
  ROOT extern-template
  FILES main.cpp  bar-11.cpp foo-11.cpp factorial-11.cpp
  STANDARD 11
  )
add_example(
  ROOT nullptr
  FILES nullptr-11.cpp
  STANDARD 11
  )
add_example(
  ROOT reference-wrapper
  FILES capacity_tracker.cpp
  STANDARD 11
  )
add_example(
  ROOT thread
  FILES flood.cpp
  STANDARD 11
  LINKS Threads::Threads
  )
add_example(
  ROOT tuple
  FILES binding.cpp
  STANDARD 11
  )
add_example(
  ROOT type-traits
  FILES main-11.cpp
  STANDARD 11
  )
add_example(
  ROOT type-traits
  FILES main-98.cpp
  STANDARD 98
  )
add_example(
  ROOT uniform-initialization
  FILES struct.cpp
  STANDARD 11
  )
add_example(
  ROOT variadic-template
  FILES main-11.cpp callbacks.cpp
  STANDARD 11
  )
add_example(
  ROOT variadic-template
  FILES main-98.cpp callbacks.cpp
  STANDARD 98
  )
add_example(
  TARGET variadic-template-array
  ROOT variadic-template
  FILES collect_type_names.cpp
  STANDARD 11
  )
add_example(
  TARGET variable-template-11
  ROOT variable-template
  FILES main-11.cpp
  STANDARD 11
  )
add_example(
  TARGET variable-template-14
  ROOT variable-template
  FILES main-14.cpp
  STANDARD 14
  )

add_latex_document(
  counting-in-c++.tex

  BIBFILES
  bibliography.bib

  CONFIGURE
  counting-in-c++.tex

  IMAGE_DIRS
  assets

  INPUTS
  ${latex_example_files}

  examples/extern-template/factorial-11.hpp
  examples/extern-template/factorial-98.hpp
  examples/nullptr/nullptr-98.cpp
  examples/static-assert/even_sized_array-11.cpp
  examples/static-assert/even_sized_array-98.cpp
  examples/type-traits/mix-11.hpp
  examples/type-traits/mix-98.hpp
  examples/variadic-template/dispatcher-11.hpp
  examples/variadic-template/dispatcher-98.hpp
  examples/variadic-template/dispatcher_impl_1.hpp
  examples/variadic-template/dispatcher_impl_2.hpp

  parts/11.tex
  parts/14.tex
  parts/cpp-general.tex
  parts/license.tex
  parts/preface.tex
  parts/title-page.tex

  parts/11/array.tex
  parts/11/auto.tex
  parts/11/bind.tex
  parts/11/constexpr.tex
  parts/11/decltype.tex
  parts/11/defaulted-constructors.tex
  parts/11/delegated-constructors.tex
  parts/11/deleted-constructors.tex
  parts/11/extern-template.tex
  parts/11/free-begin.tex
  parts/11/function.tex
  parts/11/hash-table.tex
  parts/11/initializer-list.tex
  parts/11/lambdas.tex
  parts/11/miscellaneous.tex
  parts/11/move.tex
  parts/11/nullptr.tex
  parts/11/override-and-final.tex
  parts/11/prev-next.tex
  parts/11/random.tex
  parts/11/range-based-for-loops.tex
  parts/11/reference-wrapper.tex
  parts/11/rvalue-reference.tex
  parts/11/template-aliases.tex
  parts/11/scoped-enumerations.tex
  parts/11/smart-pointers.tex
  parts/11/static-assert.tex
  parts/11/thread.tex
  parts/11/tuple.tex
  parts/11/type-traits.tex
  parts/11/uniform-initialization.tex
  parts/11/using-parent-function.tex
  parts/11/variadic-template.tex

  parts/14/binary-literals.tex
  parts/14/decltype-auto.tex
  parts/14/deprecated.tex
  parts/14/generic-lambdas.tex
  parts/14/integer-sequence.tex
  parts/14/lambda-capture.tex
  parts/14/make-unique.tex
  parts/14/number-separator.tex
  parts/14/relaxed-constexpr.tex
  parts/14/return-type-deduction.tex
  parts/14/variable-templates.tex

  style/code-listings.tex
  )
