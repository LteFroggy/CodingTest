#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

/*
    네트워크의 개수를 return하자.
    
    하나 잡고, 갈 수 있는 이어진 값들을 모두 탐색하면서 하나의 네트워크로 이어주면 된다.
    탐색 회수별로 1개의 네트워크가 된다.
*/

int solution(int n, vector<vector<int>> computers) {
    int answer = 0;
    
    vector<bool> visited(n, false);
    vector<vector<int>> connected(n);
    queue<int> que;
    
    // 각 값을 보면서 이어진 모든 길을 탐색한다
    for (int i = 0; i < n; i++) {
        // 만약 지금 본 값이 이미 다른 곳에서 확인한 값이면 볼 필요 없음
        if (visited[i]) continue;
        
        // 아니라면, 큐에 넣어주고 탐색 시작한다.
        que.push(i);
        visited[i] = true;
        answer++;
        /// cout << i << "에서 " << answer << "로 값 증가" << endl;
        
        while (!que.empty()) {
            // 일단, 지금 꺼낸 값이 갈 수 있는 모든 위치를 큐에 넣는다
            int now_loc = que.front();
            que.pop();
            /// cout << i << "에서 시작해서 " << now_loc << "탐색 중" << endl;
            
            for (int j = 0; j < n; j++) {
                // 일단 이어져있는지 확인한다
                if (computers[now_loc][j] != 1) continue;
                if (visited[j]) continue;
                
                // 이어져있고, 방문한적도 없다면 방문해본다.
                que.push(j);
                visited[j] = true;
            }
        }
    }
    
    return answer;
}