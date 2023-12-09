cmake_minimum_required(VERSION 3.10)

project(HUJAM C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	set(CMAKE_BUILD_TYPE Release)

	set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}$<0:>)

	set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
	set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
	set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
	set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
	set(GLFW_VULKAN_STATIC OFF CACHE BOOL "" FORCE)

	set(CGLM_SHARED OFF CACHE BOOL "" FORCE)
	set(CGLM_STATIC ON CACHE BOOL "" FORCE)
	set(CGLM_USE_C99 ON CACHE BOOL "" FORCE)
	set(CGLM_USE_TEST OFF CACHE BOOL "" FORCE)

	set(BOX2D_BUILD_STATIC ON CACHE BOOL "" FORCE)
	set(BOX2D_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
	set(BOX2D_BUILD_UNITTESTS OFF CACHE BOOL "" FORCE)

	set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
	set(CMAKE_GENERATOR_PLATFORM x64)
    set(CMAKE_CXX_FLAGS_RELEASE "/O2 /Ob2 /Oi /Ot /Oy /GT /GL /MT /GS-")
	set(CMAKE_C_FLAGS_RELEASE "/O2 /Ob2 /Oi /Ot /Oy /GT /GL /MT /GS-")
    set(CMAKE_EXE_LINKER_FLAGS "/LTCG /machine:x64 /INCREMENTAL:NO /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup
	/NODEFAULTLIB:MSVCRT /NODEFAULTLIB:LIBCMT")
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)

	add_subdirectory(third_party/glfw)
	add_subdirectory(third_party/cglm)
	add_subdirectory(third_party/liquidfun/liquidfun/Box2D)

	include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
	include_directories(${CMAKE_CURRENT_SOURCE_DIR}/third_party/cglm/include)
	include_directories(${CMAKE_CURRENT_SOURCE_DIR}/third_party/glfw/include)
	include_directories(${CMAKE_CURRENT_SOURCE_DIR}/third_party/opengl/include)
	include_directories(${CMAKE_CURRENT_SOURCE_DIR}/third_party/stb)
	include_directories(${CMAKE_CURRENT_SOURCE_DIR}/third_party/liquidfun/liquidfun/Box2D/)

	FILE(GLOB_RECURSE MY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")
	FILE(GLOB_RECURSE MY_SOURCES2 "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
	add_executable(HUJAM ${MY_SOURCES} ${MY_SOURCES2} ${CMAKE_CURRENT_SOURCE_DIR}/third_party/opengl/src/glad.c)

	find_package(OpenGL REQUIRED)
	target_link_libraries(HUJAM cglm glfw Box2D msvcrt OpenGL::GL)
	target_compile_options(HUJAM PUBLIC /MT)

	set_target_properties(HUJAM PROPERTIES WIN32_EXECUTABLE TRUE)
else()
    message(FATAL_ERROR "Unsupported compiler")
endif()
