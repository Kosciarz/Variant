set(SOURCES
    "Point.cpp"
    "StateMachine.cpp"
)

set(LIB_NAME project_lib)

message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
message(STATUS "CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")

add_library(${LIB_NAME} STATIC ${SOURCES})
target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)  

add_executable(${PROJECT_NAME} "Main.cpp")
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIB_NAME})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)