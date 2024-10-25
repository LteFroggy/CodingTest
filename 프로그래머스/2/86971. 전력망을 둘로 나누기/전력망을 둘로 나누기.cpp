#include <string>
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

/*
    입력은 트리이다!
    각 노드마다 자신 + 자신의 자식의 개수를 저장한다.
    
    모두 구했다면, 총합 - 개수가 가장 작은 친구가 잘라야 하는 가지가 된다.
    구하는 과정에서 탐색을 하자.
    
    
    먼저 1번 노드를 잡아서 Head로 만든다.
    그리고 이어진 노드를 재귀적으로 들어간다
    이어진 노드 하나당 값을 1씩 늘리면 됨
*/

// 탐색하고 값을 저장해줄 함수
int search_tree(const vector<vector<int>> &edges, vector<bool> &visited, vector<int> &result, int now_loc);

int solution(int n, vector<vector<int>> wires) {
    int answer = -1;
    
    // 이어진 노드들을 저장할 vector
    vector<vector<int>> edges(n);
    
    // 방문 여부 저장할 vector
    vector<bool> visited(n);
    
    // 각 노드 개수를 저장할 vector
    vector<int> connected_nodes(n);
    
    // 각 값을 보면서 노드 이어주기
    for (auto wire : wires) {
        edges[wire[0] - 1].push_back(wire[1] - 1);
        edges[wire[1] - 1].push_back(wire[0] - 1);
    }
    
    // 연산 시작
    // 헤드는 0으로 정했으므로, 0으로 시작시킨다.
    visited[0] = true;
    search_tree(edges, visited, connected_nodes, 0);
    
    
    // 이제 각 노드별로 자신 + 자식의 노드 개수가 저장되었다.
    // 어디를 잘라야 제일 차이가 적을지 저장한다.
    answer = 1e9;
    
    for (auto v : connected_nodes) {
        int sub_val = n - v;
        int diff = abs(sub_val - (n - sub_val));
        if (diff < answer) {
            answer = diff;
        }
    }
    
    
    return answer;
}


/* ㅡㅡㅡㅡㅡ 함수 구현부 ㅡㅡㅡㅡㅡ */
int search_tree(const vector<vector<int>> &edges, vector<bool> &visited, vector<int> &connected_nodes, int now_loc) {
    // 일단 이어진 노드를 카운트할 때, 나를 센다
    int node_count = 1;
    
    // 일단 이어진 노드가 있는지 확인한다.
    for (auto next : edges[now_loc]) {
        // 가보지 않은 노드라면, 가본다.
        if (!visited[next]) {
            visited[next] = true;
            // 길을 따라가보며, 이어진 노드 갯수에 추가한다
            node_count += search_tree(edges, visited, connected_nodes, next);
        }
    }
    
    // 다 가봤다면, 지금의 개수가 나와 이어진 노드의 개수이다.
    // 값에 적용하고, return한다. 
    connected_nodes[now_loc] = node_count;
    // cout << now_loc + 1 << "번에서 자르면 이어진 노드는 " << node_count << "개" << endl;
    return node_count;
}
    