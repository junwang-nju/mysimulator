
project (polymerONsphere)

include_directories (${TEST_SOURCE_DIR}/include)
link_directories (${TEST_SOURCE_DIR}/lib)
add_definitions (-Wall -O3 -DNDEBUG -fno-tree-vectorize)

add_executable (pOs-basic.run basic.cxx)
target_link_libraries (pOs-basic.run blas)

add_executable (pOs-constd.run const-d.cxx)
target_link_libraries (pOs-constd.run blas)

add_executable (pOs-nbasic.run nbasic.cxx)
target_link_libraries (pOs-nbasic.run blas)
set_source_files_properties (nbasic.cxx COMPILE_FLAGS "-msse2 -DHAVE_SSE2")

