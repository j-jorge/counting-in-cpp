find_package(LibXml2 REQUIRED)

add_executable(html-cleanup
  main.cpp
)

set_property(TARGET html-cleanup PROPERTY CXX_STANDARD 17)

target_link_libraries(html-cleanup LibXml2::LibXml2)

set(html_cleanup "${CMAKE_CURRENT_BINARY_DIR}/html-cleanup" PARENT_SCOPE)
