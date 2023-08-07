set(lib dbg)
include_directories(${CMAKE_CURRENT_LIST_DIR} ${LUA_DIR})
add_library(${lib} SHARED
    ${CMAKE_CURRENT_LIST_DIR}/dbg.h
    ${CMAKE_CURRENT_LIST_DIR}/dbg.c
)
target_link_libraries(${lib} PUBLIC lua)