cmake_minimum_required (VERSION 2.6)

project (MicroUrl)

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
	SET(GCC_CPP17 "-std=c++17")
	add_definitions(${GCC_CPP17})
endif()

if (MSVC_VERSION GREATER_EQUAL "1900")
    include(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG("/std:c++17" _cpp_latest_flag_supported)
    if (_cpp_latest_flag_supported)
        add_compile_options("/std:c++17")
    endif()
endif()

include_directories(microurl/)
include_directories(microurl/src/)

FILE(GLOB ThirdPartySources microurl/3rdparty/*.cpp)
FILE(GLOB ThirdPartyHeaders microurl/3rdparty/*.h)

FILE(GLOB Ver1Sources microurl/src/ver1/*.cpp)
FILE(GLOB Ver1Headers microurl/src/ver1/*.h)

add_executable(microurl_1 microurl/src/ver1/tests/MakeUrlTest.cpp ${ThirdPartyHeaders} ${ThirdPartySources} ${Ver1Headers} ${Ver1Sources})
