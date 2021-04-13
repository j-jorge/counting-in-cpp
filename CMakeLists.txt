cmake_minimum_required(VERSION 3.16)

project(
  counting-in-c++
  LANGUAGES NONE
  VERSION 1
  )

set(
  CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake/modules/"
  )

include(UseLATEX)

add_latex_document(
  c++-book.tex

  CONFIGURE
  c++-book.tex

  INPUTS
  parts/11.tex
  parts/cpp-general.tex
  parts/preface.tex

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
