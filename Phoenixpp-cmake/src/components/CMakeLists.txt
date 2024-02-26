add_subdirectory(messages)
add_subdirectory(implementations)
add_library(Components
    base_component.h
    base_component.cpp
    parameters_manager.h
    parameters_manager.cpp
)
target_include_directories(Components PRIVATE ${CMAKE_SOURCE_DIR}/src/components/messages)
target_link_libraries(Components PUBLIC Messages)
target_link_libraries(Components PUBLIC nlohmann_json)
