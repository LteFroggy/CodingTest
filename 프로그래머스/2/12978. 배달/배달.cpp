#include <iostream>
#include <vector>
#include <stack>
using namespace std;

/*
    N개의 마을로 이뤄진 나라가 있다. 1 ~ N까지의 번호가 부여되어 있음
    양방향으로 통행이 가능한데, 시간이 도로별로 다르다.
    1번 마을에서 배달을 하려고 하는데, K시간 이하로 배달 가능한 음식점에서만 주문한다.
    
    배달 가능한 마을의 개수를 구하자.
    
    마을을 탐색하면서 시간을 계속 갱신하는 방법을 선택해야 할 듯. 그런데 도로마다 걸리는 시간이 다르기 때문에, 다익스트라를 사용해야 한다.
    기존 비용보다 적을 경우에만 탐색을 진행한다.
    
    먼저 2차원 벡터로, 각 도시에서 갈 수 있는 길을 모두 저장한다.
*/

// 최대값으로 설정
int MAX = int(10e8);

// typedef pair<int, int> Edge;

struct Edge {
    int dest;
    int distance;
    
    Edge(int a, int b) : dest(a), distance(b) {};
};

int solution(int N, vector<vector<int>> road, int K) {
    int answer = 0;
    vector<vector<Edge>> pos_ways(N + 1, vector<Edge>());
    vector<int> shortest_dist(N + 1, MAX);
    
    
    for (int i = 0; i < road.size(); i++) {
        // road정보를 보면서, 갈 수 있는 길들을 미리 저장해둔다.
        int start, end, distance;
        start = road[i][0];
        end = road[i][1];
        distance = road[i][2];
        
        // start에는 end의 정보를, end에는 start의 정보를 넣어주기
        pos_ways[start].push_back({end, distance});
        pos_ways[end].push_back({start, distance});
    }
    
    // 1에서 시작한다.
    shortest_dist[1] = 0;
    int now = 1;
    stack<int> stk;
    stk.push(now);
    
    while (!stk.empty()) {
        // 일단 현재 자리를 확인한다.
        now = stk.top();
        stk.pop();
        
        // now에서 갈 수 있는 길 중, 최저 길이인 길만 간다
        for (auto next : pos_ways[now]) {
            int dest = next.dest;
            // 지금 가는 길이 목표 노드로 가는 제일 짧은 길인지 체크
            if (shortest_dist[next.dest] > shortest_dist[now] + next.distance) {
                shortest_dist[next.dest] = shortest_dist[now] + next.distance;
                // 만약 그렇다면, queue에 집어넣고 탐색 진행하기
                stk.push(next.dest);
            }
        }
    }
    
    // 탐색이 종료되면 모든 최소 길이가 나온다. 이를 통해 answer 갱신
    for (auto dist : shortest_dist) {
        if (dist <= K) {
            answer++;
        }
    }
    
    return answer;
}