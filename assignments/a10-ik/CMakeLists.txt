set(LIBS imgui ${LIBS})

add_executable(a10-ikviewer ikviewer.cpp ik_controller.cpp)
target_link_libraries(a10-ikviewer ${LIBS})

add_executable(a10-dancer dancer.cpp ik_controller.cpp)
target_link_libraries(a10-dancer ${LIBS})

add_executable(a10-looker looker.cpp)
target_link_libraries(a10-looker ${LIBS})

add_executable(a10-unique unique.cpp)
target_link_libraries(a10-unique ${LIBS})
