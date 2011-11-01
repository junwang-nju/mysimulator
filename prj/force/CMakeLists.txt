
project (Forced)

include_directories (${TEST_SOURCE_DIR}/include/new)
#add_definitions (-Wall -O3 -DNDEBUG -fno-tree-vectorize)
add_definitions (-Wall -O3 -fno-tree-vectorize)

add_executable (cma-2-cnt.run cma-2-cnt.cxx)
target_link_libraries (cma-2-cnt.run blas)

add_executable (force-min.run force-min.cxx)
target_link_libraries (force-min.run blas)

