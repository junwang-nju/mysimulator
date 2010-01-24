
include_directories (${TEST_SOURCE_DIR}/include)
link_directories (${TEST_SOURCE_DIR}/lib)

add_executable (test-vector.run test-vector.cxx)
target_link_libraries (test-vector.run blas vector)

