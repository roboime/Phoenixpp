add_library(Factories
    component_factory.h
    component_factory.cpp
)
target_include_directories(Factories PUBLIC ${CMAKE_SOURCE_DIR}/src/components/implementations/filters/kalman_filter)
target_include_directories(Factories PUBLIC ${CMAKE_SOURCE_DIR}/src/components/implementations/logic/test_logic)
target_include_directories(Factories PUBLIC ${CMAKE_SOURCE_DIR}/src/components/implementations/vision/test_vision)
target_include_directories(Factories PUBLIC ${CMAKE_SOURCE_DIR}/src/components/implementations/communicator/udp_communicator)
target_include_directories(Factories PUBLIC ${CMAKE_SOURCE_DIR}/src/components/implementations/navigation/elo_mec_tester)
target_include_directories(Factories PUBLIC ${CMAKE_SOURCE_DIR}/src/components)
target_link_libraries(Factories PUBLIC KalmanFilter)
target_link_libraries(Factories PUBLIC TestLogic)
target_link_libraries(Factories PUBLIC TestVision)
target_link_libraries(Factories PUBLIC UdpVision)
target_link_libraries(Factories PUBLIC UdpCommunicator)
target_link_libraries(Factories PUBLIC EloMecTester)
target_link_libraries(Factories PUBLIC Components)
target_link_libraries(Factories PUBLIC Eigen3::Eigen)
