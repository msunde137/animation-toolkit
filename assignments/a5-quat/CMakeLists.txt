set(LIBS atkmath ${LIBS})

add_executable(a5-unique unique.cpp)
target_link_libraries(a5-unique ${LIBS})

add_executable(a5-test-quat test_quat.cpp)
target_link_libraries(a5-test-quat ${LIBS})

add_executable(a5-test-quat-mat test_quat_mat.cpp)
target_link_libraries(a5-test-quat-mat ${LIBS})
