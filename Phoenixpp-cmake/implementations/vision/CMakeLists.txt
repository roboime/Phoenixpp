add_library(TestVision test_vision/test_vision.h test_vision/test_vision.cpp)
target_include_directories(TestVision PRIVATE ${CMAKE_SOURCE_DIR}/utils/interfaces)
target_include_directories(TestVision PRIVATE ${CMAKE_SOURCE_DIR}/utils/structs)