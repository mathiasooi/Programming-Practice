#include <iostream>
#include <bitset>

using namespace std;

int main() {
    freopen("sample.out", "w", stdout);
    freopen("sample.in","r", stdin);
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    bitset<9000000> phonenumbers;

    cin >> n;
    while (n--) {
        int t; cin >> t;
        phonenumbers[t-1000000] = 1;
    }

    for (int i = 0; i < 9000000; ++i) {
        if (phonenumbers[i]) cout << i + 1000000 << '\n';
    }
}