#include <queue>
#include <string>
#include <vector>

using namespace std;

/*
    리코쳇 로봇이라는 게임이 있다.
    
    격자모양 보드판 위에서 말을 움직이는 게임으로, 시작에서 출발해서 목표에 멈추기 위해 몇 번의 이동이 필요한지 말한다.
    끝까지 쭉 이동하는 게임임.
    
    몇 번 이동해야 할지 찾아보자.
    
    DP느낌으로 각 위치에 멈췄을 때의 최소 이동 횟수들을 저장해보자.
*/

int solution(vector<string> board) {
    int answer = 0;
    
    
    // 초기 값은 최대로 잡아둔다.
    vector<vector<int>> dp(board.size(), vector<int>(board[0].size(), 1e9));
    
    // 보드에서 시작 위치 찾기
    int startY;
    int startX;
    int targetY;
    int targetX;
    
    int endFlag = false;
    
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[0].size(); j++) {
            if (board[i][j] == 'R') {
                startY = i;
                startX = j;
                
                // 루프 종료 조건 확인
                if (endFlag) break;
                endFlag = !endFlag;
            }
            
            else if (board[i][j] == 'G') {
                targetY = i;
                targetX = j;
                
                if (endFlag) break;
                endFlag = !endFlag;
            }
        }
    }
    
    int dy[] = {-1, 1, 0, 0};
    int dx[] = {0, 0, -1, 1};
    
    // 시작 위치 0으로 시작
    dp[startY][startX] = 0;
    queue<vector<int>> que;
    que.push({startY, startX});
    
    while (!que.empty()) {
        // 현재 위치와 이동 횟수 확인
        int yLoc = que.front()[0];
        int xLoc = que.front()[1];
        que.pop();
        
        int cost = dp[yLoc][xLoc];
        
        // 상하좌우 이동하기
        for (int k = 0; k < 4; k++) {
            int y_ = yLoc;
            int x_ = xLoc;
            
            // 어디까지 갈 수 있는지 확인.
            while (true) {
                int newY = y_ + dy[k];
                int newX = x_ + dx[k];
                
                // 보드 밖으로 가면, 그만 이동
                if (newY < 0 || newY >= board.size() || newX < 0 || newX >= board[0].size()) {
                    break;
                }
                
                // 이제 벽이면, 그만 이동
                else if (board[newY][newX] == 'D') {
                    break;
                }
                
                // 이동 가능하면, 계속 이동
                y_ = newY;
                x_ = newX;
            }
            
            // 이동 다 했으면, dp값과 비교하여 갱신
            if (dp[y_][x_] > cost + 1) {
                dp[y_][x_] = cost + 1;
                que.push({y_, x_});
            }
        }
    }
    
    // 확인 다했으면, G자리 값을 반환한다
    if (dp[targetY][targetX] == 1e9) return -1;
    else return dp[targetY][targetX];
}