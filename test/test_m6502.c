#include "unity.h"
#include "cpu.h"

cpu_t cpu;
mem_t mem;

void setUp(void)
{
    // Called before each test
    CPU_Reset(&cpu);
    MEM_Init(&mem);
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

void checkZNStatusFlags(int isFlagZShouldBeSet, int isFlagNShouldBeSet, cpu_t* cpuBefore)
{
    int isFlagZSet = cpu.cpu_status & FLAG_Z;
    int isFlagNSet = cpu.cpu_status & FLAG_N;

    if (isFlagZShouldBeSet)
        TEST_ASSERT_TRUE(isFlagZSet);
    else
        TEST_ASSERT_FALSE(isFlagZSet);

    if (isFlagNShouldBeSet)
        TEST_ASSERT_TRUE(isFlagNSet);
    else
        TEST_ASSERT_FALSE(isFlagNSet);
}

void test_CPU_LDAImmediateShouldLoadAValueIntoTheRegister(void)
{
    // Given:
    u32 cycles = 2;
    cpu_t cpuBefore = cpu;

    // START OF INS SET
    mem.data[0xFFFC] = INS_LDA_IM;
    mem.data[0xFFFD] = 0x84;        // 0x84 is a negative number (0b10000100)
    // END OF INS SET

    // When:
    s32 cyclesUsed = CPU_Exec(&cycles, &cpu, &mem);

    // Then:
    TEST_ASSERT_EQUAL_HEX8(0x84, cpu.a);
    TEST_ASSERT_EQUAL(2, cyclesUsed);
    checkZNStatusFlags(0, 1, &cpuBefore);
    // Checking status flags before and after executing instructions (FLAG_N should be set)
    TEST_ASSERT_EQUAL_HEX8(cpuBefore.cpu_status | FLAG_N, cpu.cpu_status);
}

void test_CPU_LDAZeroPageShouldLoadAValueIntoTheRegister(void)
{
    // Given:
    u32 cycles = 3;
    cpu_t cpuBefore = cpu;

    // START OF INS SET
    mem.data[0xFFFC] = INS_LDA_ZP;
    mem.data[0xFFFD] = 0x42;
    mem.data[0x0042] = 0x37;
    // END OF INS SET

    // When:
    s32 cyclesUsed = CPU_Exec(&cycles, &cpu, &mem);

    // Then:
    TEST_ASSERT_EQUAL_HEX8(0x37, cpu.a);
    TEST_ASSERT_EQUAL(3, cyclesUsed);
    checkZNStatusFlags(0, 0, &cpuBefore);
    // Checking status flags before and after executing instructions
    TEST_ASSERT_EQUAL_HEX8(cpuBefore.cpu_status, cpu.cpu_status);
}

void test_CPU_LDAZeroPageXShouldLoadAValueIntoTheRegister(void)
{
    // Given:
    u32 cycles = 4;
    cpu.x = 5;  // Offset
    cpu_t cpuBefore = cpu;

    // START OF INS SET
    mem.data[0xFFFC] = INS_LDA_ZPX;
    mem.data[0xFFFD] = 0x42;
    mem.data[0x0047] = 0x37;
    // END OF INS SET

    // When:
    s32 cyclesUsed = CPU_Exec(&cycles, &cpu, &mem);

    // Then:
    TEST_ASSERT_EQUAL_HEX8(0x37, cpu.a);
    TEST_ASSERT_EQUAL(4, cyclesUsed);
    checkZNStatusFlags(0, 0, &cpuBefore);
    // Checking status flags before and after executing instructions
    TEST_ASSERT_EQUAL_HEX8(cpuBefore.cpu_status, cpu.cpu_status);
}

void test_CPU_LDAZeroPageXShouldLoadAValueIntoTheRegisterWhenItWraps(void)
{
    // Given:
    u32 cycles = 4;
    cpu.x = 0xFF;  // Offset
    cpu_t cpuBefore = cpu;

    // START OF INS SET
    mem.data[0xFFFC] = INS_LDA_ZPX;
    mem.data[0xFFFD] = 0x80;
    mem.data[0x007F] = 0x37;
    // END OF INS SET

    // When:
    s32 cyclesUsed = CPU_Exec(&cycles, &cpu, &mem);

    // Then:
    TEST_ASSERT_EQUAL_HEX8(0x37, cpu.a);
    TEST_ASSERT_EQUAL(4, cyclesUsed);
    checkZNStatusFlags(0, 0, &cpuBefore);
    // Checking status flags before and after executing instructions
    TEST_ASSERT_EQUAL_HEX8(cpuBefore.cpu_status, cpu.cpu_status);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_CPU_ShouldResetCorrectly);
    RUN_TEST(test_CPU_LDAImmediateShouldLoadAValueIntoTheRegister);
    RUN_TEST(test_CPU_LDAZeroPageShouldLoadAValueIntoTheRegister);
    RUN_TEST(test_CPU_LDAZeroPageXShouldLoadAValueIntoTheRegister);
    RUN_TEST(test_CPU_LDAZeroPageXShouldLoadAValueIntoTheRegisterWhenItWraps);

    return UNITY_END();
}