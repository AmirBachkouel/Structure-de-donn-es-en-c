add_library(queue STATIC queue.c)
target_include_directories(queue PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(queue_demo queuemain.c)
target_link_libraries(queue_demo PRIVATE queue)
