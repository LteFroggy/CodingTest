#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

/*
    그래프는 도넛, 막대, 8자 등이 있다.
    
    1. 도넛은 n개의 정점과 n개의 간선이 있다. 아무 한 정점에서 출발해서 이용한 적 없는 간선을 따라가면, n-1개의 정점을 방문하고 다시 나에게로 돌아온다.
    2. 막대 모양 그래프는 n개의 간선과 n-1개의 간선이 있다. 임의의 한 정점에서 출발해서 간선을 계속 따라가면, 나머지 정점을 한 번씩 방문하는 정점이 있다!
    3. 8자 모양 그래프는 2n+1개의 정점과 2n+2개의 간선이 존재한다. 크기가 동일한 2개의 도넛 그래프에서 정점을 골라 결합시킨 형태!
    
    이 그래프들과 무관한 정점을 하나 생성하고, 각 그래프 정점 하나로 향하게 간선을 연결했다.
    간선 정보가 주어지면, 생성한 정점 번호와 정점 생성 전 도넛 수, 막대 수, 8자 수를 구하자.

    
    ## 먼저 생성한 정점을 찾아야 함!
    -> 어떤 정점이 보내기만 하고 받는 건 하나도 없다? -> 그럼 보내는 개수 확인해야 함. 하나만 보내면 막대의 시작, 두개 이상 보내면 그녀석이 새로 생긴 놈임
    
    생성한 정점을 찾았다면, 거기서부터 값을 받은 애들이 각각 무슨 모양인지만 탐색하면 된다.
    그래프별 특징을 보자.
    1. 도넛 -> 모든 값이 보내는 값 하나, 받는 값 하나임
    2. 막대 -> 모든 값이 보내는 값 하나 혹은 받는 값 하나만을 가짐(size 1인 경우에는 받지도, 보내지도 않음)
    3. 8자 -> 도넛과 같으나, 중간에 보내는 값과 받는 값이 두개인 친구가 있음
*/

vector<int> solution(vector<vector<int>> edges) {
    vector<int> answer(4, 0);
    int max_node = 0;
    
    for (auto v : edges) {
        max_node = max(max_node, v[0]);
        max_node = max(max_node, v[1]);
   }
    
    // 일단 간선 보면서 받는거, 보내는거 찾기, +1을 해주는 이유는 얘가 0번을 노드로 사용 안하기 떄문
    vector<vector<int>> receive(max_node + 1);
    vector<vector<int>> send(max_node + 1);
    
    // 간선 하나하나 넣기
    for (auto edge : edges) {
        send[edge[0]].push_back(edge[1]);
        receive[edge[1]].push_back(edge[0]);
    }
    
    // 이제 간선을 탐색하면서 하나도 받지 않으면서, 보내는게 2개 이상인 친구를 찾는다
    int send_node;
    for (int i = 1; i <= max_node; i++) {
        if (receive[i].size() == 0 && send[i].size() >= 2) {
            send_node = i;
            break;
        }
    }
    
    queue<int> que;
    // 새로 생긴 노드를 찾았다면, 이제 얘가 send하는 각각의 노드들이 어떤 도형인지 파악하면 된다
    for (auto target : send[send_node]) {
        
        // 만약, 이 노드에서 갈 길이 없다면 막대인 것이다.(막대 마지막 값이거나, n = 1인 막대이거나)
        if (send[target].size() == 0) {
            answer[2]++;
            continue;
        }
        
        // 각각 8자 혹은 도넛인지 파악하기 위한 플래그
        bool flag_8 = false;
        bool flag_donut = false;
        que.push(send[target][0]);
        
        // 이 노드에서 갈 수 있는 모든 노드를 탐색해 볼 것!
        while (!que.empty()) {
            int now = que.front();
            que.pop();
            
            // 중간에 두갈래길이 있다면 이건 8자
            if (send[now].size() == 2) {
                flag_8 = true;
                break;
            }
            
            // 나에게 다시 돌아왔다면 이건 도넛!
            if (now == target) {
                flag_donut = true;
                break;
            }
            
            // 더 갈 길이 없다면 막대이다
            if (send[now].size() == 0) break;
            
            // 갈 길이 있다면 계속 보낸다
            int next = send[now][0];
            que.push(next);
        }
        
        // 루프를 다 돌고 나왔을 때, flag에 따라 값을 더한다.
        if (flag_8) answer[3]++;
        else if (flag_donut) answer[1]++;
        else answer[2]++;
    }
    
    answer[0] = send_node;
    return answer;
}