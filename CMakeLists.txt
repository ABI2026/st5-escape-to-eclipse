cmake_minimum_required(VERSION 3.10)

project("Escape-To-Eclipse")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

include(GNUInstallDirs)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Compiler SECURITY Configuration
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(
        -Wall                
        -Wextra              
        -Wpedantic           
        -Wconversion         
        -Wshadow             
        -Wformat=2           
        -Werror              
    )
elseif(MSVC)
    add_compile_options(
        /W4                 
        /WX                 
    )
endif()

# Secury Memory via sanatizers
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    # Memory safety checks
    set(SANITIZER_OPTIONS "-fsanitize=address,undefined")
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_options(${SANITIZER_OPTIONS})
        add_link_options(${SANITIZER_OPTIONS})
    endif()

    # Enable stack protection
    add_compile_options(-fstack-protector-strong)

    # Enable control flow integrity
    include(CheckCXXCompilerFlag)
    check_cxx_compiler_flag("-fsanitize=cfi" HAS_CFI_FLAG)
    if(HAS_CFI_FLAG)
        add_compile_options(-fsanitize=cfi -flto)
        add_link_options(-fsanitize=cfi -flto)
    endif()
endif()

# Disable some insecure functions (POSIX only)
if(UNIX)
    add_definitions(-D_FORTIFY_SOURCE=2) # Buffer overflow protection
endif()

# Link-time optimization
if(NOT CMAKE_BUILD_TYPE MATCHES "Debug")
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

# Include subdirectories 
add_subdirectory(lib)

# Include SFML
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(main ./src/main.cpp)
target_link_libraries(main PRIVATE sfml-graphics)
target_link_libraries(main PUBLIC game_lib)
target_compile_features(main PRIVATE cxx_std_17)

target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib)

if(WIN32)
    add_custom_command(
        TARGET main
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:main>
        VERBATIM)
endif()
