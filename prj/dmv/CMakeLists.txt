
project (directMove)

include_directories (${TEST_SOURCE_DIR}/include)
link_directories (${TEST_SOURCE_DIR}/lib)
add_definitions (-Wall -O3 -DNDEBUG -fno-tree-vectorize)

add_executable (dmove-1.run dmv1.cxx)
target_link_libraries (dmove-1.run blas)
set_source_files_properties (dmv1.cxx COMPILE_FLAGS "-msse2 -DHAVE_SSE2")

add_executable (dmove-2.run dmv2.cxx)
target_link_libraries (dmove-2.run blas)
set_source_files_properties (dmv2.cxx COMPILE_FLAGS "-msse2 -DHAVE_SSE2")

