add_executable(a2-gradient gradient.cpp)
target_link_libraries(a2-gradient ${LIBS})

add_executable(a2-unique unique.cpp)
target_link_libraries(a2-unique ${LIBS})

add_executable(a2-drawcurve drawcurve.cpp)
target_link_libraries(a2-drawcurve ${LIBS})

add_executable(a2-particlecubic particlecubic.cpp)
target_link_libraries(a2-particlecubic ${LIBS})

add_executable(a2-screensaver screensaver.cpp)
target_link_libraries(a2-screensaver ${LIBS})
