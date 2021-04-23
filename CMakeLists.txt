cmake_minimum_required(VERSION 3.16)

project(
  counting-in-c++
  LANGUAGES CXX
  VERSION 0
  )

set(
  CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake/modules/"
  )

include(UseLATEX)

set(latex_example_files)

function(add_example)
  cmake_parse_arguments(
    example
    ""
    "ROOT;STANDARD"
    "FILES"
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

  set(target_name ${example_ROOT}-${example_STANDARD})
  add_executable(${target_name} ${files})
  set_property(TARGET ${target_name} PROPERTY CXX_STANDARD ${example_STANDARD})
  target_include_directories(${target_name} PRIVATE ${source_root})
endfunction()

add_example(
  ROOT anonymous-namespace
  FILES foo.cpp main.cpp
  STANDARD 98
  )
add_example(
  ROOT anonymous-namespace
  FILES foo-anonymous.cpp main-anonymous.cpp
  STANDARD 11
  )
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
  ROOT extern-template
  FILES main.cpp bar-98.cpp foo-98.cpp
  STANDARD 98
  )
add_example(
  ROOT extern-template
  FILES main.cpp  bar-11.cpp foo-11.cpp some_template-11.cpp
  STANDARD 11
  )
add_example(
  ROOT nullptr
  FILES nullptr-11.cpp
  STANDARD 11
  )

add_latex_document(
  c++-book.tex

  BIBFILES
  bibliography.bib

  CONFIGURE
  c++-book.tex

  INPUTS
  ${latex_example_files}

  examples/extern-template/some_template-11.hpp
  examples/extern-template/some_template-98.hpp
  examples/nullptr/nullptr-98.cpp
  examples/static-assert/even_sized_array-11.cpp
  examples/static-assert/even_sized_array-98.cpp

  parts/11.tex
  parts/cpp-general.tex
  parts/preface.tex

  parts/11/anonymous-namespace.tex
  parts/11/auto.tex
  parts/11/constexpr.tex
  parts/11/decltype.tex
  parts/11/defaulted-constructors.tex
  parts/11/delegated-constructors.tex
  parts/11/deleted-constructors.tex
  parts/11/extern-template.tex
  parts/11/free-begin.tex
  parts/11/lambdas.tex
  parts/11/move.tex
  parts/11/nullptr.tex
  parts/11/override-and-final.tex
  parts/11/prev-next.tex
  parts/11/range-based-for-loops.tex
  parts/11/rvalue-reference.tex
  parts/11/template-aliases.tex
  parts/11/scoped-enumerations.tex
  parts/11/smart-pointers.tex
  parts/11/static-assert.tex

  style/code-listings.tex
  )
