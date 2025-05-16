#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>

using namespace std;

/*
    다각형 지형에서 캐릭터가 이동한다.
    캐릭터는 이 다각형의 둘레를 따라 이동한다.
    
    중앙에 빈 공간이 생겨도, 바깥쪽 테두리만 본다.
    
    아이템의 위치가 주어지면, 이동하는 가장 짧은 거리를 Return하자
    
    일단 내, 외부를 구분해야 한다. 그를 위해 좌표를 두 배로 확장한다고 함.
    두 배로 확장하는 이유는, 경계선과 내부를 구분하기 위해
    
    예를 들어 1,1 ~ 4,4와 2,2 ~ 3,3 이 있을 경우
    
    1 1 1 1
    1 1 1 1
    1 1 1 1
    1 1 1 1
    
    이게 좌표가 된다. 이러면 DFS로 최단거리를 탐색할 때 테두리라고 생각하는 1을 따라갔다가는 내부를 관통할 수 있게 된다.
    좌표를 두 배로 확장하면 아래와 같아진다.
    
    1 1 1 1 1 1 1 1
    1 0 0 0 0 0 0 1
    1 0 1 1 1 1 0 1
    1 0 1 0 0 1 0 1
    1 0 1 0 0 1 0 1
    1 0 1 1 1 1 0 1
    1 0 0 0 0 0 0 1
    1 1 1 1 1 1 1 1
    
    이러면 이제 이쁘게 외곽선만 타고 다닐 수 있는 것!
*/

int solution(vector<vector<int>> rectangle, int characterX, int characterY, int itemX, int itemY) {
    int answer = 0;
    
    // 일단, 확장한 보드를 만든다
    vector<vector<int>> board(102, vector<int>(102));
    
    int maxVal = 0;
    
    // 확장한 보드에 적용한다
    for (auto v : rectangle) {
        int leftX = v[0] * 2;
        int rightX = v[2] * 2;
        int upY = v[1] * 2;
        int downY = v[3] * 2;
        
        if (maxVal < downY) maxVal = downY;
        if (maxVal < rightX) maxVal = rightX;
        
        // 가로선 긋기
        for (int x = leftX; x <= rightX; x++) {
            board[upY][x] = 1;
            board[downY][x] = 1;
        }
        
        // 세로선 긋기
        for (int y = upY; y <= downY; y++) {
            board[y][leftX] = 1;
            board[y][rightX] = 1;
        }
    }
    
    // 이제 Flood Fill을 통해 진짜 외곽선을 탐색한다.
    vector<vector<int>> real_board(102, vector<int>(102, 2));
    queue<pair<int, int>> que;
    que.push({0, 0});
    real_board[0][0] = 0;
    /*
    int dy[4] = {0, 0, 1, -1};
    int dx[4] = {1, -1, 0, 0};
    */
    
    int dy[8] = {0, 0, 1, -1, -1, -1, 1, 1};
    int dx[8] = {1, -1, 0, 0, 1, -1, 1, -1};
    
    while(!que.empty()) {
        // 현재 칸
        int y = que.front().first;
        int x = que.front().second;
        que.pop();
        
        // 상하좌우 보기
        for (int k = 0; k < 8; k++) {
            int y_ = y + dy[k];
            int x_ = x + dx[k];
            // 보드 밖이라면 넘기기
            if (y_ < 0 || y_ >= real_board.size() || x_ < 0 || x_ >= real_board.size()) continue;
            // 이미 본 칸이어도 넘기기
            if (real_board[y_][x_] != 2) continue;
            
            // 안 본 칸이라면, 값 넣기
            if (board[y_][x_] == 0) {
                real_board[y_][x_] = 0;
                que.push({y_, x_});
            }
            
            // 1이라면, 값만 넣고 탐색은 하지 않기
            else if (board[y_][x_] == 1) {
                real_board[y_][x_] = 1;
            }
        }
    }
    
    // 확인용 출력
    /*
    for (int i = maxVal; i >= 0; i--) {
        for (int j = 0; j <= maxVal; j++) {
            cout << real_board[i][j] << " ";
        }
        cout << endl;
    }
    */
    
    // 이제, 시작점에서부터 BFS로 탐색하기
    queue<vector<int>> search_que;
    // 시작좌표, 총 이동거리
    search_que.push({characterY * 2, characterX * 2, 0});
    // 이미 방문한 외곽선은 값을 3으로 바꿈
    real_board[characterY * 2][characterX * 2] = 3;
    
    int dy2[4] = {0, 0, 1, -1};
    int dx2[4] = {1, -1, 0, 0};
    
    while (!search_que.empty()) {
        // 타고 가면서 제일 짧은 루트 찾기
        int y = search_que.front()[0];
        int x = search_que.front()[1];
        int cost = search_que.front()[2];
        search_que.pop();
        
        // 목표 지점에 도달했나?? 그렇다면 절반 값 넘기기. 이유는 좌표를 2배로 확장했으니까..
        if (y == itemY * 2 && x == itemX * 2) return cost / 2;
        
        // 아니라면 상하좌우 보면서 1로만 이동
        for (int k = 0; k < 4; k++) {
            int ny = y + dy2[k];
            int nx = x + dx2[k];
            
            // 범위 넘어가면 넘기기
            if (ny < 0 || ny >= 102 || nx < 0 || nx >= 102) continue;
            
            // 값이 1 아니어도 넘기기
            if (real_board[ny][nx] != 1) continue;
            
            // 1이라면, 큐에 넣고 간다
            search_que.push({ny, nx, cost + 1});
            real_board[ny][nx] = 3;
        }
    }
    
    
    return -1;
}