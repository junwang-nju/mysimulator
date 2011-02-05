
project (polymerONsphere)

include_directories (${TEST_SOURCE_DIR}/include)
add_definitions (-Wall -O3 -DNDEBUG -fno-tree-vectorize)

add_executable (pOs-basic.run basic.cxx)
target_link_libraries (pOs-basic.run blas)

add_executable (pOs-basic-lg.run basic-lg.cxx)
target_link_libraries (pOs-basic-lg.run blas)

add_executable (pOs-basic-gao.run basic-gao.cxx)
target_link_libraries (pOs-basic-gao.run blas)

add_executable (pOs-constd.run const-d.cxx)
target_link_libraries (pOs-constd.run blas)

add_executable (pOs-nbasic.run nbasic.cxx)
target_link_libraries (pOs-nbasic.run blas)
set_source_files_properties (nbasic.cxx COMPILE_FLAGS "-msse2 -DHAVE_SSE2")

