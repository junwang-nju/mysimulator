
project (Binding-Integral)

include_directories (${TEST_SOURCE_DIR}/include/new)
add_definitions (-Wall -O3 -DNDEBUG -fno-tree-vectorize)

add_executable (bp.run plane.cxx)

