	# minimum CMake version required
cmake_minimum_required(VERSION 3.15)
# Project name, version and description
project(cpp-discBot VERSION 1.0 DESCRIPTION "A discord bot")

# Create an executable
add_executable(${PROJECT_NAME}
    src/main.cpp
)
 
add_subdirectory(deps/sleepy-discord)
add_subdirectory(deps/cpp-dotenv)


target_link_libraries(${PROJECT_NAME} 
    sleepy-discord
    cpp_dotenv
)

# Set C++ version
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17 # or 20 if you want something more recent
    CXX_STANDARD_REQUIRED ON
)
