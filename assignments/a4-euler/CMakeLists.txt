set(LIBS atkmath imgui ${LIBS})
add_executable(a4-teapots teapots.cpp)
target_link_libraries(a4-teapots ${LIBS})

add_executable(a4-test-euler test_euler.cpp)
target_link_libraries(a4-test-euler ${LIBS})

add_executable(a4-unique unique.cpp)
target_link_libraries(a4-unique ${LIBS})
