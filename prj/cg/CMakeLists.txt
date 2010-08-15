
project (coarse-grain)

include_directories (${TEST_SOURCE_DIR}/include)
link_directories (${TEST_SOURCE_DIR}/lib)
add_definitions (-Wall -O3 -DNDEBUG -fno-tree-vectorize)

add_executable (dw.run dual-well-traj.cxx)
target_link_libraries (dw.run blas)

add_executable (cg-dw.run cg-dual-well.cxx)
target_link_libraries (cg-dw.run blas)

add_executable (bd-dw.run bd-dual-wall.cxx)
target_link_libraries (bd-dw.run blas)

add_executable (fp-dw.run fp-dual-well.cxx)
target_link_libraries (fp-dw.run blas)

add_executable (fpd-dw.run fpd-dual-well.cxx)
target_link_libraries (fpd-dw.run blas)

add_executable (fpdist.run fpdist-dual-well.cxx)
target_link_libraries (fpdist.run blas)

