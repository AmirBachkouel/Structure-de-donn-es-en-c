add_library(stack STATIC stack.c)
target_include_directories(stack PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(stack_demo stackmain.c)
target_link_libraries(stack_demo PRIVATE stack)
