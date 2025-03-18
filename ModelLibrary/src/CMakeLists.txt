cmake_minimum_required( VERSION 3.21 )
project(ModelLibrary VERSION 1.0.0)
add_library(ourmodelib STATIC
	modelib.cpp modelib.h
	cell.cpp  cell.h
	material.cpp material.h  
	matrix.cpp  matrix.h 
	model.cpp  model.h
	vector3D.cpp vector3D.h
)
set_target_properties(ourmodelib PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(ourmodelib PROPERTIES PUBLIC_HEADER modelib.h)
