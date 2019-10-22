add_library(attestsource "")

target_sources(attestsource 
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/atcommandscheduler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/utils.cpp
PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/atcommandscheduler.h
    ${CMAKE_CURRENT_LIST_DIR}/atcommandbase.h
    ${CMAKE_CURRENT_LIST_DIR}/utils.h
)

target_include_directories(attestsource PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)