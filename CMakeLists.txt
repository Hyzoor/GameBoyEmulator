cmake_minimum_required(VERSION 3.10.0)

project(test1 VERSION 0.1.0 LANGUAGES C CXX)

# Busca todos los archivos .cpp en el directorio raíz
file(GLOB SOURCES "src/*.cpp")

# Incluyo directorio "include" para saber donde buscar los .h
include_directories(${PROJECT_SOURCE_DIR}/include)

# Crea el ejecutable usando todos los .cpp encontrados
add_executable(${PROJECT_NAME} ${SOURCES})