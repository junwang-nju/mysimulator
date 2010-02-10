
include_directories(${TEST_SOURCE_DIR}/include)

add_library (Base vector-base.cxx vector-impl.cxx
                  vector-op.cxx 
                  util.cxx
                  hash-func.cxx)

