add_library(mos-6502-emulator-lib STATIC
    cpu.c
    cpu.h
    typedefs.h
)

add_executable(mos-6502-emulator main.c)

target_link_libraries(mos-6502-emulator PRIVATE mos-6502-emulator-lib)

include(GNUInstallDirs)
install(TARGETS mos-6502-emulator
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
