#include <iostream>
#include <chrono>

int Square(int x) {
    return x * x;
}

int main() {
    const int iterations = 10000;
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < iterations; ++i) {
        int result = Square(i);
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "Total execution time: " << duration << " microseconds" << std::endl;

    return 0;
}