macro(package_add_test TESTNAME FILES LIBRARIES)
    add_executable(${TESTNAME} ${FILES})
    target_link_libraries(${TESTNAME} GTest::gtest GTest::gmock GTest::gtest_main ${LIBRARIES}
            Qt6::Core
            Qt6::Gui
            Qt6::Widgets
            Qt6::Network
    )
    gtest_discover_tests(${TESTNAME}
            WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/tests"
            PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/tests"
    )
    set_target_properties(${TESTNAME} PROPERTIES FOLDER tests)
endmacro()

#package_add_test(testMessageListener messaging/test_environment.cpp messaging)
package_add_test(testCore core/test_core.cpp core)