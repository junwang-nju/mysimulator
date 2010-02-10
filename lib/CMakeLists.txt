
include_directories(${TEST_SOURCE_DIR}/include)

add_library (Base vector-base-basic.cxx vector-base.cxx vector-impl.cxx
                  vector-op.cxx 
                  matrix-base.cxx util.cxx matrix-rectangle-base.cxx
                  object-with-storage.cxx
                  ref-object.cxx var-matrix-rectangle.cxx
                  ref-matrix-rectangle.cxx fix-matrix-rectangle.cxx
                  hash-func.cxx
                  parameter-key-base.cxx var-parameter-key.cxx
                  ref-parameter-key.cxx parameter-list-base.cxx)

