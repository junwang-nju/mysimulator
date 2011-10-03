
project (Binding-FreeEnergy-New)

include_directories (${TEST_SOURCE_DIR}/include/new)
add_definitions (-Wall -O3 -DNDEBUG -fno-tree-vectorize)

add_executable (binding-p.run plane.cxx)
target_link_libraries (binding-p.run blas)

