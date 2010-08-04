
project (coarse-grain)

include_directories (${TEST_SOURCE_DIR}/include)
link_directories (${TEST_SOURCE_DIR}/lib)
add_definitions (-Wall -O3 -DNDEBUG -fno-tree-vectorize)

add_executable (dw.run dual-well-traj.cxx)
target_link_libraries (dw.run blas)

add_executable (cg-dw.run cg-dual-well.cxx)
target_link_libraries (cg-dw.run blas)

