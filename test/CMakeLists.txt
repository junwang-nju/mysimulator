
include_directories (${TEST_SOURCE_DIR}/include)
link_directories (${TEST_SOURCE_DIR}/lib)

add_executable (test-vector-impl.run test-vector-impl.cxx)
target_link_libraries (test-vector-impl.run blas Base)

add_executable (test-util.run test-util.cxx)
target_link_libraries (test-util.run Base)

add_executable (test-chain-node.run test-chain-node.cxx)

add_executable (test-chain.run test-chain.cxx)

add_executable (test-btree-node.run test-btree-node.cxx)

