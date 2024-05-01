#include<bits/stdc++.h>
using namespace std;

// Function to calculate the Greatest Common Divisor (GCD) using Euclid's Algorithm
long gcd(long a, long b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Function to calculate modular inverse using extended Euclidean algorithm
long modInverse(long a, long m) {
    long m0 = m;
    long y = 0, x = 1;

    if (m == 1)
        return 0;

    while (a > 1) {
        long q = a / m;
        long t = m;

        m = a % m;
        a = t;
        t = y;

        y = x - q * y;
        x = t;
    }

    if (x < 0)
        x += m0;

    return x;
}

long powerModulo(long base, long exponent, long mod) {
    if (exponent == 0)
        return 1;
    long result = 1;
    while (exponent > 0) {
        if (exponent % 2 == 1) // If exponent is odd
            result = (result * base) % mod;
        base = (base * base) % mod;
        exponent /= 2;
    }
    return result;
}

// Function to generate keys
void generateKeys(long &p, long &g, long &x, long &y) {
    // Randomly choose a prime number
    srand(time(NULL));
    // Example range [100, 200]
    while (true) {
        bool isPrime = true;
        for (long i = 2; i <= sqrt(p); ++i) {
            if (p % i == 0) {
                isPrime = false;
                break;
            }
        }
        if (isPrime)
            break;
        else
            p = rand() % 100 + 100;
    }

    // Randomly choose a generator
    g = rand() % (p - 2) + 2;

    // Choose a private key x
    x = rand() % (p - 1) + 1;

    // Calculate public key y
    y = powerModulo(g, x, p);
}


// Function to sign a message
pair<long, long> sign(long message, long p, long g, long x) {
    long k = rand() % (p - 1) + 1; // Choose a random k
    long r = powerModulo(g, k, p);
    long s = (modInverse(k, p - 1) * (message - x * r)) % (p - 1);
    if (s < 0)
        s += (p - 1);
    return make_pair(r, s);
}

// Function to verify the signature
bool verify(long message, pair<long, long> signature, long p, long g, long y) {
    long r = signature.first;
    long s = signature.second;
    if (r < 1 || r > p - 1 || s < 1 || s > p - 1)
        return false;

    long left = powerModulo(y, r, p) * powerModulo(r, s, p) % p;
    long right = powerModulo(g, message, p);
    return left == right;
}

int main() {
    long p, g, x, y;
    cin>>p;
    generateKeys(p, g, x, y);
    

    long message = 123; // Example message to sign
    pair<long, long> signature = sign(message, p, g, x);
    cout << "Signature (S1, S2): (" << signature.first << ", " << signature.second << ")" << endl;

    bool isValid = verify(message, signature, p, g, y);
    if (isValid)
        cout << "Signature is valid." << endl;
    else
        cout << "Signature is not valid." << endl;

    return 0;
}
