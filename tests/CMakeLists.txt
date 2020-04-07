#
# CMakeLists.txt - CMake configuration file for epanet/tests
#


#Prep ourselves for compiling with boost
include(../extern/boost.cmake)


add_subdirectory(outfile)
add_subdirectory(solver)


# Setting up tests to run from build tree
set(TEST_BIN_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIGURATION>")


###########  ADD TESTS HERE  ###########
add_test(NAME test_output
    COMMAND "${TEST_BIN_DIRECTORY}/test_output"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/outfile/data
    )

add_test(NAME test_solver
    COMMAND "${TEST_BIN_DIRECTORY}/test_solver"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/solver/data
    )

add_test(NAME test_datetime
    COMMAND "${TEST_BIN_DIRECTORY}/test_datetime"
    )
