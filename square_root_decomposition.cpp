#include <bits/stdc++.h>
using namespace std;
#define int long long

vector<int> arr;        // input array
vector<int> blockSums;  // sum of each block
int sz, blockSize, numBlocks;

// initialize block sums
void build(int n) {
    sz = n;
    blockSize = sqrtl(sz) + 1;                      // Block size ~ sqrt(n)
    numBlocks = (sz + blockSize - 1) / blockSize;  // Ceiling of n/blockSize
    blockSums.assign(numBlocks, 0);

    // block sums
    for (int i = 0; i < sz; i++) {
        blockSums[i / blockSize] += arr[i];
    }
}

// update element at index i to value
void update(int i, int value) {
    if (i < 0 || i >= sz) return;
    int blockIdx = i / blockSize;
    blockSums[blockIdx] += value - arr[i];  // update block sum
    arr[i] = value;                         // update array
}

// sum in range [l, r] (inclusive)
int query(int l, int r) {
    if (l < 0 || r >= sz || l > r) return 0;
    int sum = 0;

    // elements until we reach a full block or the end
    int i = l;
    while (i <= r && i % blockSize != 0 && i / blockSize == l / blockSize) {
        sum += arr[i];
        i++;
    }

    // complete blocks
    while (i + blockSize - 1 <= r) {
        sum += blockSums[i / blockSize];
        i += blockSize;
    }

    // remaining elements in the last partial block
    while (i <= r) {
        sum += arr[i];
        i++;
    }

    return sum;
}
