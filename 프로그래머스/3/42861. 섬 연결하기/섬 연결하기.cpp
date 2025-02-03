#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*
    다리 건설 비용이 주어질 때, 최소의 비용으로 모든 섬이 통행 가능하도록 만들자.
    
    모든 다리를 고려하고, 최소 비용의 다리만 만들어나가면 된다. 사이클 없는 그래프 만들듯이
    사이클을 만들 필요가 없다. 어차피 다리 하나만 이어져있으면 되므로.
    
    모든 섬의 개수 -1개가 될때까지 다리를 지으면 된다.
*/

int find_parent(vector<int> parent_infos, int target) {
    if (parent_infos[target] == target)
        return target;
    
    else 
        return parent_infos[target] = find_parent(parent_infos, parent_infos[target]);
}

int solution(int n, vector<vector<int>> costs) {
    int answer = 0;
    
    // 일단 costs를 정렬한다
    sort(costs.begin(), costs.end(), [](const vector<int> &a, const vector<int> &b) -> bool {
       return a[2] < b[2];
    });
    
    // 그리고, 각 노드의 부모 저장을 위한 값을 생성한다
    vector<int> parent_infos(n);
    for (int i = 0; i < n; i++) {
        parent_infos[i] = i;
    }
    
    // 이제 제일 싼 다리부터 찾으면서 하나씩 짓는다
    int count = 0;
    
    for (auto bridge : costs) {
        int island1 = bridge[0];
        int island2 = bridge[1];
        int cost = bridge[2];
        
        // 둘의 부모를 확인하고, 같다면 짓지 않는다
        int parent1 = find_parent(parent_infos, island1);
        int parent2 = find_parent(parent_infos, island2);
        
        if (parent1 == parent2) continue;
        
        // 다르다면, 다리 건설하고 부모를 합친다
        parent_infos[parent1] = parent2;
        answer += cost;
        count++;
        
        // count가 n-1이 되면 다 지은 것!! 그만 짓는다
        if (count == n-1) break;
    }
    
    return answer;
}