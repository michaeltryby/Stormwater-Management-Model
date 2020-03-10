


add_executable(test_datetime
    test_datetime.cpp
    ${CMAKE_SOURCE_DIR}/src/solver/datetime.c
    )

target_include_directories(test_datetime
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src/solver/
    )

target_link_libraries(test_datetime
    ${Boost_LIBRARIES}
    )



add_test(NAME test_datetime
    COMMAND "${TEST_BIN_DIRECTORY}/test_datetime"
    )
