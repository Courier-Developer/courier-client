

# Use the package PkgConfig to detect GTK+ headers/library files
FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTKmm REQUIRED gtkmm-3.0)

INCLUDE_DIRECTORIES(${GTKmm_INCLUDE_DIRS})
LINK_DIRECTORIES(${GTKmm_LIBRARY_DIRS})

AUX_SOURCE_DIRECTORY(../Logic_Part/class CLASS_DIR)
AUX_SOURCE_DIRECTORY(View VIEW_DIR)

add_executable(main main.cpp

        ${CLASS_DIR}
        ${VIEW_DIR}
        )
add_executable(test test.cpp)
TARGET_LINK_LIBRARIES(main ${GTKmm_LIBRARIES})

