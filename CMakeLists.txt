cmake_minimum_required(VERSION 3.16)
project(todo-qtquick VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

if(MSVC)
  add_compile_options(/utf-8)
endif()

find_package(Qt6 REQUIRED COMPONENTS Quick Qml QuickControls2 Widgets)

qt_add_executable(todo-qtquick
  src/main.cpp
  src/todostore.cpp
  src/todostore.h
  src/todocontroller.cpp
  src/todocontroller.h
)

qt_add_qml_module(todo-qtquick
  URI TodoApp
  VERSION 1.0
  QML_FILES qml/Main.qml
)

target_link_libraries(todo-qtquick PRIVATE Qt6::Quick Qt6::Qml Qt6::QuickControls2 Qt6::Widgets)

if(WIN32)
  set_target_properties(todo-qtquick PROPERTIES WIN32_EXECUTABLE ON OUTPUT_NAME "todo-qtquick")
endif()
