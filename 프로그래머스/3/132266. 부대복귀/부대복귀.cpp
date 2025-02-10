#include <string>
#include <vector>
#include <queue>

using namespace std;

/*
    부대가 위치한 지역은 번호로 구분되고, 지역 간의 길을 통과하는 데는 모두 1의 시간이 걸린다.
    각 부대원은 지도 정보를 바탕으로 최단시간에 부대로 복귀하고자 하는데, 시작 때와 다르게 돌아오는 경로가 없어져 복귀가 불가능할수도 있다.
    
    총 지역의 수는 n개이며 각 부대원이 위치한 지역을 나타내는 sources가 있다. 이 원소 순서대로 복귀할 수 있는 최단시간을 담은 배열을 return하자
    
    도착지점에서부터 모든 지역을 탐색하면 된다.
*/

vector<int> solution(int n, vector<vector<int>> roads, vector<int> sources, int destination) {
    vector<int> answer;
    
    // 최단거리 저장을 위한 배열
    vector<int> shortest_paths(n, 1e9);
    
    // 각 지역에서 갈 수 있는 길을 담은 2차원 배열
    vector<vector<int>> paths(n, vector<int>());
    
    // 갈 수 있는 길을 정리한다.
    for (auto v : roads) {
        paths[v[0] - 1].push_back(v[1] - 1);
        paths[v[1] - 1].push_back(v[0] - 1);
    }
    
    // 탐색을 위한 queue<현위치, 비용> 생성 및 초기 설정
    queue<pair<int, int>> que;
    que.push({destination - 1, 0});
    shortest_paths[destination - 1] = 0;
    
    
    // 최단거리를 탐색한다
    while(!que.empty()) {
        int nowLoc = que.front().first;
        int cost = que.front().second;
        
        que.pop();
        
        // 갈 수 있는 모든 길을 탐색한다.
        for (auto next : paths[nowLoc]) {
            if (shortest_paths[next] < cost + 1) continue;
            que.push({next, cost + 1});
            shortest_paths[next] = cost + 1;
        }
    }
    
        // 이제, sources의 순서대로 값을 answer에 넣는다
    for (auto source : sources) {
        if (shortest_paths[source - 1] == 1e9) answer.push_back(-1);
        else answer.push_back(shortest_paths[source - 1]);
    }

    
    return answer;
}