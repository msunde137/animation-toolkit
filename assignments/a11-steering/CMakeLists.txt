set(LIBS imgui ${CORE})
set(SOURCES world.cpp steerable.cpp steerable-basecode.cpp behaviors-basecode.cpp)

add_executable(a11-steering steeringdemo.cpp ${SOURCES})
target_link_libraries(a11-steering ${LIBS})
   
add_executable(a11-behaviors behaviorviewer.cpp ${SOURCES})
target_link_libraries(a11-behaviors ${LIBS})
