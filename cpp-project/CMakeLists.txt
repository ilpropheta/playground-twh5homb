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

FILE(GLOB Ver2Sources microurl/src/ver2/*.cpp)
FILE(GLOB Ver2Headers microurl/src/ver2/*.h)

add_executable(ver1 
	microurl/src/ver1/tests/NiceToMeetYou.cpp 
	${ThirdPartyHeaders} ${ThirdPartySources} 
	${Ver1Headers} ${Ver1Sources})

add_executable(ver2 
	microurl/src/ver2/tests/MicroUrlInitializationTest.cpp 
	${ThirdPartyHeaders} ${ThirdPartySources} 
	${Ver2Headers} ${Ver2Sources})

add_executable(ver2_2 
	microurl/src/ver2/tests/MicroUrlInitializationTest.cpp 
	microurl/src/ver2/tests/MicroUrlCustomIdGeneratorTest.cpp
	${ThirdPartyHeaders} ${ThirdPartySources} 
	${Ver2Headers} ${Ver2Sources})	
	