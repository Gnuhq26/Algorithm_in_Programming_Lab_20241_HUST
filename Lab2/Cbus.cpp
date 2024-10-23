#include<bits/stdc++.h>
using namespace std;

int n, K;
int load; // đếm số khách hiện tại trên xe
int f_best = INT_MAX; // chi phí tốt nhất ban đầu gán giá trị vô cùng lớn
int f; // chi phí hiện tại
int cmin = INT_MAX; // đường đi ngắn nhất
bool appear[100]; // mảng đánh dấu điểm đã thăm (true = đã thăm)
int x[100]; // mảng lưu lộ trình
int A[100][100]; // ma trận khoảng cách

bool check(int k, int v) {
    if (appear[v] == true) return false; // nếu điểm đã được thăm
    if (v > n && load == 0) return false; // nếu điểm trả khách v > n mà không có khách
    if (v <= n && load >= K) return false; // nếu là điểm đón khách v <= n mà xe đã đầy
    if (v > n && appear[v - n]==false) return false; // nếu là điểm trả khách nhưng chưa đón khách tương ứng
    return true;
}

void Try(int k) {
    for (int v = 1; v <= 2 * n; v++) {
        if (check(k, v)) {
            x[k] = v;
            f += A[x[k - 1]][x[k]]; // cộng chi phí đường đi
            appear[v] = true; // đánh dấu đã thăm

            if (v <= n) load++; // nếu đón khách
            else load--; // nếu trả khách

            if (k == 2 * n) {
                f_best = min(f_best, f + A[x[k]][0]); // nếu đi hết các điểm, cập nhật chi phí tốt nhất
            } else {
                if (f + (2 * n -k+1) * cmin < f_best) Try(k + 1);
            }

            // Quay lui
            f -= A[x[k - 1]][x[k]]; // trừ chi phí đường đi
            if (v <= n) load -= 1;
            else load += 1;
            appear[v] = false; // đánh dấu chưa thăm lại
        }
    }
}

int main() {
    cin >> n >> K;
    for (int i = 0; i <= 2 * n; i++) {
        for (int j = 0; j <= 2 * n; j++) {
            cin >> A[i][j];
            if (i != j && A[i][j] < cmin) // tìm cmin là khoảng cách nhỏ nhất không bằng 0
                cmin = A[i][j];
        }
    }
    x[0] = 0;
    load = 0;
    memset(appear, false, sizeof(appear)); // đánh dấu tất cả điểm chưa thăm

    Try(1);
    cout << f_best;
}
