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

set(latex_example_files)

function(add_example)
  cmake_parse_arguments(
    example
    ""
    "ROOT;STANDARD"
    "FILES"
    ${ARGN}
    )

  foreach(file ${example_FILES})
    set(file_path "examples/${example_ROOT}/${file}")
    set(latex_example_files ${latex_example_files} ${file_path})
    set(files ${files} ${file_path})
  endforeach()

  set(target_name ${example_ROOT}-${example_STANDARD})
  add_executable(${target_name} ${files})
  set_property(TARGET ${target_name} PROPERTY CXX_STANDARD ${example_STANDARD})
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

add_latex_document(
  c++-book.tex

  CONFIGURE
  c++-book.tex

  INPUTS
  ${latex_example_files}

  parts/11.tex
  parts/cpp-general.tex
  parts/preface.tex

  parts/11/anonymous-namespace.tex
  parts/11/auto.tex
  parts/11/decltype.tex
  parts/11/defaulted-constructors.tex
  parts/11/delegated-constructors.tex
  parts/11/deleted-constructors.tex
  parts/11/free-begin.tex
  parts/11/lambdas.tex
  parts/11/move.tex
  parts/11/prev-next.tex
  parts/11/range-based-for-loops.tex
  parts/11/rvalue-reference.tex
  parts/11/template-aliases.tex
  parts/11/smart-pointers.tex

  style/code-listings.tex
  )
