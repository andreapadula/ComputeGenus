cmake_minimum_required(VERSION 2.4)

# name of the project (computeGenusGui)
project(computeGenusGui)

# GUI build-mode
set(TTK_BUILD_MODE "VTK-GUI")

# path to the common code base
find_path(TTK_DIR ttk.cmake
  PATHS
    ttk/
    ../ttk/
    ../../ttk/
    ../../../ttk/
)
include(${TTK_DIR}/ttk.cmake)

# include the different packages required for the application
ttk_add_vtkWrapper_package(ttkComputeGenus)

# add the local cpp files
ttk_add_source(main.cpp)

ttk_wrapup_binary(computeGenusGui)
