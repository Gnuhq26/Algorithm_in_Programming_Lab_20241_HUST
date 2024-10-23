#include<bits/stdc++.h>

using namespace std;

int M, N;
int C[50]; //mang ds mon hoc
int assignment[50]; //mang luu giao vien duoc phan cong cho moi mon
vector<vector<int>> canTeach; //ds so mon hoc gv co the day
vector<vector<int>> conflic; //ds mon hoc xung dot
int TLoad[50]; // luu so mon hoc cua moi gv
int TLoadMax = 0;
int minimum = 1000000;

void input() {
    int k;
    cin >> M >> N;
    canTeach.resize(M);
    for(int i=0 ; i<M ; i++) {
        cin >> k;
        for(int j=0 ; j<k ; j++) {
            int x; cin >> x;
            canTeach[i].push_back(x);
        }
    }
    cin >> k;
    conflic.resize(N+1);
    for(int i=0 ; i<k ; i++) {
        int c1, c2;
        cin >> c1 >> c2;
        conflic[c1].push_back(c2);
        conflic[c2].push_back(c1);
    }
}

bool check(int course, int i) {
    if(find(canTeach[i].begin(), canTeach[i].end(), course) == canTeach[i].end()) return false;
    for(int j=0 ; j<conflic[course].size() ; j++) {
        int conflicCourse = conflic[course].at(j);
        if( C[conflicCourse] == i && conflicCourse < course) return false;
    }
    return true;
}

void solution() {
    minimum = min(minimum, TLoadMax);
}

void Try(int course) {
    for(int v=0 ; v<M ; v++) {
        if(check(course,v)) {
            C[course] = v;
            TLoad[v]++;
            int pre = TLoadMax;
            TLoadMax = max(TLoadMax, TLoad[v]);

            if(course == N) solution();
            else{
                if(TLoadMax < minimum) Try(course + 1);
            }
            TLoad[v]--;
            TLoadMax = pre;
        }
    }
}

int main() {
    input();
    Try(1);
    cout << minimum;
    return 0;
}
