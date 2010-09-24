
project (coarse-grain)

include_directories (${TEST_SOURCE_DIR}/include)
link_directories (${TEST_SOURCE_DIR}/lib)
add_definitions (-Wall -O3 -DNDEBUG -fno-tree-vectorize)

add_executable (dw.run dual-well-traj.cxx)
target_link_libraries (dw.run blas)

add_executable (cg-dw.run cg-dual-well.cxx)
target_link_libraries (cg-dw.run blas)

add_executable (bd-dw.run bd-dual-wall.cxx)
target_link_libraries (bd-dw.run blas)

add_executable (fp-dw.run fp-dual-well.cxx)
target_link_libraries (fp-dw.run blas)

add_executable (fpd-dw.run fpd-dual-well.cxx)
target_link_libraries (fpd-dw.run blas)

add_executable (fpdist.run fpdist-dual-well.cxx)
target_link_libraries (fpdist.run blas)

add_executable (fp-2d.run fp-2d-funnel.cxx)
target_link_libraries (fp-2d.run blas)

add_executable (bd-2d.run bd-2d-funnel.cxx)
target_link_libraries (bd-2d.run blas)

add_executable (l2denum.run 2d-conf-enum.cxx)
target_link_libraries (l2denum.run blas)

add_executable (l2dneib.run 2d-conf-neighbor.cxx)
target_link_libraries (l2dneib.run blas Base)

add_executable (l2ddifu.run 2d-conf-diffuse.cxx)
target_link_libraries (l2ddifu.run blas)

add_executable (fk.run fk.cxx)
target_link_libraries (fk.run blas)

add_executable (l2dana.run 2d-conf-analysis.cxx)
target_link_libraries (l2dana.run blas)

add_executable (clus.run cluster.cxx)
target_link_libraries (clus.run blas)

add_executable (l3denum.run 3d-conf-enum.cxx)
target_link_libraries (l3denum.run blas)

add_executable (l3dneib.run 3d-conf-neighbor.cxx)
target_link_libraries (l3dneib.run blas Base)

add_executable (l3ddifu.run 3d-conf-diffuse.cxx)
target_link_libraries (l3ddifu.run blas)

