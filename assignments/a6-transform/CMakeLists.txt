add_executable(a6-test-slerp test_slerp.cpp)
target_link_libraries(a6-test-slerp ${LIBS} atkmath)

add_executable(a6-boxes boxes.cpp)
target_link_libraries(a6-boxes ${LIBS})

add_executable(a6-slerp-teapot slerp_teapot.cpp)
target_link_libraries(a6-slerp-teapot ${LIBS} atkmath)

add_executable(a6-skeleton-practice skeleton_practice.cpp)
target_link_libraries(a6-skeleton-practice ${LIBS})

add_executable(a6-tentacle tentacle.cpp)
target_link_libraries(a6-tentacle ${LIBS})