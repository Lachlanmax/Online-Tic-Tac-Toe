# Online Tic-Tac-Toe (C++ LAN Edition)

A multiplayer Tic Tac Toe game implemented in C++ with TCP/IP networking for LAN play.

## Features

- **Multiplayer over LAN**: Two players can play against each other over a local network
- **Server-Client Architecture**: One player hosts as a server, another connects as a client
- **Real-time State Synchronization**: Board state is updated and synchronized between both players
- **Win/Draw Detection**: Automatic detection of wins, losses, and draws
- **Windows Compatible**: Uses Winsock2 for networking

## Building

### Using CMake (Recommended)

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

The executable `tictactoe.exe` will be created in the build directory.

### Using Visual Studio Compiler (cl.exe)

```bash
cl /EHsc main.cpp game.cpp server.cpp client.cpp /link ws2_32.lib
```

## How to Play

1. **Start the Server (Host)**
   - Run the executable and choose option `1` (Host Game)
   - The server will wait for a client to connect
   - The host becomes Player X

2. **Start the Client (Join)**
   - Run the executable and choose option `2` (Join Game)
   - Enter the server's IP address (e.g., 192.168.1.100 for remote, or 127.0.0.1 for local testing)
   - The client becomes Player O

3. **Playing the Game**
   - Board positions are numbered 0-8:
     ```
     0 | 1 | 2
     ---------
     3 | 4 | 5
     ---------
     6 | 7 | 8
     ```
   - Players alternate turns entering positions (0-8)
   - First to get 3 in a row wins!
   - If all 9 positions are filled with no winner, it's a draw

## Network Details

- **Port**: 5555
- **Protocol**: TCP/IP
- **Supported Networks**: Works on any LAN (local network)
- **IP Address**: Server needs to be accessible at its IP address

## Architecture

- **game.h/game.cpp**: Core Tic Tac Toe game logic, board management, win detection
- **server.h/server.cpp**: Server implementation that handles two client connections and game flow
- **client.h/client.cpp**: Client implementation that connects to server and handles user input
- **main.cpp**: Entry point with menu for choosing server or client mode

## Requirements

- Windows OS (uses Winsock2)
- C++ compiler supporting C++17
- CMake 3.10+ (for building)
