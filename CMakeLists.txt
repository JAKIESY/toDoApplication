cmake_minimum_required(VERSION 3.16)
project(MyQt5App LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 让 Qt 自动处理 moc / uic / rcc
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/qt@5")


# 找 Qt5 Widgets 模块
find_package(Qt5 COMPONENTS Widgets REQUIRED)

# 可执行程序（Qt 项目）
add_executable(MyQt5App
        main.cpp
        mainwindow.cpp
        mainwindow.hpp
        mainwindow.ui
)

# 链接 Qt5 Widgets
target_link_libraries(MyQt5App PRIVATE Qt5::Widgets)
