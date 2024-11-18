file(GLOB_RECURSE header_files_ CONFIGURE_DEPENDS ./*.h)
file(GLOB_RECURSE source_files_ CONFIGURE_DEPENDS ./*.cpp)

add_library(game_lib ${header_files_} ${source_files_})

target_include_directories(game_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})