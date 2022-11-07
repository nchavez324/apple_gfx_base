cmake_minimum_required(VERSION 3.21.0)

project(
  AppleGfxBase
  VERSION 0.0.1
  LANGUAGES C
            CXX
            OBJC
            OBJCXX
)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}"
                      "${PROJECT_SOURCE_DIR}/tools/cmake"
)

set(CMAKE_C_EXTENSIONS NO)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

set(CMAKE_CXX_EXTENSIONS NO)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_OBJCXX_STANDARD 17)
set(CMAKE_OBJCXX_STANDARD_REQUIRED True)
set(CMAKE_OBJCXX_EXTENSIONS NO)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_XCODE_ATTRIBUTE_CODE_SIGNING_REQUIRED NO)
set(CMAKE_XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "")
set(CMAKE_XCODE_GENERATE_TOP_LEVEL_PROJECT_ONLY True)

if("${CMAKE_BUILD_TYPE}"
   STREQUAL
   ""
)
  message(STATUS "No build type selected, default to Debug")
  set(CMAKE_BUILD_TYPE "Debug")
endif()

add_subdirectory("external/glm")
add_subdirectory("examples")
