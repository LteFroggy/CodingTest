#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

/*
    무인도로 가기 위한 지도.
    상하좌우는 하나의 무인도
    일단 섬별로 얼마나 지낼 수 있는지 보자.
*/

vector<int> solution(vector<string> maps) {
    vector<int> answer;
    int n = maps.size();
    int m = maps[0].size();
    
    vector<vector<bool>> visited(n, vector<bool>(m, false));

    
    // 상하좌우 이동용 변수
    int dy[] = {-1, 1, 0, 0};
    int dx[] = {0, 0, 1, -1};
        
    // 모든 칸을 본다
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            // 이미 확인한 칸이면 확인 안함
            if (visited[i][j] == true) continue;
            // 값이 X여도 확인 안함
            else if (maps[i][j] == 'X') continue;
            
            // 둘 다 아닌 숫자값이 있다면, 탐색 시작.
            int days(maps[i][j] - '0');
            
            queue<vector<int>> que;
            que.push({i, j});
            visited[i][j] = true;
            
            while (!que.empty()) {
                int y = que.front()[0];
                int x = que.front()[1];
                que.pop();
                
                for (int k = 0; k < 4; k++) {
                    int y_ = y + dy[k];
                    int x_ = x + dx[k];
                    
                    // 보드 넘어갔으면, 넘기기
                    if (y_ < 0 || y_ >= n || x_ < 0 || x_ >= m) continue;
                    
                    // X칸이어도 탐색 안하기
                    else if (maps[y_][x_] == 'X') continue;
                    
                    // 이미 방문했어도 탐색 안하기
                    else if (visited[y_][x_]) continue;
                    
                    // 다 아니라면 값을 더하고, 큐에 삽입 후 방문처리
                    days += maps[y_][x_] - '0';
                    que.push({y_, x_});
                    visited[y_][x_] = true;
                }
            }
            // 연걸된 모든 섬 체크 후에 answer에 넣어주기
            answer.push_back(days);
        }
    }
    
    // 반환 전에 조정
    sort(answer.begin(), answer.end());
    if (answer.size() == 0) answer.push_back(-1);
    return answer;
}