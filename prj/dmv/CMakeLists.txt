
project (directMove)

include_directories (${TEST_SOURCE_DIR}/include)
link_directories (${TEST_SOURCE_DIR}/lib)
add_definitions (-Wall -O3 -DNDEBUG -fno-tree-vectorize)

add_executable (dmove-1.run dmv1.cxx)
target_link_libraries (dmove-1.run blas)
set_source_files_properties (dmv1.cxx COMPILE_FLAGS "-msse2 -DHAVE_SSE2")

