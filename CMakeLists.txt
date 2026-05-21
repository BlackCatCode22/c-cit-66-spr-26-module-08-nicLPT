cmake_minimum_required(VERSION 3.15)
project(WeatherApp)

set(CMAKE_CXX_STANDARD 17)

# 1. Global Settings
include(FetchContent)
set(BUILD_SHARED_LIBS OFF CACHE INTERNAL "") # Force static linking

# 2. SSL/HTTPS Settings for Windows (Crucial for api.weather.gov)
set(CURL_USE_SCHANNEL ON CACHE INTERNAL "")
set(CMAKE_USE_SCHANNEL ON CACHE INTERNAL "")
set(CURL_USE_OPENSSL OFF CACHE INTERNAL "")

# 3. Configure ASIO (For Crow)
FetchContent_Declare(
        asio
        URL https://github.com/chriskohlhoff/asio/archive/refs/tags/asio-1-30-2.zip
)
FetchContent_MakeAvailable(asio)

# 4. Configure CURL (For Fetching Data)
FetchContent_Declare(
        curl
        URL https://github.com/curl/curl/archive/refs/tags/curl-8_7_1.zip
)
# Settings to keep the build fast and static
set(BUILD_CURL_EXE OFF CACHE INTERNAL "")
set(BUILD_TESTING OFF CACHE INTERNAL "")
set(CURL_USE_LIBPSL OFF CACHE INTERNAL "")
set(CURL_STATICLIB ON CACHE INTERNAL "")

FetchContent_MakeAvailable(curl)

# 5. Build your Program
add_executable(WeatherApp hominy.cpp)

# 6. Windows-specific definitions
target_compile_definitions(WeatherApp PRIVATE _WIN32_WINNT=0x0A00)
target_compile_definitions(WeatherApp PRIVATE CURL_STATICLIB)

# 7. Link everything together
target_link_libraries(WeatherApp PRIVATE
        libcurl
        ws2_32
        mswsock
        crypt32
        normaliz
)

# 8. Tell Crow where to find asio.hpp
target_include_directories(WeatherApp PRIVATE ${asio_SOURCE_DIR}/asio/include)