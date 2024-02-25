add_library(Components
    base_ui.h
    base_ui.cpp
    base_component.h
    base_component.cpp
    parameters_manager.h
    parameters_manager.cpp
)
# target_include_directories(Components PRIVATE ${CMAKE_SOURCE_DIR}/src/factories)
target_link_libraries(Components PRIVATE Factories)
set_target_properties(Components PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(Components PRIVATE nlohmann_json)