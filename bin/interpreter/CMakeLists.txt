find_package (BISON REQUIRED)
find_package (FLEX REQUIRED)


flex_target(flexer lexer.l "${CMAKE_CURRENT_BINARY_DIR}/lexer.cc")
bison_target(bparser parser.y "${CMAKE_CURRENT_BINARY_DIR}/parser.cc")


add_library (simulator STATIC simulator.cpp "${CMAKE_CURRENT_BINARY_DIR}/lexer.cc" "${CMAKE_CURRENT_BINARY_DIR}/parser.cc")
target_link_libraries(simulator PUBLIC stdcomponents ir readline)
target_include_directories (simulator PUBLIC  "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_BINARY_DIR}")


