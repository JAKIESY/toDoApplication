cmake_minimum_required(VERSION 4.0)
project(toDoSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Keep user's Qt5 prefix by default; users can override CMAKE_PREFIX_PATH if needed
set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/qt@5")

# Find Qt Widgets (Qt5). If you prefer Qt6, change this or set CMAKE_PREFIX_PATH accordingly.
find_package(Qt5 COMPONENTS Core Widgets Test Sql REQUIRED)

add_executable(toDoSystem
        main.cpp
        LoginWindow.cpp
        TodoWindow.cpp
        log/Logger.cpp
        loginwindow.ui
        todo.ui
        utils/EnvPath.cpp
        utils/EnvPath.hpp
)

target_link_libraries(toDoSystem
        Qt5::Widgets
        Qt5::Core
        Qt5::Sql
)
