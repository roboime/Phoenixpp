add_subdirectory(messages)
add_subdirectory(implementations)
add_library(Components
    base_component.h
    base_component.cpp
)
target_include_directories(Components PRIVATE ${CMAKE_SOURCE_DIR}/src/components/messages)
target_include_directories(Components PRIVATE ${CMAKE_SOURCE_DIR}/src/utils)
target_link_libraries(Components PUBLIC Messages)
target_link_libraries(Components PUBLIC Utils)
