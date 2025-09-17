#include <queue>
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

/*
    물류창고에 알파벳 대문자로 종류 구분 가능한 컨테이너
    세로 n줄, 가로 m줄
    
    특정 종류 컨테이너의 출고 요청이 들어오면?? 접근 가능한 컨테이너 모두 꺼내기.
    접근 가능이란 한쪽면이라도 외부랑 연결되어있어야 함
    
    한 알파벳이 두번 나오면, 그냥 모든 컨테이너가 크레인에 의해 다 꺼내진다
    
    outside 확인용 배열을 확인한다.
    그리고 바로 꺼낼 수 있는 값들을 저장하기 위한 unordered_map<char, pair<int, int>> 사용
*/

typedef pair<int, int> point;

int solution(vector<string> storage, vector<string> requests) {
    int answer = 0;
    
    int n = storage.size();
    int m = storage[0].size();
    
    // 바깥과 맞닿아있는지 체크하기 위한 값
    vector<vector<bool>> outside(n, vector<bool>(m, false));
    // 바로 제거 가능한 리스트 임시저장용
    vector<queue<point>> removable(26);
    
    // 처음에는 outside가 없다. 그리고 제일 바깥쪽은 바로 출고 가능
    int y1 = 0;
    int y2 = n - 1;
    int x1 = 0;
    int x2 = m - 1;
    // 왼쪽, 오른쪽 넣기
    for (int y = 0; y < n; y++) {
        char val = storage[y][x1];
        removable[val - 'A'].push({y, x1});
        val = storage[y][x2];
        removable[val - 'A'].push({y, x2});
    }
    
    // 위, 아래 넣기
    for (int x = 0; x < m; x++) {
        char val = storage[y1][x];
        removable[val - 'A'].push({y1, x});
        val = storage[y2][x];
        removable[val - 'A'].push({y2, x});
    }
    
    int dy[4] = {1, -1, 0, 0};
    int dx[4] = {0, 0, 1, -1};
    
    /*
    cout << "초기 보드판 상태" << endl;
    for (auto v : storage) {
        cout << v;
        cout << endl;
    }
    */
    
    for (auto command : requests) {
        /// cout << "삭제 명령 : " << command << endl;
        
        // 이번에 적재할 물건값
        char target = command[0];
        
        // 삭제될 값 모아둘 임시 버퍼
        queue<point> removed_vals;
        
        // 명령어가 두글자라면, 전체탐색하면서 모두 제거함
        if (command.length() == 2) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (storage[i][j] == target) {
                        removed_vals.push({i, j});
                    }
                }
            }
        }
        
        // 한글자라면, deliverable 체크하면서 제거할 곳 찾기
        else {
            while (!removable[target - 'A'].empty()) {
                int y = removable[target - 'A'].front().first;
                int x = removable[target - 'A'].front().second;
                removable[target - 'A'].pop();
                
                // 4방향 중에 하나라도 outside가 있어야 함
                for (int k = 0; k < 4; k++) {
                    int y_ = y + dy[k];
                    int x_ = x + dx[k];
                    
                    // 체크할 범위가 넘어갔거나, outside가 옆에 있으면 삭제 후보가 됨
                    if (y_ < 0 || y_ >= n || x_ < 0 || x_ >= m || outside[y_][x_] == true) {
                        removed_vals.push({y, x});
                        break;
                    }
                }
            }
        }
        
        // 이번에 삭제되는 위치들 처리
        while (!removed_vals.empty()) {
            int y = removed_vals.front().first;
            int x = removed_vals.front().second;
            removed_vals.pop();
            
            // 이미 삭제된 값이라면 처리 안함
            if (storage[y][x] == '#') continue;
            
            // storage에서 값 삭제처리
            storage[y][x] = '#';
            answer++;
            /// cout << y + 1 << ", " << x + 1 << " 값 삭제됨" << endl;
            
            // 현재 값이 외곽과 맞닿아있다면, BFS로 추가 외곽 탐색해야 함
            int flag = false;
            for (int k = 0; k < 4; k++) {
                int y_ = y + dy[k];
                int x_ = x + dx[k];
                
                // 외곽인지 확인
                if (y_ < 0 || y_ >= n || x_ < 0 || x_ >= m || outside[y_][x_] == true) {
                    flag = true;
                    break;
                }
            }
            
            // BFS 할 필요 없다면 여기까지만 하고 반환
            if (!flag) continue;
        
            // BFS로 추가 탐색
            queue<point> que;
            que.push({y, x});
            outside[y][x] = true;
            
            while (!que.empty()) {
                int y = que.front().first;
                int x = que.front().second;
                que.pop();
                
                for (int k = 0; k < 4; k++) {
                    int y_ = y + dy[k];
                    int x_ = x + dx[k];
                    
                    // 저장소 밖이면 처리안함
                    if (y_ < 0 || y_ >= n || x_ < 0 || x_ >= m) continue;
                    
                    // outside여도 처리 안함
                    if (outside[y_][x_]) continue;
                    
                    // outside가 아니며, 값이 있는 경우에는 removable에 삽입
                    if (storage[y_][x_] != '#') {
                        removable[storage[y_][x_] - 'A'].push({y_, x_});
                    }
                    
                    // 값이 없는 경우에는 추가 탐색
                    else {
                        que.push({y_, x_});
                        outside[y_][x_] = true;
                    }
                }
            }
        }
        
        /*
        cout << "보드판 상태" << endl;
        for (auto v : storage) {
            cout << v;
            cout << endl;
        }   
            
        cout << endl << endl;
        */
    }
    
    return (n * m) - answer;
}