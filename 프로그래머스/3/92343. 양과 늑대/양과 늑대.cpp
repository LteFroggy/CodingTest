#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

/*
    이진트리. 늑대와 양
    루트 노드에서 출발하면서 노드를 돌아다니며 양을 모을 것이다
    
    각 노드를 방문할때마다 양과 늑대가 날 따라온다! 늑대의 수가 양 이상이 되면 모든 양을 먹어버린다..
    
    잡아먹히지 않도록 하면서 최대한 많은 수의 양을 모아 루트로 돌아오자
    노드가 겨우 17개밖에 안되니, 그냥 완전완전탐색 해야 할 듯
*/

/*
    완전완전탐색 수행하는 함수
    int node_now                현재 위치
    vector<int> sheep_wolf      현재의 양과 늑대 정보
    vector<vector<int>> paths   진행 가능한 경로 정보
    list<int> que              갈 수 있는 노드
    vector<int> info            양, 늑대 정보    
    int max_count               지금까지 모은 최대 양 마리수
*/
void getMaximumSheeps(int node_now, vector<int> sheep_wolf, const vector<vector<int>> &paths, const vector<int>& info, list<int> candidates, int& max_count) {
    // 내가 지금까지 모은 양이 최대치라면, 갱신한다!
    if (sheep_wolf[0] > max_count) max_count = sheep_wolf[0];

    
    /// cout << "현재 위치는 " << node_now << endl;
    
    // 현재 위치에서 갈 수 있는 길을 등록해둔다
    for (auto next : paths[node_now]) {
        /// cout << next << "가 후보지에 추가됨" << endl;
        candidates.push_back(next);
    }
    
    // 이제, 갈 수 있는 길을 하나하나 탐색해본다
    for (auto it = candidates.begin(); it != candidates.end();) {
        // 다음 위치 값 확인, 양이라면 그냥 가보면 된다
        if (info[*it] == 0) {
            int next = *it;
            
            /// cout << "양은 " << sheep_wolf[0] << "마리, 늑대는 " << sheep_wolf[1] << "마리, 양이 있는 " << next << "로 진행해봄" << endl;
            // 재귀 들어가기 전 값 세팅
            sheep_wolf[0]++;
            it = candidates.erase(it);
            
            getMaximumSheeps(next, sheep_wolf, paths, info, candidates, max_count);
            
            // 재귀 나온 후 값 초기화
            sheep_wolf[0]--;
            candidates.insert(it, next);
        }
        
        // 늑대인데, 양의 마리수에 여유가 있다면 가보면 됨
        else if (sheep_wolf[0] - 1 > sheep_wolf[1]) {
            int next = *it;
            /// cout << "양은 " << sheep_wolf[0] << "마리, 늑대는 " << sheep_wolf[1] << "마리, 늑대가 있는 " << next << "로 진행해봄" << endl;
            // 재귀 들어가기 전 값 세팅
            sheep_wolf[1]++;
            it = candidates.erase(it);
            
            getMaximumSheeps(next, sheep_wolf, paths, info, candidates, max_count);
            
            // 재귀 나온 후 값 초기화
            sheep_wolf[1]--;
            candidates.insert(it, next);
        }
        
        // 아직 갈 수 없는 위치라면, 그냥 넘기기
        else ++it;
    }
}

int solution(vector<int> info, vector<vector<int>> edges) {
    int answer = 0;
    // 먼저, 노드별로 갈 수 있는 길을 정리해둔다
    vector<vector<int>> paths(info.size());
    
    // 어차피 루트에서 아래로만 내려갈 것이다! 갈 수 있는 길만 잘 봐두면 됨
    for (auto v : edges) {
        paths[v[0]].push_back(v[1]);
    }
    
    // 항상 시작은 0번이다! 그리고 0번에는 항상 양이 있음
    int start = 0;
    vector<int> sheep_wolf = {1, 0};
    list<int> candidates;
    
    getMaximumSheeps(start, sheep_wolf, paths, info, candidates, answer);
    return answer;
}