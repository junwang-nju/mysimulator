
project (Binding-FreeEnergy)

include_directories (${TEST_SOURCE_DIR}/include)
add_definitions (-Wall -O3 -DNDEBUG -fno-tree-vectorize)

add_executable (binding-FE.run FE-Coulomb.cxx)
target_link_libraries (binding-FE.run blas)

add_executable (binding-FE-exp.run FE-Exponential.cxx)
target_link_libraries (binding-FE-exp.run blas)

add_executable (binding-intg.run Integral.cxx)
target_link_libraries (binding-intg.run blas)

add_executable (binding-line.run Line-FE.cxx)
target_link_libraries (binding-line.run blas)

add_executable (binding-sphere.run Sphere-FE.cxx)
target_link_libraries (binding-sphere.run blas)

add_executable (binding-psphere.run PlaneSphere-FE.cxx)
target_link_libraries (binding-psphere.run blas)

add_executable (binding-dimer.run Dimer.cxx)
target_link_libraries (binding-dimer.run blas)

add_executable (binding-plane.run Plane-FE.cxx)
target_link_libraries (binding-plane.run blas)


