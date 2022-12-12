cmake_minimum_required (VERSION 3.18)
project (utils VERSION 0.0.1 LANGUAGES CXX)

# Determine if utils is built as a subproject (using add_subdirectory) or if it is the master project.

if (NOT DEFINED NETEWORK_MASTER_PROJECT)
  set (UTILS_MASTER_PROJECT OFF)

  if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set (UTILS_MASTER_PROJECT ON)
  endif ()
endif ()


# Set an additional path to the CMake modules and connect them

list (APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(NestingFileSearch)
include(CMakeDependentOption)


# Options available for project customization

cmake_dependent_option (UTILS_BUILD_SHARED_LIBS "Build the project as a dynamic library" "${BUILD_SHARED_LIBS}" "UTILS_MASTER_PROJECT" ${UTILS_MASTER_PROJECT})
cmake_dependent_option (UTILS_BUILD_TESTING "Build tests for the project" "${BUILD_TESTING}" "UTILS_MASTER_PROJECT" ${UTILS_MASTER_PROJECT})

option (UTILS_INSTALL "Generate a target for project installation" ON)
option (UTILS_BUILD_EXAMPLE "Build examples for a project" OFF)
option (UTILS_GENERATE_DOCUMENTATION "Generate documentation when building a project" OFF)
option (UTILS_PEDANTIC "Enable the display of additional warnings" OFF)
option (UTILS_WERROR "Handle all compiler warnings with errors" OFF)
option (UTILS_MSVC_STATIC_RUNTIME "Link static runtime libraries" OFF)
option (UTILS_ENABLE_COVERAGE "Run coverage" OFF)
option (UTILS_ENABLE_SANITIZERS "Run static analysis" OFF)

message (STATUS "UTILS_BUILD_SHARED_LIBS - ${UTILS_BUILD_SHARED_LIBS}")
message (STATUS "UTILS_BUILD_TESTING - ${UTILS_BUILD_TESTING}")
message (STATUS "UTILS_INSTALL - ${UTILS_INSTALL}")
message (STATUS "UTILS_BUILD_EXAMPLE - ${UTILS_BUILD_EXAMPLE}")
message (STATUS "UTILS_GENERATE_DOCUMENTATION - ${UTILS_GENERATE_DOCUMENTATION}")
message (STATUS "UTILS_PEDANTIC - ${UTILS_PEDANTIC}")
message (STATUS "UTILS_WERROR - ${UTILS_WERROR}")
message (STATUS "UTILS_ENABLE_COVERAGE - ${UTILS_ENABLE_COVERAGE}")
message (STATUS "UTILS_ENABLE_SANITIZERS - ${UTILS_ENABLE_SANITIZERS}")

# Configuring project output directories

if (UTILS_MASTER_PROJECT)
  set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
  set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
  set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib) 
endif ()    


# Configuring project build options

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set_property (GLOBAL PROPERTY USE_FOLDERS ON)
set_property (GLOBAL PROPERTY LINKER_LANGUAGE CXX)
string (APPEND CMAKE_DEBUG_POSTFIX "_dbg")


# Additional options for building on Windows  
if (WIN32)
    set (CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

    if (MSVC AND ${UTILS_MSVC_STATIC_RUNTIME})
        set (FLAG_VARS 
            CMAKE_CXX_FLAGS 
            CMAKE_CXX_FLAGS_DEBUG 
            CMAKE_CXX_FLAGS_RELEASE
            CMAKE_CXX_FLAGS_MINSIZEREL 
            CMAKE_CXX_FLAGS_RELWITHDEBINFO
        )

        foreach (FLAG_VAR ${FLAG_VARS})
            if (${FLAG_VAR} MATCHES "/MD")
                string (REGEX REPLACE "/MD" "/MT" ${FLAG_VAR} "${${FLAG_VAR}}")
            endif ()
        endforeach ()
        
        string (APPEND CMAKE_DEBUG_POSTFIX "_mt")
        string (APPEND CMAKE_RELEASE_POSTFIX "_mt")
    else ()
        string (APPEND CMAKE_DEBUG_POSTFIX "_md")
        string (APPEND CMAKE_RELEASE_POSTFIX "_md")
    endif ()
    message (STATUS "UTILS_MSVC_STATIC_RUNTIME - ${UTILS_MSVC_STATIC_RUNTIME}")
endif ()

# Enable coverage

if (UTILS_ENABLE_COVERAGE AND UNIX)
    list (APPEND CMAKE_CXX_FLAGS "--coverage -g -O0")
    find_package(Threads REQUIRED)
endif ()

if(UTILS_ENABLE_SANITIZERS)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g -fno-omit-frame-pointer -fsanitize=address -fsanitize=leak -fsanitize=undefined")
endif()

# Adding subdirectories to the project

add_subdirectory (lib)

if (UTILS_BUILD_TESTING)
    include (CTest)
    enable_testing ()
    add_subdirectory (test)
endif ()

if (UTILS_BUILD_EXAMPLE)
    add_subdirectory (example)
endif ()
