#include <unity.h>

void test_sanity(void) {
    TEST_ASSERT_TRUE(true);
}

void setup() {
    UNITY_BEGIN();
    RUN_TEST(test_sanity);
    UNITY_END();
}

void loop() {}
