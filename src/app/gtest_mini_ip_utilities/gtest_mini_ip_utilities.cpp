
#include <gtest/gtest.h>
/**
 * @brief Main function for getests
 * 
 * @param argc 
 * @param argv 
 * @return int returns 0 on success.
 */
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);


  return RUN_ALL_TESTS();
}
