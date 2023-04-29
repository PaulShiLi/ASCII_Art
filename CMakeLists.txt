	# minimum CMake version required
    cmake_minimum_required(VERSION 3.15)
    # Project name, version and description
    project(cpp-discBot VERSION 1.0 DESCRIPTION "A discord bot")
    
    # Autofind Curl package
    find_package(CURL REQUIRED)

    # Create an executable
    add_executable(${PROJECT_NAME}
        src/main.cpp
    )
     
    add_subdirectory(deps/cpp-dotenv)
    add_subdirectory(deps/DPP)
    add_subdirectory(deps/json)

    target_link_libraries(${PROJECT_NAME} 
        cpp_dotenv
        dpp
        nlohmann_json
        ${CURL_LIBRARIES}
    )
    
    include_directories(
        ${CURL_INCLUDE_DIR}
    )

    link_directories(
        ${CURL_LIBRARY_DIRS}
    )

    # Specify includes
    target_include_directories(${PROJECT_NAME} PRIVATE
        deps/DPP/include
        # Remember to add the include directories of any other libraries too
    )
    
    # Set C++ version
    set_target_properties(${PROJECT_NAME} PROPERTIES
        CXX_STANDARD 17 # or 20 if you want something more recent
        CXX_STANDARD_REQUIRED ON
    )
    