#include <queue>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>

using namespace std;

/*
    크루스칼로 경로 압축 이후, 다익스트라 수행하기
    
*/

// 시간 덜 걸리는 경로 순으로 정렬
bool comp_std(vector<int> a, vector<int> b) {
    return a[2] < b[2];
}

class union_find {
private :
    vector<int> parents;
    
    // 부모 찾기
    int find(int a) {
        if (parents[a] == a) 
            return a;
        else
            return parents[a] = find(parents[a]);
    }
    
public :
    // 생성자에서 vector 초기화
    union_find(int N) {
        parents = vector<int>(N + 1);
        
        for (int i = 1; i <= N; i++) {
            parents[i] = i;
        }
    }
    
    // 바로 임의접근 가능하도록 지정
    int operator[](int index) {
        return find(index);
    }
    
    // 링크 삽입하기. 삽입 성공하면 true, 실패하면 false이다.
    bool insert(int a, int b) {
        int a_parent = find(a);
        int b_parent = find(b);
        
        if (a_parent != b_parent) {
            parents[a_parent] = b_parent;
            return true;
        }
        else
            return false;
    }
};

vector<int> solution(int n, vector<vector<int>> paths, vector<int> gates, vector<int> summits) {
    vector<int> answer;
    // 출발, 도착지를 계산할 set
    unordered_set<int> gateSet;
    unordered_set<int> summitSet;
    
    for (auto v : gates) gateSet.insert(v);
    for (auto v : summits) summitSet.insert(v);
    
    // union-find용 클래스
    union_find ufClass(n);
    
    // 이제 크루스칼 수행할 것
    vector<vector<int>> new_paths;
    int connect_count = 0;
    
    sort(paths.begin(), paths.end(), comp_std);
    
    for (auto path : paths) {
        // 각 경로가 잇는 두 곳을 확인한다.
        int start = path[0];
        int end = path[1];
        int cost = path[2];
        
        // 두 경로가 모두 시작점이거나, 산봉우리라면 이런 경로는 필요가 없다. 어차피 하나의 시작점이나 산봉우리만 도착해야 하므로
        // 모두 시작점 중 하나인지 체크
        if (gateSet.count(start) && gateSet.count(end)) continue;
        
        // 모두 산봉우리 중 하나인지 체크
        if (summitSet.count(start) && summitSet.count(end)) continue;
        
        // 둘 다 아니라면, 크루스칼에 넣어준다
        bool flag = ufClass.insert(start, end);
        if (flag) {
            new_paths.push_back({start, end, cost});
            connect_count++;
        }
        
        // 가지치기용
        if (connect_count == n - 1) break;
    }
    
    //// 정렬되었는지 확인
    /*
    for (auto v : new_paths) {
        cout << v[0] << "-" << v[1] << " : " << v[2] << endl;
    }
    */
    
    // 새 경로를 possible_paths에 삽입
    vector<vector<pair<int, int>>> possible_paths(n + 1);
    for (auto path : new_paths) {
        possible_paths[path[0]].push_back({path[1], path[2]});
        possible_paths[path[1]].push_back({path[0], path[2]});
    }
    
    // 탐색
    queue<pair<int, int>> que;
    vector<int> costs;
    
    for (auto start : gates) {
        // 각 시작점에서부터 시작한다.
        que.push({start, 0});
        costs = vector<int>(n + 1, 1e9);
        costs[start] = 0;
        
        while (!que.empty()) {
            int nowLoc = que.front().first;
            int maxCost = que.front().second;
            que.pop();
            
            // 만약 현위치가 summit중 하나라면, 답에 저장한다.
            if (summitSet.count(nowLoc)) {
                if (answer.size() == 0) {
                    answer.push_back(nowLoc);
                    answer.push_back(maxCost);
                }
                
                else if (maxCost < answer[1] || 
                         (maxCost == answer[1] && nowLoc < answer[0])) {
                    answer[0] = nowLoc;
                    answer[1] = maxCost;
                }
                
                continue;
            }
            
            // 현재 위치에서 갈 수 있는 모든 다음 길을 탐색한다.
            for (auto next : possible_paths[nowLoc]) {
                int nextLoc = next.first;
                int nextCost = max(maxCost, next.second);
                
                // 그곳이 시작점이라면, 갈 필요 없음
                if (gateSet.count(nextLoc)) continue;
                
                // 시작점이 아니면서, 비용도 더 저렴하다면 가본다
                else if (nextCost < costs[nextLoc]) {
                    costs[nextLoc] = nextCost;
                    que.push({nextLoc, nextCost});
                }
            }
        }
    }
    
    return answer;
}