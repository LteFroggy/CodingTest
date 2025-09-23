#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
    서로 다른 정수 5개가 오름차순으로 정렬됨
    
    m번 시도 가능, 서로 다른 5개의 정수 입력하면 시스템은 몇 개가 비밀에 포함되어있는지 알려준다.
    
    m번 시도 후, 비밀 코드로 가능한 정수 조합의 개수를 알고자 한다.
    
    각 숫자가 몇 번 코드에 포함되는지 확인한다.
    만약 그 숫자를 정답으로 지목했다면, 5가 되는지 확인하면 됨
    범위는 1 ~ 10.
    사실상 30C5이다. 
    
    next_permutation으로 1 1 1 1 1 0 0 0 0 0 을 돌리면 됨
    보면서 가능한 경우 값 더해주기
*/

int solution(int n, vector<vector<int>> q, vector<int> ans) {
    int answer = 0;
    
    // 각 값이 q에 등장했는지 저장하기 위한 2차원 배열
    vector<vector<bool>> q_summary(n, vector<bool>(q.size(), false));
    
    // q를 보면서 정리한다.
    for (int i = 0; i < q.size(); i++) {
        for (auto val : q[i]) {
            // 실제 값은 1 ~ 30이나, 0 ~ 29를 사용할 것이므로 1 뺴서 저장
            q_summary[val - 1][i] = true;
        }
    }
    
    vector<int> now(n, 1);
    for (int i = 0; i < 5; i++) now[i] = 0;
    
    // 한 경우씩 가정해가면서 가능한지 체크하기
    do {
        // now값을 기반으로 이 경우는 가능한지 체크한다.
        vector<int> tmp_ans(q.size(), 0);
        for (int i = 0; i < n; i++) {
            // 현재 값이 비밀 코드에 포함되지 않았다면 스킵
            if (now[i] == 1) {
                continue;
            }
            
            // 비밀 코드에 포함되는 값이라면, q.size()까지 다 보면서 tmp_ans에 더한다.
            for (int j = 0; j < q.size(); j++) {
                // i값이 j번째 질문에 포함되어있으면, tmp_ans에 1 더하기
                if (q_summary[i][j])
                    tmp_ans[j]++;
            }
        }
        
        // tmp_ans와 실제 ans를 비교한다.
        if (tmp_ans == ans) {
            // 같다면, 결과 출력과 answer++:
            answer++;
            
            /*
            cout << "답안 발견 : ";
            for (int i = 0; i < now.size(); i++) {
                if (now[i] == 0) cout << i + 1 << " ";
            }
            cout << endl;
            */
        }
    } while (next_permutation(now.begin(), now.end()));
    
    
    return answer;
}