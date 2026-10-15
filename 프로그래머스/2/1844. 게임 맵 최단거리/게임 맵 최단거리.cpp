#include <vector>
#include <queue>
#include <cmath>

using namespace std;

/*
    두 팀으로 나눠서 진행, 상대 팀 진영 파괴하면 이긴다.
    
    가능한 한 빨리 도착해야 함.
    
    한 팀의 팀원이 되어서 진행할거다.
    도착하기 위한 최소거리를 return 하도록 쓰기.
*/

int solution(vector<vector<int>> maps) {
    int answer = 0;
    
    queue<vector<int>> que;
    
    vector<vector<int>> maps_count(maps.size(), vector<int>(maps[0].size(), 1e9));
    
    int dy[] = {-1, 1, 0, 0};
    int dx[] = {0, 0, -1, 1};
    
    // 시작 지점 초기화
    vector<int> start = {0, 0};
    maps_count[0][0] = 1;
    
    que.push({0, 0});
    while (!que.empty()) {
        vector<int> now = que.front();
        que.pop();
        
        for (int k = 0; k < 4; k++) {
            int y_ = now[0] + dy[k];
            int x_ = now[1] + dx[k];
            
            // 맵 넘어가는지 체크
            if (y_ < 0 || y_ >= maps.size() || x_ < 0 || x_ >= maps[0].size()) { continue; }
            
            // 벽 칸이면 가지않음
            if (maps[y_][x_] == 0) { continue; }
            
            // 이미 내가 가는것보다 빠르게 갈 수 있으면 버리기
            if (maps_count[y_][x_] <= maps_count[now[0]][now[1]] + 1) { continue; }
            
            // 다 통과하면, 가기
            maps_count[y_][x_] = maps_count[now[0]][now[1]] + 1;
            que.push({y_, x_});
        }
    }
    
    return maps_count[maps.size() - 1][maps[0].size() - 1] == 1e9 ? -1 : maps_count[maps.size() - 1][maps[0].size() - 1];
}