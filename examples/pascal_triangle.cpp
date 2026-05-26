/**
 * Pascal's Triangle Example
 * 
 * This example demonstrates the use of BigInt to calculate and print
 * Pascal's Triangle. The values in the triangle grow exponentially,
 * quickly exceeding the capacity of standard 64-bit integers.
 */
#include <iostream>
#include <vector>
#include "../bigint.h"

using namespace BigInt;

// Calculates and prints Pascal's Triangle up to num_rows using bigint
void print_pascal_triangle(int num_rows) {
    std::vector<bigint> current_row;
    
    for (int i = 0; i < num_rows; ++i) {
        std::vector<bigint> next_row(i + 1);
        next_row[0] = 1;
        next_row[i] = 1;
        
        for (int j = 1; j < i; ++j) {
            next_row[j] = current_row[j - 1] + current_row[j];
        }
        
        current_row = std::move(next_row);
        
        // Print the row
        std::cout << "Row " << i << ": ";
        for (const auto& val : current_row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    int rows = 50;
    std::cout << "Calculating the first " << rows << " rows of Pascal's Triangle..." << std::endl;
    print_pascal_triangle(rows);
    return 0;
}
