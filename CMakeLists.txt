cmake_minimum_required( VERSION 3.21 )
project( MainProject VERSION 1.0.0)

add_subdirectory( ModelLibrary/src)
add_subdirectory( qtvtk )

set(PROJECT_NAME "qtvtkviewer-git")
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/package_conf")

set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})

install(TARGETS qtvtk-viewer RUNTIME DESTINATION bin)
install(TARGETS ourmodelib ARCHIVE DESTINATION lib)
install(FILES ModelLibrary/src/modelib.h DESTINATION include)
install(FILES QTViewer.desktop DESTINATION /usr/share/applications)
install(FILES QTViewer.svg DESTINATION /usr/share/icons)

include(ubuntu-impish)



