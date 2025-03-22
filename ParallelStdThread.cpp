#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono;

#define THREAD_COUNT 4

void randomVector(int* vector, int size) {
  for (int i = 0; i < size; i++) {
    vector[i] = rand() % 100;
  }
}

void vectorAddition(int* v1, int* v2, int* v3, int start, int end) {
  for (int i = start; i < end; i++) {
    v3[i] = v1[i] + v2[i];
  }
}

int main() {
  unsigned long size = 100000000;
  srand(time(0));

  int *v1 = (int*)malloc(size * sizeof(int));
  int *v2 = (int*)malloc(size * sizeof(int));
  int *v3 = (int*)malloc(size * sizeof(int));

  randomVector(v1, size);
  randomVector(v2, size);

  auto start = high_resolution_clock::now();

  // Creating 4 threads for parallel addition
  thread t[THREAD_COUNT];
  int chunkSize = size / THREAD_COUNT;

  for (int i = 0; i < THREAD_COUNT; i++) {
    t[i] = thread(vectorAddition, v1, v2, v3, i * chunkSize, (i + 1) * chunkSize);
  }

  for (int i = 0; i < THREAD_COUNT; i++) {
    t[i].join();
  }

  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);

  cout << "Time taken by parallel function :" << duration.count() << " microseconds" << endl;

  free(v1);
  free(v2);
  free(v3);

  return 0;
}
