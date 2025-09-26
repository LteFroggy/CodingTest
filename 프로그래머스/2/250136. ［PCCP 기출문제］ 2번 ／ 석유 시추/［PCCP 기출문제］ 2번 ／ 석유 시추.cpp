#include <queue>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
    세로가 n, 가로가 m인 격자 땅에서 석유 발견 
    석유는 덩어리로 나눠있다. 시추관을 수직으로 딱 하나만 뚫을 수 있음.
    x값 기준으로 석유 위치 정렬
    
    땅은 총 250,000 크기
    
    조사에는 큰 무리 없음
    y값은 중요하지 않다. 따라서 x값만 생각하면 됨
    
    1. 칸을 다 보면서 DFS로 x시작, x끝, 매장량을 조사한다
    조사방법은 DFS면 될 듯
    
    2. 이를 기반으로 누적합을 생성한다
    
    3. 최대 누적합 값을 구한다.
*/

// x의 종료값 순으로 정렬하기 위한 기준
bool comp_std(vector<int> a, vector<int> b) {
    if (a[1] == b[1]) return a[0] < b[0];
    else return a[1] < b[1];
}

int solution(vector<vector<int>> land) {
    int answer = 0;
    int n = land.size();
    int m = land[0].size();
 
    // 이미 조사한 땅 또 조사하지 않기
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    
    // 석유 찾으면 저장하기. x시작, x끝, 매장량 순으로 저장할 것.
    vector<vector<int>> fuels;
    
    // 석유 찾았을 떄 DFS를 위한 queue
    queue<vector<int>> searchQue;
    
    int dy[4] = {-1, 0, 1, 0};
    int dx[4] = {0, -1, 0, 1};
    
    // 칸을 보면서 석유 다 찾기
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            // 이미 방문한 곳이면, 보지 않음
            if (visited[i][j]) continue;
            // 석유 매장되어있지 않으면, 그냥 넘기기
            else if (land[i][j] == 0) {
                visited[i][j] = true;
                continue;
            }
            
            // 석유가 있다면, DFS 시작해야 함
            int xMax = j;
            int xMin = j;
            int amount = 1;
            
            visited[i][j] = true;
            searchQue.push({i, j});
            
            // DFS
            while (!searchQue.empty()) {
                int y = searchQue.front()[0];
                int x = searchQue.front()[1];
                searchQue.pop();
                
                // 상하좌우에 묻힌 추가 석유 찾기
                for (int k = 0; k < 4; k++) {
                    int y_ = y + dy[k];
                    int x_ = x + dx[k];
                    
                    // 범위 넘어가면 확인하지 않기
                    if (y_ < 0 || y_ >= n || x_ < 0 || x_ >= m) continue;
                    
                    // 이미 가본 곳이어도 확인하지 않기
                    else if (visited[y_][x_]) continue;
                    
                    // 석유가 아니면, 방문처리만 하기
                    else if (land[y_][x_] == 0) {
                        visited[y_][x_] = true;
                    }
                    
                    // 석유라면, queue에 넣고, min, max, amount 수정
                    else {
                        visited[y_][x_] = true;
                        xMin = x_ < xMin ? x_ : xMin;
                        xMax = x_ > xMax ? x_ : xMax;
                        amount++;
                        searchQue.push({y_, x_});
                    }
                }
            } // DFS 종료
            
            // 모든 석유 탐색이 종료되었다면, 저장하기
            fuels.push_back({xMin, xMax, amount});
        }
    }
    
    // 확인용 출력
    /*
    for (auto v : fuels) {
        cout << v[0] << " 부터 " << v[1] << " 까지의 총 매장량 : " << v[2] << endl;
    }
    */
    
    // 이제 이를 바탕으로 누적합을 만든다.
    vector<int> prefixSum(m + 1, 0);
    
    for (auto fuel : fuels) {
        prefixSum[fuel[0]] += fuel[2];
        prefixSum[fuel[1] + 1] -= fuel[2];
    }
    
    for (int i = 1; i < m; i++) {
        prefixSum[i] += prefixSum[i - 1];
        answer = prefixSum[i] > answer ? prefixSum[i] : answer;
    }
    return answer;
}