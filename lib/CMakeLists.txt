file(GLOB_RECURSE header_files_ CONFIGURE_DEPENDS ./*.h)
file(GLOB_RECURSE source_files_ CONFIGURE_DEPENDS ./*.cpp)

add_library(game_lib ${header_files_} ${source_files_})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(game_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


MACRO(SUBDIRLIST result curdir)
  FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
  SET(dirlist "")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${curdir}/${child})
      LIST(APPEND dirlist ${child})
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
ENDMACRO()

SUBDIRLIST(SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR})

foreach(subdir ${SUBDIRS})
    target_include_directories(game_lib PUBLIC ${subdir})
endforeach()
