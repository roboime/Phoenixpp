add_library(Factories
    component_factory.h
    component_factory.cpp
)
target_include_directories(Factories PRIVATE ${CMAKE_SOURCE_DIR}/utils/components)
target_include_directories(Factories PRIVATE ${CMAKE_SOURCE_DIR}/utils/messages)
target_include_directories(Factories PRIVATE ${CMAKE_SOURCE_DIR}/implementations/user_interface)
target_include_directories(Factories PRIVATE ${CMAKE_SOURCE_DIR}/implementations/logic/test_logic)
target_include_directories(Factories PRIVATE ${CMAKE_SOURCE_DIR}/implementations/vision/test_vision)
set_target_properties(Factories PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(Factories PRIVATE nlohmann_json)
target_link_libraries(Factories PRIVATE TestLogic)
target_link_libraries(Factories PRIVATE TestVision)