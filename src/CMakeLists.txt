cmake_minimum_required(VERSION 3.16)

project(mos-6502-emulator LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(mos-6502-emulator main.c cpu.c cpu.h typedefs.h)

include(GNUInstallDirs)
install(TARGETS mos-6502-emulator
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
