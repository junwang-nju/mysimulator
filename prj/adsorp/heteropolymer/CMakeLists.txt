
project (adsorp-heteropolymer)

include_directories (${TEST_SOURCE_DIR}/include)
add_definitions (-Wall -O3 -DNDEBUG -fno-tree-vectorize)

add_executable (ht-plane.run plane.cxx)
target_link_libraries (ht-plane.run blas)

