cmake_minimum_required(VERSION 3.15.3)
project(munny)

set(CMAKE_CXX_STANDARD 17)

# Curl For People (python requests)
add_subdirectory(libs/cpr)
include_directories(${CPR_INCLUDE_DIRS})
#find_package(cpr CONFIG REQUIRED)

# nlohmann/json
add_subdirectory(libs/json)

set(LIBS ${CPR_LIBRARIES} nlohmann_json::nlohmann_json)

#set(SOURCES )

# When we start adding files we will create our own library out of them and
# all other files and just include this created lib to build our main file
# Since we have no files yet, I'm not compiling this
#add_library(munnylib STATIC ${SOURCES})
#target_link_libraries(munnylib PUBLIC ${LIBS})
#target_compile_options(munnylib PRIVATE -Werror -Wall -Wextra)

add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE ${LIBS})
target_compile_options(main PRIVATE -Werror -Wall -Wextra)
