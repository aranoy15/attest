#include <iostream>
#include <cstdio>
#include <ctime>

int main() {
    std::clock_t start;
    int duration;

    start = std::clock();

    /* Your algorithm here */

    for (;;) {

      duration = static_cast<int>((std::clock() - start) / CLOCKS_PER_SEC);
      
      std::cout << duration << " secs" << std::endl;
      std::cout << "Test: " << (duration >= 3 ? "yes" : "no") << std::endl;
    }
}