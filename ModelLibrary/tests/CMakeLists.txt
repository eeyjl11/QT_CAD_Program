cmake_minimum_required( VERSION 3.21 )
project(ModelLibraryTests VERSION 1.0.0)
add_executable(test_ourmodelib
	test.cpp test.h
	test_material.cpp test_material.h
    test_model.cpp test_model.h
	test_vector3D.cpp test_vector3D.h
	test_cell.cpp test_cell.h)
target_link_libraries(test_ourmodelib ${CMAKE_SOURCE_DIR}/../../build/ModelLibrary/src/libourmodelib.a)
