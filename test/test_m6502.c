#include "unity.h"
#include "cpu.h"

cpu_t cpu;

void setUp(void)
{
    // Called before each test
    CPU_Reset(&cpu);
}

void tearDown(void)
{
    // Called after each test
}

void test_CPU_ShouldResetCorrectly(void)
{
    // Testing SP and PC
    TEST_ASSERT_EQUAL_HEX16(VEC_RESET, cpu.pc);
    TEST_ASSERT_EQUAL_HEX16(VEC_ZEROPG, cpu.sp);
    // Testing flags
    TEST_ASSERT_FALSE   (cpu.cpu_status & FLAG_C);
    TEST_ASSERT_FALSE   (cpu.cpu_status & FLAG_Z);
    TEST_ASSERT_TRUE    (cpu.cpu_status & FLAG_I);
    TEST_ASSERT_FALSE   (cpu.cpu_status & FLAG_D);
    TEST_ASSERT_FALSE   (cpu.cpu_status & FLAG_B);
    TEST_ASSERT_FALSE   (cpu.cpu_status & FLAG_V);
    TEST_ASSERT_FALSE   (cpu.cpu_status & FLAG_N);
    // Testing registers
    TEST_ASSERT_EQUAL_HEX8(0x00, cpu.a);
    TEST_ASSERT_EQUAL_HEX8(0x00, cpu.x);
    TEST_ASSERT_EQUAL_HEX8(0x00, cpu.y);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_CPU_ShouldResetCorrectly);

    return UNITY_END();
}