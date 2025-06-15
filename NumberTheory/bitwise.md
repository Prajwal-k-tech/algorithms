# Bitwise Operations & Tricks 🔢

A comprehensive guide to bitwise operators and their clever applications in competitive programming.

## Table of Contents
- [Basic Bitwise Operators](#basic-bitwise-operators)
- [Checking Properties](#checking-properties)
- [Bit Manipulation](#bit-manipulation)
- [Arithmetic Operations](#arithmetic-operations)
- [Advanced Tricks](#advanced-tricks)
- [Built-in Functions](#built-in-functions)
- [Common Patterns](#common-patterns)
- [Practice Problems](#practice-problems)

## Basic Bitwise Operators

| Operator | Name | Description | Example |
|----------|------|-------------|---------|
| `&` | AND | Both bits must be 1 | `5 & 3 = 1` (101 & 011 = 001) |
| `\|` | OR | At least one bit is 1 | `5 \| 3 = 7` (101 \| 011 = 111) |
| `^` | XOR | Bits are different | `5 ^ 3 = 6` (101 ^ 011 = 110) |
| `~` | NOT | Flip all bits | `~5 = -6` (inverts all bits) |
| `<<` | Left Shift | Shift bits left | `5 << 1 = 10` (multiply by 2) |
| `>>` | Right Shift | Shift bits right | `5 >> 1 = 2` (divide by 2) |

## Checking Properties

### 1. Even/Odd Check
```cpp
// Check if number is odd
if (x & 1) {
    cout << "Odd" << endl;
} else {
    cout << "Even" << endl;
}
```

### 2. Power of 2 Check
```cpp
// Method 1: Using bit manipulation
bool isPowerOf2(int x) {
    return x && !(x & (x - 1));
}

// Method 2: Alternative approach
bool isPowerOf2Alt(int x) {
    return x > 0 && (x & (x - 1)) == 0;
}

// Examples:
// 8 & 7 = 1000 & 0111 = 0000 ✓
// 6 & 5 = 0110 & 0101 = 0100 ✗
```

## Bit Manipulation

### Working with k-th Bit (0-indexed from right)

```cpp
// Check if k-th bit is set
bool isSet = x & (1 << k);

// Set k-th bit to 1
x |= (1 << k);

// Set k-th bit to 0 (clear)
x &= ~(1 << k);

// Toggle k-th bit
x ^= (1 << k);

// Get k-th bit value (0 or 1)
int kthBit = (x >> k) & 1;
```

### Examples
```cpp
int x = 5; // Binary: 101

// Check 2nd bit (from right, 0-indexed)
bool bit2 = x & (1 << 2); // 101 & 100 = 100 (true)

// Set 1st bit
x |= (1 << 1); // 101 | 010 = 111 (x becomes 7)

// Clear 0th bit
x &= ~(1 << 0); // 111 & 110 = 110 (x becomes 6)

// Toggle 3rd bit
x ^= (1 << 3); // 0110 ^ 1000 = 1110 (x becomes 14)
```

## Arithmetic Operations

### Fast Arithmetic Using Shifts
```cpp
// Multiply by 2^k
int result = x << k;

// Divide by 2^k (for positive numbers)
int result = x >> k;

// Modulo 2^k
int remainder = x & ((1 << k) - 1);

// Examples:
// 12 << 2 = 48    (12 * 4)
// 12 >> 2 = 3     (12 / 4)
// 12 & 7 = 4      (12 % 8, where 8 = 2^3)
```

## Advanced Tricks

### 1. Variable Swapping (without temp variable)
```cpp
// XOR swap
void swap(int &x, int &y) {
    x = x ^ y;
    y = x ^ y;  // y = (x^y) ^ y = x
    x = x ^ y;  // x = (x^y) ^ x = y
}

// One-liner version
void swapOneLine(int &x, int &y) {
    x ^= y ^= x ^= y;
}
```

### 2. Absolute Value (for integers)
```cpp
int abs_value(int x) {
    int mask = x >> 31;  // -1 if negative, 0 if positive
    return (x + mask) ^ mask;
}
```

### 3. Min/Max without conditionals
```cpp
int min(int x, int y) {
    return y ^ ((x ^ y) & -(x < y));
}

int max(int x, int y) {
    return x ^ ((x ^ y) & -(x < y));
}
```

### 4. Sign function
```cpp
int sign(int x) {
    return (x >> 31) | ((-x) >> 31);
}
// Returns: -1 if negative, 0 if zero, 1 if positive
```

## Built-in Functions

### GCC Built-ins
```cpp
int x = 12; // Binary: 1100

// Count number of set bits (1s)
int popcount = __builtin_popcount(x);  // Returns 2

// Count trailing zeros
int ctz = __builtin_ctz(x);  // Returns 2 (for 1100)

// Count leading zeros
int clz = __builtin_clz(x);  // Returns 28 (for 32-bit int)

// For long long
__builtin_popcountll(x);
__builtin_ctzll(x);
__builtin_clzll(x);
```

### C++20 bit functions
```cpp
#include <bit>

int x = 12;
std::popcount(x);      // Count set bits
std::countr_zero(x);   // Count trailing zeros  
std::countl_zero(x);   // Count leading zeros
std::bit_width(x);     // Minimum bits needed
```

## Common Patterns

### 1. Iterate through all subsets
```cpp
// Iterate through all subsets of mask
for (int subset = mask; subset > 0; subset = (subset - 1) & mask) {
    // Process subset
}
```

### 2. Check if subset
```cpp
bool isSubset(int subset, int set) {
    return (subset & set) == subset;
}
```

### 3. Remove lowest set bit
```cpp
int removeLowestBit(int x) {
    return x & (x - 1);
}
```

### 4. Get lowest set bit
```cpp
int getLowestBit(int x) {
    return x & (-x);
}
```

### 5. Set all bits in range [l, r]
```cpp
int setBitsInRange(int x, int l, int r) {
    int mask = ((1 << (r - l + 1)) - 1) << l;
    return x | mask;
}
```

## Useful Formulas

```cpp
// Number with k trailing ones: (1 << k) - 1
// Number with k leading ones: ~((1 << (32 - k)) - 1)
// Check if x is odd: x & 1
// Check if x is power of 2: x && !(x & (x-1))
// Round up to next power of 2: 1 << (int)ceil(log2(x))
// Isolate rightmost 1 bit: x & -x
// Turn off rightmost 1 bit: x & (x-1)
// Turn on rightmost 0 bit: x | (x+1)
```

## Practice Problems

### Easy
- Check if a number is power of 2
- Count set bits in a number
- Find the only non-repeating element (XOR all)

### Medium  
- Find two non-repeating elements
- Subset sum using bitmask
- Generate all subsets

### Hard
- Digit DP with bitmask
- Traveling Salesman Problem (TSP)
- Maximum subset XOR

## Performance Notes

- Bitwise operations are **extremely fast** (1 CPU cycle)
- Use shifts instead of multiplication/division by powers of 2
- XOR can be used for encryption (simple)
- Bit manipulation is often key in optimization problems

---

**Remember:** Practice these patterns regularly - they appear frequently in competitive programming! 🚀 