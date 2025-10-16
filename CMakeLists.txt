cmake_minimum_required(VERSION 3.10)
project(OnlineTicTacToe)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source files
add_executable(tictactoe 
    main.cpp
    game.cpp
    server.cpp
    client.cpp
)

# Link Windows Socket library (required for Winsock2)
if(WIN32)
    target_link_libraries(tictactoe ws2_32)
endif()

# Include directories
target_include_directories(tictactoe PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
