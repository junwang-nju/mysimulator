
project (partition-zero)

include_directories (${TEST_SOURCE_DIR}/include)
link_directories (${TEST_SOURCE_DIR}/lib)
add_definitions (-Wall -O3 -DNDEBUG -fno-tree-vectorize)

add_executable (2dconf.run 2d-conf-enum.cxx)
target_link_libraries (2dconf.run blas)

add_executable (eqsolve.run eq-solve.cxx)
target_link_libraries (eqsolve.run blas)

add_executable (2dcase1.run 2d-conf-case1.cxx)
target_link_libraries (2dcase1.run blas)

