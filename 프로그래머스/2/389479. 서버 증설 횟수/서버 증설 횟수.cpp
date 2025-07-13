#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

/*
    게임 이용자가 m명 늘어나면, 서버 1대가 추가로 필요하다,
    이요자가 m명 미만이면, 증설 필요 없다.
    
    한 서버는 k시간동안 운영하고, 반납한다.
    
    모든 이용자가 게임을 이용하기 위해 몇 번 서버를 증설해야 할까??
*/

int solution(vector<int> players, int m, int k) {
    int answer = 0;
    
    // 서버는 기본적으로 1대가 있고, 추가되면 큐에 집어넣는다
    // 큐에 집어넣는 이유는, 먼저 들어간 서버가 먼저 끝나기 때문
    queue<int> que;
    
    for (int i = 0; i < players.size(); i++) {
        // 대여시간이 만료된 서버가 있는지 확인한다
        while (!que.empty() && que.front() < i) {
            que.pop();
        }
        
        // 만료된 서버 제하고 현재 남은 서버 갯수 확인한다. 1개는 기본으로 있음
        int serverCount = que.size() + 1;
        
        /// cout << "현재 시간 : " << i << ", 서버 갯수 : " << serverCount << endl;
        
        // 지금 존재하는 서버로 인원 수용이 가능한지 확인한다
        int possiblePlayerCount = (serverCount * m) - 1;
        int leftPlayers = players[i] - possiblePlayerCount;
        
       /// cout << "추가로 수용해야 할 플레이어 인원수 : " << leftPlayers << endl;
        
        // 모든 플레이어 수용이 불가능하다면?
        if (leftPlayers > 0) {
            // 모든 플레이어 수용 가능할때까지 서버 늘리기
            while (leftPlayers > 0) {
                // 서버 만료시간 설정
                que.push(i + k - 1);
                leftPlayers -= m;
                answer++;
            }
        }
    }
    
    return answer;
}