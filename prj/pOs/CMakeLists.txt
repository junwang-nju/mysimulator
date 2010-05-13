
project (polymerONsphere)

include_directories (${TEST_SOURCE_DIR}/include)
link_directories (${TEST_SOURCE_DIR}/lib)
add_definitions (-Wall -O3 -DNDEBUG)

add_executable (pOs-basic.run basic.cxx)
target_link_libraries (pOs-basic.run blas)

