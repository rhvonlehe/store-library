cmake_minimum_required(VERSION 3.12)

project(store-library VERSION 1.0 LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
    json
    URL  https://github.com/nlohmann/json/releases/download/v3.10.5/json.tar.xz
)

FetchContent_MakeAvailable(json)


set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
add_library(store SHARED)
target_compile_features(store PRIVATE cxx_std_17)

target_sources(store
    PRIVATE
    Store.cpp
    JsonConvertUtils.cpp
    OSMutex.cpp
)

target_link_libraries(store
    PRIVATE
    nlohmann_json::nlohmann_json
)
