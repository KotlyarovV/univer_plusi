#include <iostream>
#include <vector>

using namespace std;

void division(vector<int>& v, int left, int right, int &t) {
    int x = v[left];
    int tmp = 0;
    t = left;
    for (int i = left + 1; i <= right; i++) {
        if (v[i] < x) {
            t++;
            tmp = v[t];
            v[t] = v[i];
            v[i] = tmp;
        }
    }
    tmp = v[left];
    v[left] = v[t];
    v[t] = tmp;
}

void quick_sort(vector<int>& v, int left, int right) {
    if (left < right) {
        int t = 0;
        division(v, left, right, t);
        quick_sort(v, left, t);
        quick_sort(v, t + 1, right);
    }
}



int main() {
    vector<int> v = {2, 1, 6, 6, 20, 1, -1, 4, 2, 83, 2, 1, 1, 1, 3233};
    int size = v.size() - 1;
    quick_sort(v, 0, size);
    for (auto i : v)
        cout << i << " ";
    return 0;
}