# Headers
file(GLOB HDR
    safety/*.hpp
    server/*.hpp
    output/*.hpp
    *.hpp
)

# Sources
file(GLOB SRC
    safety/*.cpp
    server/*.cpp
    output/*.cpp
    *.cpp
)

add_executable(server ${HDR} ${SRC} main.cpp)

# Include the path to the ASIO headers
target_include_directories(server PRIVATE ${INCLUDE_DIR} ${ASIO_INCLUDE_DIR})

# Link pthread library
target_link_libraries(server pthread)

if(MINGW)
  target_link_libraries(server ws2_32 wsock32)
endif()
