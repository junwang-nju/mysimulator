
project (Rumor-Propagation)

include_directories (${TEST_SOURCE_DIR}/include/new)
add_definitions (-Wall -O3 -DNDEBUG -fno-tree-vectorize -std=c++0x)

add_executable (rumor-percolation.run percolation.cxx)
target_link_libraries (rumor-percolation.run blas)

