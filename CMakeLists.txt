cmake_minimum_required(VERSION 3.10)
project(HTTPServerExample VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Point to your local libmicrohttpd build directory
#set(libmicrohttpd_ROOT "/path/to/libmicrohttpd-source")  # Replace with the absolute path, e.g., /home/yourusername/libmicrohttpd-source

# Include the custom Find module
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")  # Assuming your Findlibmicrohttpd.cmake is in cmake/ subdirectory
find_package(libmicrohttpd REQUIRED)

# Find and link OpenSSL
find_package(OpenSSL REQUIRED)

# Add your executable
add_executable(https_server source/main.cpp)

# Link libraries
target_link_libraries(https_server PRIVATE ${LIBMHD_LIBRARIES} OpenSSL::SSL OpenSSL::Crypto)
target_include_directories(https_server PRIVATE ${LIBMHD_INCLUDE_DIRS} ${OpenSSL_INCLUDE_DIR})
