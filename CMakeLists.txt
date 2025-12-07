cmake_minimum_required(VERSION 4.0)
project(toDoSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Ensure Qt UIC searches our UI folders (we moved UI files to data/UI)
list(APPEND CMAKE_AUTOUIC_SEARCH_PATHS "${CMAKE_SOURCE_DIR}/data/UI" "${CMAKE_SOURCE_DIR}/implement/login")

# Keep user's Qt5 prefix by default; users can override CMAKE_PREFIX_PATH if needed
set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/qt@5")

# Find Qt Widgets (Qt5). If you prefer Qt6, change this or set CMAKE_PREFIX_PATH accordingly.
find_package(Qt5 COMPONENTS Core Widgets Test Sql REQUIRED)

add_executable(toDoSystem
        main.cpp
        implement/login/LoginWindow.cpp
        TodoWindow.cpp
        log/Logger.cpp
        data/UI/loginwindow.ui
        data/UI/todo.ui
        utils/EnvPath.cpp
        utils/EnvPath.h
)

target_link_libraries(toDoSystem
        Qt5::Widgets
        Qt5::Core
        Qt5::Sql
)
