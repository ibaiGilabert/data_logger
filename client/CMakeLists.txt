add_executable(client main.cpp client.cpp)

# Include the path to the ASIO headers
target_include_directories(client PRIVATE ${INCLUDE_DIR} ${ASIO_INCLUDE_DIR})

# Link pthread library
target_link_libraries(client pthread)

if(MINGW)
  target_link_libraries(client ws2_32)
endif()
