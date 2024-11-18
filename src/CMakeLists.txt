# Include all free headers and sources
file(GLOB_RECURSE header_files_ CONFIGURE_DEPENDS ./*.h)
file(GLOB_RECURSE source_files_ CONFIGURE_DEPENDS ./*.cpp)

add_library(local_includes ${header_files_} ${source_files_})

target_include_directories(local_includes PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
