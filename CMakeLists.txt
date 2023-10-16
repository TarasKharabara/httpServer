cmake_minimum_required(VERSION 3.5)

project(serverHTTP LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(serverHTTP src/main.cpp
    src/serverhttp.h src/serverhttp.cpp
    src/request.h src/request.cpp
    src/requestdispatcher.h src/requestdispatcher.cpp
)

include(GNUInstallDirs)
install(TARGETS serverHTTP
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
