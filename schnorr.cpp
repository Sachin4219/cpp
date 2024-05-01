#include <iostream>
#include <cmath>
#include <string>

using namespace std;

long long calc_pow(int a, int n, int p) {
    long long ans = 1;
    for (int i = 0; i < 12; i++) {
        int bit = 1 << i;
        if (n & bit) {
            ans = (ans * a) % p;
        }
        a = (a * a) % p;
    }
    return ans;
}

int gcd(int a, int p, int &t1, int t2) {
    if (a == 0) {
        return p;
    }
    if (p == 0) {
        return a;
    }
    if (a < p) {
        int q = p / a;
        int r = p % a;
        int t = t1 - t2 * q;
        t1 = t2;
        return gcd(a, r, t1, t);
    } else {
        int q = a / p;
        int r = a % p;
        int t = t1 - t2 * q;
        t1 = t2;
        return gcd(r, p, t1, t);
    }
}

int findInverse(int a, int p) {
    a = (p + a % p) % p;
    int t1 = 0;
    gcd(a, p, t1, 1);
    t1 = (p + t1 % p) % p;
    return t1;
}

int main() {
    int p, q, e1, d;
    cout << "Enter p, q, e1, d: ";
    cin >> p >> q >> e1 >> d;

    int e2 = calc_pow(e1, d, p);
    int r;
    cout << "Enter r: ";
    cin >> r;

    cout << "Private key = (" << d << ")" << endl;
    cout << "Public Key = (" << e1 << ", " << e2 << ", " << p << ")" << endl;

    int s1 = calc_pow(e1, r, p);
    int m;
    cout << "Enter message: ";
    cin >> m;
    int s2 = (q + ((r + d * s1) % q)) % q;

    string v1 = to_string(m) + to_string(s1);
    cout << "S1 = " << v1 << endl;
    cout << "S2 = " << s2 << endl;

    string str1 = to_string(m);
    long long temp1 = calc_pow(e1, s2, p);
    long long temp2 = calc_pow(e2, s1, p);
    long long temp3 = findInverse(temp2, p);
    long long v2 = (temp1 * temp3) % p;
    string str2 = to_string(v2);
    string v2_str = str1 + str2;
    cout << "v1 = " << v1 << endl;
    cout << "v2 = " << v2_str << endl;

    if (v1 == v2_str) {
        cout << "Signature Verified" << endl;
    } else {
        cout << "Signature Not Verified" << endl;
    }

    return 0;
}
Enter p, q, e1, d: 2267 103 354 30
Enter r: 12
Private key = (30)
Public Key = (354, 1206, 2267)
Enter message: 23
S1 = 23854
S2 = 88
v1 = 23854
v2 = 23854
