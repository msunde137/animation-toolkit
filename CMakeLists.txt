project(atk)
cmake_minimum_required(VERSION 3.16.0)

if (WIN32) # NOTE: Needs testing for optional AntTweakBar

  find_library(GLEW NAMES glew32s PATHS external/lib/x64)
  find_library(GLFW NAMES glfw3 PATHS external/lib)
  #find_library(ODE NAMES ode_doubled PATHS 3rdparty/ode-0.13/lib/DebugDoubleDLL)

  set(INCLUDE_DIRS
     libsrc
     external/include)
     #3rdparty/ode-0.13/include
     #3rdparty/eigen-3.3.7)

  set(LIBRARY_DIRS libsrc)

  set(CMAKE_CXX_STANDARD 11) 
  set(CMAKE_CXX_FLAGS 
     "/wd4018 /wd4244 /wd4305 
     /D_CRT_SECURE_NO_WARNINGS 
     /D_CRT_NONSTDC_NO_DEPRECATE 
     /D NOMINMAX /DGLEW_STATIC
     /EHsc")

  #set(INSTALL_LIST
  #   3rdparty/glut/glutx86/glew32.dll 
  #   3rdparty/glut/glutx86/glut32.dll 
  #   3rdparty/ode-0.13/lib/DebugDoubleDLL/ode_doubled.dll)

  #set_target_properties(a0-sphere2d PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "PATH=%PATH%;${CMAKE_PREFIX_PATH}/bin")
  set(CMAKE_EXE_LINKER_FLAGS "/NODEFAULTLIB:\"MSVCRT\" /NODEFAULTLIB:\"LIBCMT\"")

  set(CORE agl ${GLEW} ${GLFW} opengl32.lib)
  set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
  set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)



  #if (AntTweakBar)
  #message("Found AntTweakBar")
  #set(INCLUDE_DIRS ${INCLUDE_DIRS} 3rdparty/AntTweakBar.1.16/include)
  #set(INSTALL_LIST ${INSTALL_LIST} 3rdparty/AntTweakBar.1.16/lib/AntTweakBar.dll)
  #set(CORE ${AntTweakBar} GLEW glut GL GLU X11)
  #add_definitions(/DGUI)
  ##else()
  #message("No AntTweakBar")
  #set(CORE ${AntTweakBar} ${GLEW} ${GLUT})
  #endif()

  #install (FILES ${INSTALL_LIST} DESTINATION ${CMAKE_SOURCE_DIR}/bin/Debug)
  #install (FILES ${INSTALL_LIST} DESTINATION ${CMAKE_SOURCE_DIR}/bin/Release)

elseif (APPLE)

  set(CMAKE_MACOSX_RPATH 1)
  set(CMAKE_CXX_FLAGS "-Wall -Wno-deprecated-declarations -Wno-reorder-ctor -Wno-unused-variable -g -stdlib=libc++ -std=c++14")
  set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)
  set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
  find_library(GL_LIB OpenGL)
  find_library(GLEW glew)
  find_library(GLFW glfw)
  add_definitions(-DAPPLE)

  set(INCLUDE_DIRS
    .
    /System/Library/Frameworks
    /usr/local/include
    external/include
    libsrc/
    )

  set(LIBRARY_DIRS libsrc/)

  #find_library(AntTweakBar NAMES AntTweakBar)
  #if (AntTweakBar)
  #  add_definitions(-DGUI)
  #  message("Found AntTweakBar")
  #  set(CORE ${AntTweakBar} ${GL_LIB} ${GL_GLUT})
  #else()
  #  message("No AntTweakBar")
  #  set(CORE ${GL_LIB} ${GL_GLUT})
  #endif()
  set(CORE agl ${GL_LIB} ${GLEW} ${GLFW})


elseif (UNIX)

  set(CMAKE_CXX_FLAGS "-Wall -g -std=c++17 -Wno-comment -Wno-sign-compare -Wno-reorder") 
  set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)
  set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

  #for FindGLM.cmake, FindGLFW3.cmake, other helpers
  #set (CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules) 

  FIND_PACKAGE(OpenGL REQUIRED) 
  FIND_PACKAGE(GLEW REQUIRED)
  #find_library(AntTweakBar NAMES AntTweakBar 
  #  PATHS 3rdparty/AntTweakBar/lib/ /usr/local/lib)

  set(INCLUDE_DIRS
    external/include
    libsrc
    )

  set(LIBRARY_DIRS
    /usr/X11R6/lib
    /usr/local/lib
    external/lib
    libsrc
    )

  #set(ODE ode pthread)
  add_definitions(-DUNIX)

  #if (AntTweakBar)
  #  message("Found AntTweakBar")
  #  set(INCLUDE_DIRS ${INCLUDE_DIRS} 3rdparty/AntTweakBar/include)
  #  set(LIBRARY_DIRS ${LIBRARY_DIRS} 3rdparty/AntTweakBar/lib)
  #  set(CORE ${AntTweakBar} GLEW glfw glut GL GLU X11)
  #  add_definitions(-DGUI)
  #else()
  #  message("No AntTweakBar")
  #  set(CORE GLEW glfw glut GL GLU X11)
  #endif()
  set(CORE agl GLEW glfw GL GLU X11)

endif()

include_directories(${INCLUDE_DIRS})
link_directories(${LIBRARY_DIRS})
add_subdirectory(assignments)
add_subdirectory(classexamples)
add_subdirectory(libsrc)
#if (IS_DIRECTORY "${PROJECT_SOURCE_DIR}/test")
  #add_subdirectory(test)
#endif()
if (IS_DIRECTORY "${PROJECT_SOURCE_DIR}/examples")
  add_subdirectory(examples)
endif()

function(get_all_targets var)
    set(targets)
    get_all_targets_recursive(targets ${CMAKE_CURRENT_SOURCE_DIR})
    set(${var} ${targets} PARENT_SCOPE)
endfunction()

macro(get_all_targets_recursive targets dir)
    get_property(subdirectories DIRECTORY ${dir} PROPERTY SUBDIRECTORIES)
    foreach(subdir ${subdirectories})
        get_all_targets_recursive(${targets} ${subdir})
    endforeach()

    get_property(current_targets DIRECTORY ${dir} PROPERTY BUILDSYSTEM_TARGETS)
    list(APPEND ${targets} ${current_targets})
endmacro()

if (WIN32)
get_all_targets(all_targets)
foreach (target ${all_targets})
message("targets: ${target}")
set_target_properties(${target} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
endforeach()
endif()

