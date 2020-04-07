

# Unit tests for swmm solver
set(solver_test_srcs
    test_solver.cpp
    test_swmm5.cpp
    )

add_executable(test_solver
    ${solver_test_srcs}
    )

target_compile_features(test_solver
    PUBLIC
      cxx_generalized_initializers
  )

target_link_libraries(test_solver
    ${Boost_LIBRARIES}
    swmm5
    )

set_target_properties(test_solver
    PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    )



# Unit tests for datatime conversions
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

set_target_properties(test_datetime
    PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    )
