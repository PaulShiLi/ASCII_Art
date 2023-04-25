	# minimum CMake version required
cmake_minimum_required(VERSION 3.15)
# Project name, version and description
project(discord-bot VERSION 1.0 DESCRIPTION "A discord bot")
 
# Add DPP as dependency
add_subdirectory(libs/cpp-dotenv)
# You can also add any other libs you want to use
add_subdirectory(libs/DPP) 

# Create an executable
add_executable(${PROJECT_NAME}
    src/main.cpp
    # your other files...
)
 
# Linking libraries
target_link_libraries(${PROJECT_NAME}
    dpp
    # Add any other libs you want to use here
    cpp_dotenv
)
 
# Specify includes
target_include_directories(${PROJECT_NAME} PRIVATE
    libs/DPP/include
    # Remember to add the include directories of any other libraries too
    libs/cpp-dotenv/include
)
 
# Set C++ version
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17 # or 20 if you want something more recent
    CXX_STANDARD_REQUIRED ON
)
