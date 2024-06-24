cmake_minimum_required(VERSION 3.10)
project(challenge)

# Define std required
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define paths
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(ASIO_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/lib/asio-1-29-0/asio/include)

# Add subdirectories
add_subdirectory(server)
add_subdirectory(client)
