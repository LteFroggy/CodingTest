#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <iomanip>

using namespace std;

/*
    1x1 크기 칸들로 이루어진 직사각형 격자 형태의 미로에서 탈출하고자 한다.
    각 칸은 통로 혹은 벽으로 구성되어 있음.
    
    통로들 중 한 칸에는 미로를 나가는 문이 있는데, 레버를 당겨야 함.
    
    그래서 일단 출발에서 레버까지 가고, 레버에서 문까지 가야 함.
    최대한 빠르게 미로 탈출하는 시간 찾기
    
    BFS로 시작점에서부터 레버, 레버에서부터 출구 가지치기 하면서 가자
*/

struct distInfo {
    int cost;
    bool isPulledLever;
    
    distInfo(int a, int b) : cost(a), isPulledLever(b) {}
};

typedef pair<int, int> point;

int solution(vector<string> maps) {
    int answer = 0;
    
    // 일단, 시작, 레버, 출구 위치 찾기
    int startY, startX;
    int leverY, leverX;
    int exitY, exitX;
    for (int i = 0; i < maps.size(); i++) {
        for (int j = 0; j < maps[0].size(); j++) {
            if (maps[i][j] == 'S') {
                startY = i;
                startX = j;
            }
            
            else if (maps[i][j] == 'L') {
                leverY = i;
                leverX = j;
            }
            
            else if (maps[i][j] == 'E') {
                exitY = i;
                exitX = j;
            }
        }
    }
    
    // 시작점에서부터 레버 제일 가까운 거리 찾기
    // point는 현위치, bool은 레버 방문 여부
    queue<pair<point, bool>> que;
    vector<vector<distInfo>> distMap(maps.size(), vector<distInfo>(maps[0].size(), distInfo(1e9, false)));
    
    // 시작점, 코스트 지정
    que.push({{startY, startX}, false});
    distMap[startY][startX] = distInfo(0, false);
    
    // 상하좌우 탐색용 변수
    int dy[4] = {-1, 1, 0, 0};
    int dx[4] = {0, 0, 1, -1};
    
    while(!que.empty()) {
        int nowY = que.front().first.first;
        int nowX = que.front().first.second;
        int cost = distMap[nowY][nowX].cost;
        bool isPulledLever = que.front().second;
        
        que.pop();
        
        for (int k = 0; k < 4; k++) {
            int newY = nowY + dy[k];
            int newX = nowX + dx[k];
            bool newIsPulledLever;
            
            // 범위 넘어가지 않는지 체크
            if (newY < 0 || newY >= maps.size() || newX < 0 || newX >= maps[0].size()) continue;
            
            // 값이 X이면 못 가는 곳임
            if (maps[newY][newX] == 'X') continue;
                
            // 도착지점이 혹시 레버라면, isPulledLever값을 true로 변경
            if (maps[newY][newX] == 'L') newIsPulledLever = true;
            else newIsPulledLever = isPulledLever;
            
            // 일단, 레버를 당겨야 목적지에 가는 것이 의미가 있으므로, isPulledLever가 false인 값을 true가 무조건 덮어쓰도록
            if (!distMap[newY][newX].isPulledLever 
                && newIsPulledLever) {
                distMap[newY][newX].cost = cost + 1;
                distMap[newY][newX].isPulledLever = newIsPulledLever;
                
                que.push({{newY, newX}, newIsPulledLever});
            }
            
            // 둘 다 레버를 당기기 전이거나, 둘 다 당긴 후라면 더 적은 값이 들어가도록
            else if (distMap[newY][newX].isPulledLever == newIsPulledLever 
                    && distMap[newY][newX].cost > cost + 1) {
                distMap[newY][newX].cost = cost + 1;
                que.push({{newY, newX}, newIsPulledLever});
            }
                    
        }
    }
    
    // 결과 확인하기
    for (auto v_ : distMap) {
        for (auto v : v_) {
            cout << setw(2) << (v.cost == 1e9 ? "X" : to_string(v.cost)) << " ";
        }
        cout << endl;
    }
    
    // 결과값 반환하기
    if (!distMap[exitY][exitX].isPulledLever || distMap[exitY][exitX].cost == 1e9) return -1;
    else return distMap[exitY][exitX].cost;
}