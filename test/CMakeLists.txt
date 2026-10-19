add_executable(run_tests
    test_m6502.c
    ../unity/unity.c
)

target_include_directories(run_tests PRIVATE
    ../unity
    ../src
)

target_link_libraries(run_tests PRIVATE mos-6502-emulator-lib)

add_test(NAME EmulatorTests COMMAND run_tests)
