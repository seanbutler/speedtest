cmake_minimum_required(VERSION 3.5.0)
project(speed_test VERSION 0.1.0 LANGUAGES C CXX)

include(FetchContent)

FetchContent_Declare(
    matplotplusplus
    GIT_REPOSITORY https://github.com/alandefreitas/matplotplusplus
    GIT_TAG origin/master) # or whatever tag you want   


FetchContent_GetProperties(matplotplusplus)
if(NOT matplotplusplus_POPULATED)
    FetchContent_Populate(matplotplusplus)
    add_subdirectory(${matplotplusplus_SOURCE_DIR} ${matplotplusplus_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()
        

add_executable(row_col_exp row_col_exp.cpp)
target_link_libraries(row_col_exp PUBLIC matplot)

add_executable(size_skip_exp size_skip_exp.cpp)
target_link_libraries(size_skip_exp PUBLIC matplot)
