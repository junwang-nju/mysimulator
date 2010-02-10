
include_directories(${TEST_SOURCE_DIR}/include)

add_library (Base vector-base-basic.cxx vector-base.cxx vector-impl.cxx
                  vector-op.cxx 
                  matrix-base.cxx util.cxx matrix-rectangle-base.cxx
                  hash-func.cxx)

