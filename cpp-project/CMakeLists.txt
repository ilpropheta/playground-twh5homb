cmake_minimum_required (VERSION 2.6)
SET(GCC_CPP17 "-std=c++17")
add_definitions(${GCC_CPP17})
project (MicroUrl)

FILE(GLOB FixedCpp microurl/fixed/*.cpp)
FILE(GLOB FixedH microurl/fixed/*.h)
FILE(GLOB MicroUrlCpp microurl/*.cpp)
FILE(GLOB MicroUrlH microurl/*.h)

include_directories(microurl/fixed)
include_directories(microurl)

add_executable(microurl_1 microurl/tests/MakeUrlTest.cpp ${FixedH} ${FixedCpp} ${MicroUrlH} ${MicroUrlCpp})
