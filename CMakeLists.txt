cmake_minimum_required(VERSION 3.10.0)

project(test1 VERSION 0.1.0 LANGUAGES C CXX)

# Busca todos los archivos .cpp en el directorio raíz
file(GLOB SOURCES "src/*.cpp")

# Incluyo directorio "include" para saber donde buscar los .h
include_directories(${PROJECT_SOURCE_DIR}/include)

# Crea el ejecutable usando todos los .cpp encontrados
add_executable(${PROJECT_NAME} ${SOURCES})


# Library JSON Parser
include(FetchContent)

cmake_policy(SET CMP0135 NEW)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz)
FetchContent_MakeAvailable(json)

target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)