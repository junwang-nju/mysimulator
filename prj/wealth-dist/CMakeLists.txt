
project (WealthDistribution)

include_directories (${TEST_SOURCE_DIR}/include)
link_directories (${TEST_SOURCE_DIR}/lib)
add_definitions (-Wall -O3 -DNDEBUG)

add_executable (basic.run basic.cxx)
target_link_libraries (basic.run blas Base)

add_executable (poor.run poor.cxx)
target_link_libraries (poor.run blas Base)

add_executable (diff-usage.run diff-usage.cxx)
target_link_libraries (diff-usage.run blas Base)

