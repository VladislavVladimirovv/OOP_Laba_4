cmake_minimum_required(VERSION 3.16)
project(OOP_Laba_4)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Подключение Google Test через FetchContent
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

include_directories(include)

# Основной исполняемый файл
add_executable(main 
    src/main.cpp 
    src/rectangle.cpp
    src/rhombus.cpp
    src/trapezoid.cpp
    src/array.cpp
)

target_compile_features(main PRIVATE cxx_std_20)

# Исполняемый файл для тестов
add_executable(tests
    tests.cpp
    src/rectangle.cpp
    src/rhombus.cpp
    src/trapezoid.cpp
    src/array.cpp
)

target_compile_features(tests PRIVATE cxx_std_20)

# Подключение Google Test к тестам
target_link_libraries(tests gtest_main)

# Включение системы тестирования CMake
enable_testing()
add_test(NAME AllTests COMMAND tests)