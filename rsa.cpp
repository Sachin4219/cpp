#include <bits/stdc++.h>
using namespace std;

// Function to calculate the Greatest Common Divisor (GCD) using Euclid's Algorithm
long gcd(long a, long b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Function to generate keys
void generateKeys(long p, long q, long &n, long &e, long &d) {
    n = p * q;
    long phi = (p - 1) * (q - 1);

    // Choose e such that e and phi(n) are coprime
    for (e = 2; e < phi; e++) {
        if (gcd(e, phi) == 1)
            break;
    }

    // Calculate d
    for (d = 2; d < phi; d++) {
        if ((d * e) % phi == 1)
            break;
    }
}

// Function to calculate the power modulo
long powerModulo(long base, long exponent, long mod) {
    if (exponent == 0)
        return 1;
    long long result = 1;
    while (exponent > 0) {
        if (exponent % 2 == 1) // If exponent is odd
            result = (result * base) % mod;
        base = (base * base) % mod;
        exponent /= 2;
    }
    return result;
}

// Function to sign a message
long sign(long message, long d, long n) {
    return powerModulo(message, d, n);
}

// Function to verify the signature
bool verify(long message, long signature, long e, long n) {
    long decrypted = powerModulo(signature, e, n);
    return decrypted == message;
}

int main() {
    // Example prime numbers
    long p = 61, q = 53;
    long n, e, d;
    generateKeys(p, q, n, e, d);

    long message = 123; // Example message to sign
    long signature = sign(message, d, n);
    cout<<"Message: "<< message << endl;
    cout << "Signature: " << signature << endl;

    bool isValid = verify(message, signature, e, n);
    if (isValid)
        cout << "Signature is valid." << endl;
    else
        cout << "Signature is not valid." << endl;

    return 0;
}
// 823 953 313
