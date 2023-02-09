# CMakeList.txt: проект CMake для intern_task; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

project ("intern_task")

# Добавьте источник в исполняемый файл этого проекта.
add_executable (intern_task "intern_task.cpp" "intern_task.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET intern_task PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
