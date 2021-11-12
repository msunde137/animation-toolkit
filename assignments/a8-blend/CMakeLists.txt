add_executable(a8-reorient reorient.cpp)
target_link_libraries(a8-reorient ${LIBS})

add_executable(a8-zombie-arms zombie_arms.cpp)
target_link_libraries(a8-zombie-arms ${LIBS})

add_executable(a8-splice splice.cpp)
target_link_libraries(a8-splice ${LIBS})

add_executable(a8-blend blend.cpp)
target_link_libraries(a8-blend ${LIBS})

add_executable(a8-unique unique.cpp)
target_link_libraries(a8-unique ${LIBS})
