
include_directories (${TEST_SOURCE_DIR}/include)
link_directories (${TEST_SOURCE_DIR}/lib)

add_executable (test-vector-impl.run test-vector-impl.cxx)
target_link_libraries (test-vector-impl.run blas Base)

