#include <iostream>

bool isPrime(long long n) {
    if (n < 2) return false;
    for (long long divisor = 2; divisor <= n / divisor; ++divisor) {
        if (n % divisor == 0) return false;
    }
    return true;
}

int main() {
    long long number;
    if (!(std::cin >> number)) return 1;
    std::cout << (isPrime(number) ? "Prime\n" : "Not prime\n");
}
