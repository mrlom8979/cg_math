cmake_minimum_required(VERSION 3.16)
project(cg_math)

# Переключатель для выбора типа библиотеки (по умолчанию статическая)
option(CG_MATH_BUILD_SHARED "Build cg_math as a shared library" OFF)

# Поиск всех .cpp и .h файлов
file(GLOB_RECURSE CG_MATH_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE CG_MATH_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")

# Создание библиотеки
if (CG_MATH_BUILD_SHARED)
  add_library(cg_math SHARED ${CG_MATH_SOURCES} ${CG_MATH_HEADERS})
  target_compile_definitions(cg_math PRIVATE CG_MATH_SHARED)
else()
  add_library(cg_math STATIC ${CG_MATH_SOURCES} ${CG_MATH_HEADERS})
endif()

# Добавление предкомпилированных заголовков (если используется pch.h)
target_precompile_headers(cg_math PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/pch.h")

# Установка директорий для заголовочных файлов
target_include_directories(cg_math PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

# Настройка платформо-зависимых флагов
if(UNIX)
  target_compile_definitions(cg_math PRIVATE __LINUX__)
elseif (WIN32)
  target_compile_definitions(cg_math PRIVATE __WIN32__)
endif()

