#pragma once
#define TEST_MODE
#ifdef TEST_MODE
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#endif