#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>

using namespace std;

/*
    n개의 노드가 존재하는 그래프 있음
    각 노드는 1~n까지 번호 있다.
    
    1에서 가장 멀리 떨어진 노드의 갯수를 구하려 함
    이는 최단경로로 이동했을 때, 간선의 개수가 가장 많은 노드를 의미한다
    
    각 1번 노드로부터 가장 멀리 떨어진 노드가 몇 개인지를 return하자
    
    각 노드에 숫자를 준다. 전의 값 +1로 갱신하고, 마지막에 모든 노드의 값을 보면 됨
*/

int solution(int n, vector<vector<int>> edge) {
    int answer = 0;
    vector<vector<int>> possible_routes(n);
    
    vector<int> shortest_path(n, 1e9);
    
    // 가능한 경로 모두 삽입하기
    for (auto v : edge) {
        possible_routes[v[0] - 1].push_back(v[1] - 1);
        possible_routes[v[1] - 1].push_back(v[0] - 1);
    }
    
    // 탐색하기, 시작 지점은 0번 노드이고, 거리는 0에서 시작한다
    queue<int> que;
    que.push(0);
    shortest_path[0] = 0;
    
    while (!que.empty()) {
        // 현재 위치와 그 거리를 확인한다
        int now = que.front();
        int now_dist = shortest_path[now];
        que.pop();
        
        // 현재 위치에서 갈 수 있는 다음 위치를 다 본다
        for (auto next : possible_routes[now]) {
            // 만약, 이게 더 짧은 거리라면 진행하고 아니면 만다
            if (shortest_path[next] > now_dist + 1) {
                shortest_path[next] = now_dist + 1;
                que.push(next);
            }
        }
    }
    
    // 이제 가장 먼 거리가 몇 개인지 셀 것이다. 정렬해버리기
    sort(shortest_path.rbegin(), shortest_path.rend());
    
    // 출력해서 결과 확인
    /*
    for (auto v : shortest_path) cout << v << " ";
    cout << endl;
    */
    
    int max_val = shortest_path[0];
    
    for (auto v : shortest_path) {
        if (max_val > v)
            break;
        else
            answer++;
    }
    
    return answer;
}