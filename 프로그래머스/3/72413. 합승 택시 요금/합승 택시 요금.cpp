#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

/*  
    어피치랑 합승할 것! 음의 간선은 없으니 다익스트라 사용 가능하다.
    노드 개수는 n개, 출발은 s에서, A의 도착은 a, B의 도착은 b.
    
    두 지점 사이의 예상 요금 나타내는 fares가 매개변수.
    
    A, B 두 사람이 각각의 도착 지점까지 택시를 타고 간다고 할 떄, 최저 예상 택시요금 계산하기
    합승 없이 각자 이동하는게 더 싸다면, 합승 안 해도 됨.
    
    1. 출발지에서 각자 집까지 최소값을 구한다
    2. A에서 다른 모든 지점까지의 최소값을 구한다.
    3. B에서 다른 모든 지점까지의 최소값을 구한다.
    4. 모든 지점에서의 합을 구해서, 최소를 출력한다.
*/

vector<int> get_min_costs(const vector<vector<pair<int, int>>> &roads, int start, int N) {
    vector<int> result(N, 1e9);
    result[start] = 0;
    
    // 출발지에서부터 모든 지점까지의 최소비용을 계산할 것
    queue<pair<int, int>> que;
    // 출발지에서의 비용은 0이다
    que.push({start, 0});
    
    while (!que.empty()) {
        // 지금 내가 있는 땅에서 갈 수 있는 길을 모두 확인한다
        int now = que.front().first;
        int cost = que.front().second;
        que.pop();
        
        for (auto next : roads[now]) {
            // 비용이 더 저렴해진다면 갱신하고, 아니면 하지 않는다
            int cost_next = cost + next.second;
            if (cost_next < result[next.first]) {
                result[next.first] = cost_next;
                que.push({next.first, cost_next});
            }
        }
    }
    
    return result;
}

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {    
    // 출발지별로 도착할 수 있는 지점과 그에 따른 가격을 저장
    vector<vector<pair<int, int>>> roads(n, vector<pair<int, int>>());
    for (auto v : fares) {
        // 요금을 roads에 넣기
        roads[v[0] - 1].push_back({v[1] - 1, v[2]});
        roads[v[1] - 1].push_back({v[0] - 1, v[2]});
    }
    
    // 출발지에서 각 지점까지의 최소 가격 구하기
    vector<int> start_min_costs = get_min_costs(roads, s - 1, n);
    // a의 집에서부터 각 지점까지의 최소 가격 구하기
    vector<int> a_min_costs = get_min_costs(roads, a - 1, n);
    // b의 집에서부터 각 지점까지의 최소 가격 구하기
    vector<int> b_min_costs = get_min_costs(roads, b - 1, n);
    
    int answer = 1e9;
    // 이제 어디까지 합승해야 제일 저렴한지 찾기
    for (int i = 0; i < n; i++) {
        // 만약, 스타트지점에서 도달하지 못하는 곳이라면, A, B의 집에서도 도달할 수가 없다. 무시하기
        if (start_min_costs[i] == 1e9) continue;
        int sum(0);
        // i번째 점까지는 함께 가고, 거기서부턴 따로 갈 것
        sum += start_min_costs[i];
        sum += a_min_costs[i];
        sum += b_min_costs[i];
        
        if (sum < answer) {
            answer = sum;
        }
    }
    
    return answer;
}