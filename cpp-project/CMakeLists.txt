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
FILE(GLOB Ver3Sources microurl/src/ver3/*.cpp)
FILE(GLOB Ver3Headers microurl/src/ver3/*.h)
FILE(GLOB Ver4Sources microurl/src/ver4/*.cpp)
FILE(GLOB Ver4Headers microurl/src/ver4/*.h)
FILE(GLOB Ver5Sources microurl/src/ver5/*.cpp)
FILE(GLOB Ver5Headers microurl/src/ver5/*.h)
FILE(GLOB Ver6Sources microurl/src/ver6/*.cpp)
FILE(GLOB Ver6Headers microurl/src/ver6/*.h)

add_executable(ver1 
	microurl/src/ver1/tests/NiceToMeetYou.cpp 
	${ThirdPartyHeaders} ${ThirdPartySources} 
	${Ver1Headers} ${Ver1Sources})

add_executable(ver2 
	microurl/src/ver2/tests/MicroUrlInitializationTest.cpp 
	${ThirdPartyHeaders} ${ThirdPartySources} 
	${Ver2Headers} ${Ver2Sources})

add_executable(ver3
	microurl/src/ver3/tests/MicroUrlInitializationTest.cpp 
	microurl/src/ver3/tests/MicroUrlCustomIdGeneratorTest.cpp
	${ThirdPartyHeaders} ${ThirdPartySources} 
	${Ver3Headers} ${Ver3Sources})	
	
add_executable(ver4	
	microurl/src/ver4/tests/UrlInfoTest.cpp
	microurl/src/ver4/tests/UrlInfoCompareTest.cpp
	${ThirdPartyHeaders} ${ThirdPartySources} 
	${Ver4Headers} ${Ver4Sources})	
	
add_executable(ver5	
	microurl/src/ver5/tests/StringViewTest.cpp
	microurl/src/ver5/tests/LoadBalancerTest.cpp
	${ThirdPartyHeaders} ${ThirdPartySources} 
	${Ver5Headers} ${Ver5Sources})	
	
add_executable(ver6	
	microurl/src/ver6/tests/VisitTest.cpp
	${ThirdPartyHeaders} ${ThirdPartySources} 
	${Ver6Headers} ${Ver6Sources})		