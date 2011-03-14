
project (Binding-FreeEnergy)

include_directories (${TEST_SOURCE_DIR}/include)
add_definitions (-Wall -O3 -DNDEBUG -fno-tree-vectorize)

add_executable (binding-FE.run FE.cxx)
target_link_libraries (binding-FE.run blas)

