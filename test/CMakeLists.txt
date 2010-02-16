
include_directories (${TEST_SOURCE_DIR}/include)
link_directories (${TEST_SOURCE_DIR}/lib)
add_definitions (-Wall)

add_executable (test-vector-impl.run test-vector-impl.cxx)
target_link_libraries (test-vector-impl.run blas Base)

add_executable (test-util.run test-util.cxx)
target_link_libraries (test-util.run Base)

add_executable (test-chain-node.run test-chain-node.cxx)

add_executable (test-chain.run test-chain.cxx)

add_executable (test-btree-node.run test-btree-node.cxx)

add_executable (test-btree.run test-btree.cxx)
target_link_libraries (test-btree.run Base)

add_executable (test-var-vector.run test-var-vector.cxx)
target_link_libraries (test-var-vector.run blas Base)

add_executable (test-fix-vector.run test-fix-vector.cxx)
target_link_libraries (test-fix-vector.run blas Base)

add_executable (test-ref-vector.run test-ref-vector.cxx)
target_link_libraries (test-ref-vector.run blas Base)

add_executable (test-hash-func.run test-hash-func.cxx)
target_link_libraries (test-hash-func.run Base)

add_executable (test-var-matrix-rectangle.run test-var-matrix-rectangle.cxx)
target_link_libraries (test-var-matrix-rectangle.run blas Base)

