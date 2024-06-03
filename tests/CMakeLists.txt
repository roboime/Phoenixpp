macro(package_add_test TESTNAME FILES LIBRARIES)
    add_executable(${TESTNAME} ${FILES})
    target_link_libraries(${TESTNAME} GTest::gtest GTest::gmock GTest::gtest_main ${LIBRARIES})
    gtest_discover_tests(${TESTNAME}
            WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/tests"
            PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/tests"
    )
    set_target_properties(${TESTNAME} PROPERTIES FOLDER tests)
endmacro()

package_add_test(testMessageListener messaging/test_message_listener.cpp messaging)