#include<bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    vector<int> bits;

    for (int i = 0; i < n; i++) {
        for (int k = 31; k >= 0; k--) {
            int bit = arr[i] & (1<<k);
            if (bit) {
                if ((int) bits.size() == 0 || bits.back() != k) {
                    bits.push_back(k);
                }
            }
        }
    }

    for (auto &x : bits) {
        cout << x << " ";
    }

    int len = 1;
    int max = 1;
    int mindx = 0;
    for (int i = 1; i < (int) bits.size(); i++) {
        if (bits[i] > bits[i - 1]) {
            len += 1;
        } else {
            if (max < len) {
                max = len;
                mindx = i - max;
            }
            len = 1;
        }
    }
    if (max < len) {
        max = len;
        mindx = (int) bits.size() - max;
    }
    int l = bits[mindx];
    int r = bits[max + mindx - 1];
    int maxbit = *max_element(bits.begin(), bits.end());

    cout << "\nL : " << l << " r:" << r;

    int x = 0;
    for (int i = 0; i < l; i++) {
        x = x | (1>>i);
    }
    for (int i = maxbit; i > r; i--) {
        x = x | (1<<i);
    }

    cout << "\nx: " << x;

    vector<int> newarr;
    int answer=0;
    for (int i = 0; i < (int)bits.size(); i++) {
        newarr.push_back(bits[i] ^ x);
    }

    // iterate left and right check max

    cout << "\nanswer: " << answer;



    return 0;
}