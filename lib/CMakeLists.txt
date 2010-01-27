
include_directories(${TEST_SOURCE_DIR}/include)

add_library (Base vector-base-basic.cxx vector-base.cxx vector-impl.cxx
                  vector-op.cxx pool.cxx 
                  ref-vector.cxx var-vector.cxx fix-vector.cxx
                  matrix-base.cxx matrix-rectangle.cxx util.cxx
                  matrix-triangle.cxx data-pack.cxx object-with-storage.cxx
                  ref-object.cxx)

