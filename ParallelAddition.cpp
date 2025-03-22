#include <chrono>
#include <cstdlib>
#include <iostream>
#include <time.h>

using namespace std::chrono;
using namespace std;

// Function to fill the vector with random numbers
void randomVector(int vector[], int size) {
  for (int i = 0; i < size; i++) {
    vector[i] = rand() % 100;
  }
}

int main() {
  unsigned long size = 100000000;
  srand(time(0));

  // Allocate memory for the vectors
  int *v1, *v2, *v3;
  v1 = (int *)malloc(size * sizeof(int));
  v2 = (int *)malloc(size * sizeof(int));
  v3 = (int *)malloc(size * sizeof(int));

  // Generate random values for the vectors
  randomVector(v1, size);
  randomVector(v2, size);

  // Start measuring execution time
  auto start = high_resolution_clock::now();

  // Perform vector addition
  for (int i = 0; i < size; i++) {
    v3[i] = v1[i] + v2[i];
  }

  // Stop measuring execution time
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);

  // Display execution time
  cout << "Time taken by function :" << duration.count() << " microseconds" << endl;

  return 0;
}
