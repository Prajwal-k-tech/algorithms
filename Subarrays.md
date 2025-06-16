# Subarrays in Competitive Programming

## Table of Contents
- [Introduction](#introduction)
- [Types of Subarrays](#types-of-subarrays)
- [Generation Techniques](#generation-techniques)
- [Common Algorithms](#common-algorithms)
- [Time Complexities](#time-complexities)
- [Practice Problems](#practice-problems)

## Introduction

A **subarray** is a contiguous sequence of elements within an array. For an array of size `n`, there are `n(n+1)/2` possible subarrays. Understanding different ways to work with subarrays is crucial for solving many competitive programming problems.

**Key Difference:**
- **Subarray**: Contiguous elements (e.g., [2,3,4] from [1,2,3,4,5])
- **Subsequence**: Non-contiguous elements maintaining order (e.g., [1,3,5] from [1,2,3,4,5])

## Types of Subarrays

### 1. All Possible Subarrays
Generate every contiguous subarray of an array.

```cpp
void generateAllSubarrays(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            // Subarray from index i to j
            cout << "Subarray [" << i << ", " << j << "]: ";
            for (int k = i; k <= j; k++) {
                cout << arr[k] << " ";
            }
            cout << endl;
        }
    }
}
```

### 2. Fixed Size Subarrays (Sliding Window)
Get all subarrays of a specific size.

```cpp
vector<vector<int>> getFixedSizeSubarrays(vector<int>& arr, int k) {
    vector<vector<int>> result;
    int n = arr.size();
    
    for (int i = 0; i <= n - k; i++) {
        vector<int> subarray;
        for (int j = i; j < i + k; j++) {
            subarray.push_back(arr[j]);
        }
        result.push_back(subarray);
    }
    return result;
}
```

## Generation Techniques

### 1. Brute Force Approach
**Time Complexity:** O(n³)
```cpp
// Generate and process all subarrays
for (int i = 0; i < n; i++) {
    for (int j = i; j < n; j++) {
        // Process subarray arr[i...j]
        for (int k = i; k <= j; k++) {
            // Do something with arr[k]
        }
    }
}
```

### 2. Optimized Generation
**Time Complexity:** O(n²)
```cpp
// Build subarray incrementally
for (int i = 0; i < n; i++) {
    vector<int> current;
    for (int j = i; j < n; j++) {
        current.push_back(arr[j]);
        // Process current subarray arr[i...j]
        processSubarray(current);
    }
}
```

### 3. Using STL Iterators
```cpp
vector<int> getSubarray(vector<int>& arr, int start, int end) {
    return vector<int>(arr.begin() + start, arr.begin() + end + 1);
}
```

## Common Algorithms

### 1. Maximum Subarray Sum (Kadane's Algorithm)
```cpp
long long maxSubarraySum(vector<int>& arr) {
    long long maxSoFar = arr[0];
    long long maxEndingHere = arr[0];
    
    for (int i = 1; i < arr.size(); i++) {
        maxEndingHere = max((long long)arr[i], maxEndingHere + arr[i]);
        maxSoFar = max(maxSoFar, maxEndingHere);
    }
    return maxSoFar;
}
```

### 2. Subarray with Given Sum
```cpp
vector<int> findSubarrayWithSum(vector<int>& arr, int targetSum) {
    int left = 0, currentSum = 0;
    
    for (int right = 0; right < arr.size(); right++) {
        currentSum += arr[right];
        
        while (currentSum > targetSum && left <= right) {
            currentSum -= arr[left];
            left++;
        }
        
        if (currentSum == targetSum) {
            return vector<int>(arr.begin() + left, arr.begin() + right + 1);
        }
    }
    return {}; // Not found
}
```

### 3. Sliding Window Maximum
```cpp
vector<int> slidingWindowMaximum(vector<int>& arr, int k) {
    deque<int> dq; // Store indices
    vector<int> result;
    
    for (int i = 0; i < arr.size(); i++) {
        // Remove elements outside current window
        while (!dq.empty() && dq.front() <= i - k) {
            dq.pop_front();
        }
        
        // Remove smaller elements from back
        while (!dq.empty() && arr[dq.back()] <= arr[i]) {
            dq.pop_back();
        }
        
        dq.push_back(i);
        
        // Add to result if window is complete
        if (i >= k - 1) {
            result.push_back(arr[dq.front()]);
        }
    }
    return result;
}
```

### 4. Prefix Sum for Range Queries
```cpp
class PrefixSum {
private:
    vector<long long> prefix;
    
public:
    PrefixSum(vector<int>& arr) {
        int n = arr.size();
        prefix.resize(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + arr[i];
        }
    }
    
    long long rangeSum(int left, int right) {
        return prefix[right + 1] - prefix[left];
    }
};
```

### 5. Two Pointers Technique
```cpp
int countSubarraysWithSumLessK(vector<int>& arr, int k) {
    int left = 0, count = 0;
    long long sum = 0;
    
    for (int right = 0; right < arr.size(); right++) {
        sum += arr[right];
        
        while (sum >= k && left <= right) {
            sum -= arr[left];
            left++;
        }
        
        // All subarrays ending at 'right' and starting from 'left' to 'right'
        count += (right - left + 1);
    }
    return count;
}
```

## Time Complexities

| Operation | Time Complexity | Space Complexity |
|-----------|----------------|------------------|
| Generate all subarrays | O(n³) | O(1) |
| Generate all subarrays (optimized) | O(n²) | O(k) where k is max subarray size |
| Kadane's Algorithm | O(n) | O(1) |
| Two Pointers | O(n) | O(1) |
| Sliding Window | O(n) | O(k) where k is window size |
| Prefix Sum (preprocessing) | O(n) | O(n) |
| Range Query (after preprocessing) | O(1) | - |

## Advanced Techniques

### 1. Subarray XOR Problems
```cpp
int countSubarraysWithXorK(vector<int>& arr, int k) {
    unordered_map<int, int> prefixXor;
    int xorSum = 0, count = 0;
    prefixXor[0] = 1; // Empty subarray
    
    for (int num : arr) {
        xorSum ^= num;
        if (prefixXor.find(xorSum ^ k) != prefixXor.end()) {
            count += prefixXor[xorSum ^ k];
        }
        prefixXor[xorSum]++;
    }
    return count;
}
```

### 2. Subarray with Equal 0s and 1s
```cpp
int findMaxLengthEqualZeroOne(vector<int>& nums) {
    unordered_map<int, int> sumToIndex;
    sumToIndex[0] = -1; // Base case
    int maxLen = 0, sum = 0;
    
    for (int i = 0; i < nums.size(); i++) {
        sum += (nums[i] == 1) ? 1 : -1;
        
        if (sumToIndex.find(sum) != sumToIndex.end()) {
            maxLen = max(maxLen, i - sumToIndex[sum]);
        } else {
            sumToIndex[sum] = i;
        }
    }
    return maxLen;
}
```

## Practice Problems

### Easy
- **Maximum Subarray** (Kadane's Algorithm)
- **Subarray Sum Equals K**
- **Find All Subarrays with Given Sum**

### Medium
- **Sliding Window Maximum**
- **Subarray Product Less Than K**
- **Continuous Subarray Sum**
- **Maximum Size Subarray Sum Equals k**

### Hard
- **Shortest Subarray with Sum at Least K**
- **Subarrays with K Different Integers**
- **Count of Subarrays with XOR Equal to K**

## Tips for Competitive Programming

1. **Choose the Right Approach:**
   - Use brute force only when n ≤ 100
   - Prefer O(n) or O(n log n) solutions for larger inputs

2. **Common Patterns:**
   - **Prefix Sum**: For range sum queries
   - **Two Pointers**: For sum-based problems
   - **Sliding Window**: For fixed-size or optimization problems
   - **HashMap**: For counting/frequency problems

3. **Edge Cases:**
   - Empty arrays
   - Single element arrays
   - All negative numbers
   - Integer overflow (use long long)

4. **Optimization Tricks:**
   - Use prefix sums to avoid recalculating sums
   - Use deque for sliding window maximum/minimum
   - Use hash maps for O(1) lookups

## Code Template

```cpp
#include <bits/stdc++.h>
using namespace std;

class SubarrayHelper {
public:
    // Generate all subarrays
    static void generateAll(vector<int>& arr) {
        int n = arr.size();
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                // Process subarray arr[i...j]
            }
        }
    }
    
    // Kadane's algorithm
    static long long maxSum(vector<int>& arr) {
        long long maxSoFar = arr[0], maxEndingHere = arr[0];
        for (int i = 1; i < arr.size(); i++) {
            maxEndingHere = max((long long)arr[i], maxEndingHere + arr[i]);
            maxSoFar = max(maxSoFar, maxEndingHere);
        }
        return maxSoFar;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    // Your code here
    
    return 0;
}
```

---

**Remember:** The key to mastering subarrays is understanding when to use each technique based on the problem constraints and requirements.
