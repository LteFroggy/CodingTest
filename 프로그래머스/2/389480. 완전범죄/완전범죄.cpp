#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
    A와 B는 훔친다
    I를 훔칠 때 [i][0]개의 흔적
    B는 [i][1]개의 흔적
    
    1 ~ 3개 사이
    
    A는 N개 이상이면 붇잡힌다
    B는 m개 이상 붙잡힌다.
    
    둘 모두 붙잡히지 않도록 훔칠 때, A가 남긴 최소값을 Return 하자.
    어떠한 방법으로도 안되면, -1
    
    일단 전부 B가 훔친다.
    그리고 A가 훔치거나, 훔치지 않거나
    
    효율적인 것부터 A한테 넘겨야 한다. B의 무게를 제일 많이 덜어주면서 A에게 부담을 덜 주는 것으로
*/

int INITIAL_VALUE = 1e9;

bool comp_std(vector<int> a, vector<int> b) {
    float a_eff = float(a[1]) / float(a[0]);
    float b_eff = float(b[1]) / float(b[0]);
    
    if (a_eff > b_eff) return true;
    else if (a_eff == b_eff) return a[0] < b[0];
    else return false;
}

int solution(vector<vector<int>> info, int n, int m) {
    int answer = 0;
    
    sort(info.begin(), info.end(), comp_std);
    
    // 정렬 결과 확인
    /**
    for (auto v : info) {
        cout << v[0] << ", " << v[1] << endl;
    }
    **/
    
    // 일단 B에 모두 넣기
    int a_sum(0), b_sum(0);
    for (auto v : info) {
        b_sum += v[1];
    }
    
    int idx = 0;
    
    // 기본 DP 초기화.
    /*
        DP[i]는 A가 i번째룰 훔쳤을 때의 B의 흔적 개수를 말한다.
        우리의 목표는 DP[i]의 값이 m보다 작은 최소의 i값을 찾는 것이다.
        
        초기값은 전부 -1로 세팅하고, DP[0] = b_sum으로 설정해둔 다음 시작한다
    */
    vector<int> dp(n + 3, INITIAL_VALUE);
    // 처음엔 B가 모두 들고 있다고 가정
    dp[0] = b_sum;
    
    // 물건을 하나씩 보면서 들어보기 해주기.
    for (auto v : info) {
        for (int i = n - 1; i >= 0; i--) {
            int a_clue = v[0];
            int b_clue = v[1];
            
            // 만약 무게가 초기 설정값 그대로면, 아직 가본 적이 없는 값이므로 수정하지 않기
            if (dp[i] == INITIAL_VALUE) continue;
            
            // 들어본 무게라면, 지금 이 짐을 들어주는 게 최대 효율인지 판단하고 최대 효율일 경우 저장하기
            if (dp[i + a_clue] > dp[i] - b_clue) {
                dp[i + a_clue] = dp[i] - b_clue;
            }
        }
    }
    
    // n이하의 값까지만 보면서 쭉 찾기. 어차피 넘어가면 의미 없음
    for (int i = 0; i < n; i++) {
        if (dp[i] < m) return i;
    }
    
    return -1;
}