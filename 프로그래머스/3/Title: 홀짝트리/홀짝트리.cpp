#include <string>
#include <unordered_map>
#include <vector>
#include <queue>

using namespace std;

/*
    루트노드가 없는 포레스트가 있다. 각각은 홀수, 짝수, 역홀수, 역짝수이다. !!! 0은 짝수 !!!
    
    홀수는 노드가 홀수고, 자식 개수가 홀수이다.
    짝수는 벊가 짝수고, 자식 개수가 짝수이다
    역홀수 노드는 값은 홀수인데, 자식이 짝수
    역짝수는 값이 짝수인데, 자식이 홀수
    
    각 트리에 대해 루트를 설정했을 떄, 홀짝트리가 될 수 있는 트리의 개수와 역홀짝트리가 될 수 있는 트리의 개수 구하기.
    
    혹짝트리는 홀수, 짝수노드로만 이루어짐
    역홀수노드는 역홀수, 역짝수 노드로만 이루어진 트리
    
    하나의 노드는 이어진 개수가 정해져있다. 따라서 자기가 루트가 아니라면, 이 친구의 노드 종류는 정해져있다.
    그럼 각 노드별로 얘가 루트가 아닐 떄, 루트일 때의 경우의 수만 정리하면 된다.
    특히 홀수 - 역홀수, 짝수 - 역짝수는 자신을 루트로 지정했을 때 반드시 바뀐다.
    
    연결된 노드의 개수만 중요하므로, 각 노드마다 연결 카운트만 계산. 값은 신경쓰지 않음
    
    근데 총 몇 개의 트리인지는 구분할 수 있어야 함.
    아니면 그냥 연결 기반으로 해도 될지도??
*/

vector<int> solution(vector<int> nodes, vector<vector<int>> edges) {
    vector<int> answer(2, 0);
    
    unordered_map<int, vector<int>> connMap;
    
    // 일단 엣지들 다 보면서 연결해주기
    for (auto v : edges) {
        int a = v[0];
        int b = v[1];
        
        connMap[a].push_back(b);
        connMap[b].push_back(a);
    }
    
    // 일단, 루트가 아닐 시에 어떤 노드인지 확인
    unordered_map<int, bool> type;
    
    for (auto val : nodes) {
        if (val % 2 == connMap[val].size() % 2) type[val] = true;
        else type[val] = false;
    }
    
    unordered_map<int, bool> visited;
    
    // 엣지 확인하면서 트리 종류 확인
    for (int val : nodes) {
        // 이미 본 노드 스킵
        if (visited[val]) continue;
        
        // 안 본 노드면 진행
        int aCount(0), bCount(0);
        
        queue<int> que;
        que.push(val);
        visited[val] = true;
        if (val % 2 == connMap[val].size() % 2) aCount++;
        else bCount++;
        
        while (!que.empty()) {
            int now = que.front();
            que.pop();
            
            for (auto next : connMap[now]) {
                if (visited[next]) continue;
                
                que.push(next);
                if (next % 2 == connMap[next].size() % 2) aCount++;
                else bCount++;
                visited[next] = true;
            }
        }
        
        
        if (aCount == 1) answer[0]++;
        if (bCount == 1) answer[1]++;
    }
    
    return answer;
}
