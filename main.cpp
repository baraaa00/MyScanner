#include "scanner.hpp"
#include <iostream>
#include <stdexcept>

int main() {
  try {
    lexicalAnalyze("test.txt");
  } catch (const std::runtime_error &e) {
    std::cerr << e.what() << "\n";
  }
  return 0;
}
