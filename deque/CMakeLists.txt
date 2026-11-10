add_library(deque STATIC deque.c)
target_include_directories(deque PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(deque_demo dequemain.c)
target_link_libraries(deque_demo PRIVATE deque)
