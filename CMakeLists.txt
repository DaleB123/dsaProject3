cmake_minimum_required(VERSION 3.29)
project(Project_3)

set(CMAKE_CXX_STANDARD 14)

include_directories(libraries/bridges/include)
link_directories(libraries/bridges/lib)

include_directories(libraries/curl/include)
link_directories(libraries/curl/lib)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)



include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)



add_executable(Project_3 main.cpp
        SFMLhelper.h
        SFMLhelper.cpp
        mergeSort.cpp
        heapSort.h
        heapSort.cpp
        mergeSort.h
)

target_link_libraries(Project_3 sfml-graphics libcurl.lib)