#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

/*
    unordered_map으로 나라별 갈 수 있는 곳 정리하기.
    그 후에 알파벳 순으로 정렬하고, 가면 됨
    
    그냥 가는게 아니었다!!!! 가능한 경로를 모두 탐색해야 함
*/

// 
/*
   BFS를 수행하고 결과를 반환하는 함수
   
   unordered_map<string, vector<pair<string, bool>>> routes -> 가능한 루트와 사용 여부 저장
   vector<string> tmp_answer -> 지금의 경로대로 실행했을 때의 결과
   int used_count -> 현재까지 사용한 티켓 갯수
   int target_count -> 목표 티켓 사용 갯수
   string nowLoc -> 현재 위치
   vector<string> answer -> 진짜 답안
*/
void DFS(unordered_map<string, vector<pair<string, bool>>> &routes, vector<string> &tmp_answer, int used_count, const int &target_count, string nowLoc, vector<string> &answer);

vector<string> solution(vector<vector<string>> tickets) {
    vector<string> answer;
    // 각 도시별로 항공권을 정리하되, 사용 여부를 bool과 함께 정리한다.
    unordered_map<string, vector<pair<string, bool>>> routes;
        
    for (auto v : tickets) {
        string arrival = v[0];
        string dest = v[1];
        
        // 아직 만들어지지 않았으면 만들기
        if (routes.find(arrival) == routes.end()) {
            routes.insert({arrival, vector<pair<string, bool>>()});
        }
        
        // 값 넣기
        routes[arrival].push_back({dest, false});
    }
    
    
    // 정렬하기
    for (auto it = routes.begin(); it != routes.end(); it++) {
        sort(it->second.begin(), it->second.end(), [](const pair<string, bool> &a, const pair<string, bool> &b) -> bool {
            return a.first < b.first;
        });
    }
    
    /*
    // 정렬 결과 확인하기
    for (auto it = routes.begin(); it != routes.end(); it++) {
        cout << it->first << "에서 갈 수 있는 도시 목록 : ";
        for (auto v : it->second) cout << v.first << " ";
        cout << endl;
    }
    */
    
    // ICN에서부터 출발한다
    string nowLoc = "ICN";
    vector<string> tmp_answer = {"ICN"};
    const int target_count = tickets.size();
    int used_count = 0;
    
    // DFS로 탐색한다
    DFS(routes, tmp_answer, used_count, target_count, nowLoc, answer);
    
    return answer;
}


void DFS(unordered_map<string, vector<pair<string, bool>>> &routes, vector<string> &tmp_answer, int used_count, const int &target_count, string nowLoc, vector<string> &answer) {
    // 모든 항공편을 다 사용하는 데에 성공했다면! 이제 answer와 tmp_answer를 비교한다.
    if (used_count == target_count) {
        // 일단, answer가 비어있다면 이걸로 대체한다
        if (answer.size() == 0) answer = tmp_answer;
        
        // 비어있지 않다면, 비교한 후 삽입한다.
        else if (tmp_answer < answer) answer = tmp_answer;
    }
    
    // 현재 위치에서 갈 수 있는 다음 위치들을 탐색한다.
    for (auto &ticket : routes[nowLoc]) {
        // 이미 사용된 티켓인지 확인하고, 그렇다면 다음 티켓을 본다
        if (ticket.second) continue;

        // 사용되지 않은 티켓이라면, 다음엔 거기로 가면 된다
        ticket.second = true;
        tmp_answer.push_back(ticket.first);
        
        DFS(routes, tmp_answer, used_count + 1, target_count, ticket.first, answer);
        
        // 함수 끝나면 다시 원상복귀
        ticket.second = false;
        tmp_answer.pop_back();
    }
}