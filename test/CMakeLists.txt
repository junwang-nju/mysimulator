
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

add_executable (test-fix-matrix-rectangle.run test-fix-matrix-rectangle.cxx)
target_link_libraries (test-fix-matrix-rectangle.run blas Base)

add_executable (test-ref-matrix-rectangle.run test-ref-matrix-rectangle.cxx)
target_link_libraries (test-ref-matrix-rectangle.run blas Base)

add_executable (test-var-parameter-key.run test-var-parameter-key.cxx)
target_link_libraries (test-var-parameter-key.run blas Base)

add_executable (test-ref-parameter-key.run test-ref-parameter-key.cxx)
target_link_libraries (test-ref-parameter-key.run blas Base)

add_executable (test-var-parameter-list.run test-var-parameter-list.cxx)
target_link_libraries (test-var-parameter-list.run blas Base)

add_executable (test-ref-parameter-list.run test-ref-parameter-list.cxx)
target_link_libraries (test-ref-parameter-list.run blas Base)

add_executable (test-free-space.run test-free-space.cxx)
target_link_libraries (test-free-space.run blas Base)

add_executable (test-var-distance-square.run test-var-distance-square.cxx)
target_link_libraries (test-var-distance-square.run blas Base)

