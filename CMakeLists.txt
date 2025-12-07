cmake_minimum_required(VERSION 4.0)
project(toDoSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Ensure Qt UIC searches our UI folders (we moved UI files to data/UI)
list(APPEND CMAKE_AUTOUIC_SEARCH_PATHS "${CMAKE_SOURCE_DIR}/implement/UI" "${CMAKE_SOURCE_DIR}/implement/login")

# Add build autogen include dir for globally generated headers
include_directories("${CMAKE_BINARY_DIR}/toDoSystem_autogen/include")

# Keep user's Qt5 prefix by default; users can override CMAKE_PREFIX_PATH if needed
set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/qt@5")

# Find Qt Widgets (Qt5). If you prefer Qt6, change this or set CMAKE_PREFIX_PATH accordingly.
find_package(Qt5 COMPONENTS Core Widgets Test Sql REQUIRED)

add_executable(toDoSystem
        main.cpp
        implement/login/LoginWindow.cpp
        implement/todo/TodoWindow.cpp
        log/Logger.cpp
        implement/UI/loginwindow.ui
        implement/UI/todo.ui
        utils/EnvPath.cpp
        utils/EnvPath.h
)

target_link_libraries(toDoSystem
        Qt5::Widgets
        Qt5::Core
        Qt5::Sql
)
