
include_directories(${TEST_SOURCE_DIR}/include)

add_library (Base vector-base-basic.cxx vector-base.cxx vector-impl.cxx
                  vector-op.cxx chain-node.cxx chain.cxx
                  ref-vector.cxx var-vector.cxx fix-vector.cxx
                  matrix-base.cxx util.cxx matrix-rectangle-base.cxx
                  data-pack.cxx object-with-storage.cxx
                  ref-object.cxx var-matrix-rectangle.cxx
                  ref-matrix-rectangle.cxx fix-matrix-rectangle.cxx
                  btree-node.cxx btree.cxx)

