# CMakeList.txt: проект CMake для intern_task; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

project ("intern_task")
# Добавьте источник в исполняемый файл этого проекта.
add_executable (first_program_task "first_program/first_program.cpp" "first_program/buffer.cpp" "first_program/reader.cpp" "first_program/writer.cpp")
add_executable(second_program_task "second_program/second_program.cpp" "second_program/receiver.cpp")
# TODO: Добавьте тесты и целевые объекты, если это необходимо.
