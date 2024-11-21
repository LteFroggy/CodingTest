#include <algorithm>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <queue>


using namespace std;

/*
    경주로 부지는 N x N사이즈의 정사각형.
    각 격자는 1x1 크기이다.
    각 격자의 칸은 0혹은 1로 채워져있다. 0은 빈칸, 1은 벽이다
    1인 칸에는 접근이 불가능함.
    
    항상 출발점은 0,0이고, 도착은 N-1, N-1이다.
    
    무사히 도착 가능하고, 끊기지 않도록 경주로를 건설해야 한다.
    벽이 있으면 건설이 불가능하다.
    
    직선 도로와 코너가 있는데, 직선 도로 하나는 100원, 코너는 500원이다.
    최소 비용을 계산해보자.
    
    당연히 완탐 해야 할듯?? N은 최대 25니까, 25^2 = 개의 칸이 있다.
    DP처럼 해보자. 어느 칸까지 가는데 최소비용을 항상 계산한다.
*/
int dy[4] = {-1, 1, 0, 0};
int dx[4] = {0, 0, -1, 1};

class state {
public:
    int y;
    int x;
    int cost;
    int direction;
    
    state(int a, int b, int c, int d) : y(a), x(b), cost(c), direction(d) {};
};

// 보드판 내의 값인지 확인하는 함수
inline bool inboard_check(int N, int y, int x) {
    return y >= 0 && y < N && x >= 0 && x < N;
}

// 탐색을 위한 구조체
struct cmp {
  bool operator()(state a, state b) {
      return a.cost < b.cost;
  }
};

int solution(vector<vector<int>> board) {
    
    // 각 점마다의 방향별 최소값을 저장할 것. 시작값은 항상 0,0이므로 0으로 처리한다.
    vector<vector<vector<int>>> dp(board.size(), vector<vector<int>>(board.size(), vector<int>(4, 1000000)));
    dp[0][0][0] = 0;
    dp[0][0][1] = 0;
    dp[0][0][2] = 0;
    dp[0][0][3] = 0;
    
    // 비용이 적은 친구부터 탐색하기 위한 pq;
    priority_queue<state, vector<state>, cmp> pq;
    
    // 첫 위치부터 탐색을 시작시키기 위해 priority_queue에 값을 넣어준다
    // 처음엔 어디로 가도 커브가 아니므로, 방향은 -1로 넣어준다.
    pq.push(state(0, 0, 0, -1));
    
    // 탐색 진행한다.
    while (!pq.empty()) {
        // 지금 값을 꺼낸다.
        state now = pq.top();
        int y = now.y;
        int x = now.x;
        int cost = now.cost;
        int dir = now.direction;
        pq.pop();
        
        // 현재 위치에서 상하좌우로 움직여본다.
        for (int k = 0; k < 4; k++) {
            int y_ = y + dy[k];
            int x_ = x + dx[k];
            int cost_next;
            
            // 보드판 밖의 값이면 가보지 않는다.
            if (!inboard_check(board.size(), y_, x_)) continue;
            
            // 지금 가려는 방향이 원래 온 방향인지 확인 후 비용 체크
            if (dir == -1 || dir == k) cost_next = cost + 100;
            else cost_next = cost + 600;

            // 목적지가 벽이거나, 이미 더 저렴한 비용으로 갈 수 있는 곳이라면 가지 않는다.
            if (board[y_][x_] == 1 || dp[y_][x_][k] < cost_next) continue;

            // 전부 해당하지 않는다면, 가본다.
            dp[y_][x_][k] = cost_next;
            // 갈 때, 얘가 사방으로 움직임을 가정하고 최소값을 갱신해준다
            for (int m = 0; m < 4; m++) {
                if (k == m) continue;
                if (dp[y_][x_][m] > cost_next + 500) dp[y_][x_][m] = cost_next + 500;
            }
            pq.push(state(y_, x_, cost_next, k));
        }
    }
    
    // 모든 경우를 체크했다면, dp[n][n]중 가장 작은 값을 반환한다
    int min_val = 1e9;
    for (auto v : dp[board.size() - 1][board.size() - 1]) {
        min_val = min(min_val, v);
    }
    return min_val;
}