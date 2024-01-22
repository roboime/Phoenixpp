add_library(TestLogic test_logic/test_logic.h test_logic/test_logic.cpp)
target_include_directories(TestLogic PRIVATE ${CMAKE_SOURCE_DIR}/utils/interfaces)
target_include_directories(TestLogic PRIVATE ${CMAKE_SOURCE_DIR}/utils/structs)