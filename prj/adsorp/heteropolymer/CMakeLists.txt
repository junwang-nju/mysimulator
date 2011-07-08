
project (adsorp-heteropolymer)

include_directories (${TEST_SOURCE_DIR}/include)
add_definitions (-Wall -O3 -DNDEBUG -fno-tree-vectorize)

add_executable (ht-plane.run plane.cxx)
target_link_libraries (ht-plane.run blas)

add_executable (hd-plane.run d-plane.cxx)
target_link_libraries (hd-plane.run blas)

add_executable (hd2-plane.run d-plane-2.cxx)
target_link_libraries (hd2-plane.run blas)

add_executable (proc2.run proc2.cxx)
target_link_libraries (proc2.run blas)

