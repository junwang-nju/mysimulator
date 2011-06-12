
project (adsorp-homopolymer)

include_directories (${TEST_SOURCE_DIR}/include)
add_definitions (-Wall -O3 -DNDEBUG -fno-tree-vectorize)

add_executable (hm-plane.run plane.cxx)
target_link_libraries (hm-plane.run blas)

