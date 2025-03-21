#include <string>
#include <vector>
#include <iostream>

using namespace std;

/*
    1번부터 N번까지 번호가 있다.
    경기는 1:1 이고, A가 B보다 강하면 항상 A는 B를 이긴다.
    
    심판은 경기 결과를 바탕으로 순위를 매기자! 근데 몇 경기가 분실되어서 정확하게 순위가 매겨지지 않는다.
    선수의 수, results가 주어지면 정확하게 순위가 매겨지는 선수의 수를 return하자
    
    각 선수별로 다른 선수와 매치 결과가 이겼는지, 졌는지를 기록한다.
*/

int solution(int n, vector<vector<int>> results) {
    int answer = 0;
    vector<vector<int>> win_lose(n, vector<int>(n, 0));
    
    // 이긴 사람, 진 사람을 체크한다.
    for (auto v : results) {
        int winner = v[0] - 1;
        int loser = v[1] - 1;
        
        win_lose[winner][loser] = 1;
        win_lose[loser][winner] = -1;
    }
    
    /*
    // 초기 플루이드마샬 출력
    for (auto v : win_lose) {
        for (auto v_ : v) cout << v_ << " ";
        cout << endl;
    }
    */
    
    // 이제, 플로이드 - 마샬을 실행한다.
    // i는 경유지, j는 출발지, k는 도착지이다
    for (int i = 0; i < n; i++) {
        // 지금 나를 이기거나 지는 모든 친구들을 확인한다
        for (int j = 0; j < n; j++) {
            if (j == i) continue;
            
            // 내가 지는 사람들은, 내가 이기는 사람들보다 모두 강하다.
            if (win_lose[i][j] == -1) {
                for (int k = 0; k < n; k++) {
                    if (i == k) continue;
                    if (win_lose[i][k] == 1) {
                        win_lose[j][k] = 1;
                    }
                }
            }
            
            // 나에게 지는 사람들은, 나를 이기는 사람들보다 모두 약하다
            else if (win_lose[i][j] == 1) {
                for (int k = 0; k < n; k++) {
                    if (i == k) continue;
                    if (win_lose[i][k] == -1) {
                        win_lose[j][k] = -1;
                    }
                }
            }
        }
    }
    /*
    // 완성된 플루이드마샬 출력
    for (auto v : win_lose) {
        for (auto v_ : v) cout << v_ << " ";
        cout << endl;
    }
    */
    
    // 이제, win_lose를 보면서 나머지 N명에 대한 값을 모두 가지는지 확인한다
    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = 0; j < n; j++) {
            if (win_lose[i][j] != 0) count++;    
        }
        
        if (count == n - 1) answer++;
    }
    return answer;
}