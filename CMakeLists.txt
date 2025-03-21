cmake_minimum_required(VERSION 3.16)
project(cgmath)

# Переключатель для выбора типа библиотеки (по умолчанию статическая)
option(CG_MATH_BUILD_SHARED "Build cgmath as a shared library" OFF)

# Поиск всех .cpp и .h файлов
file(GLOB_RECURSE CG_MATH_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE CG_MATH_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")

# Создание библиотеки
if (CG_MATH_BUILD_SHARED)
  add_library(cgmath SHARED ${CG_MATH_SOURCES} ${CG_MATH_HEADERS})
  target_compile_definitions(cgmath PRIVATE CG_MATH_SHARED)
else()
  add_library(cgmath STATIC ${CG_MATH_SOURCES} ${CG_MATH_HEADERS})
endif()

# Добавление предкомпилированных заголовков (если используется pch.h)
target_precompile_headers(cgmath PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/pch.h")

# Установка директорий для заголовочных файлов
target_include_directories(cgmath PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

# Настройка платформо-зависимых флагов
if(UNIX)
  target_compile_definitions(cgmath PRIVATE __LINUX__)
elseif (WIN32)
  target_compile_definitions(cgmath PRIVATE __WIN32__)
endif()

