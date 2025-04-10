#include <vector>

/*
    제이지는 시내 중심가의 경로 탐색 알고리즘을 개발한다.
    
    도시 중심가의 지도는 m * n 사이즈의 격자 배열 city_map이다.
    자동차는 오른쪽 혹은 아래로 한 칸씩 이동 가능하다.
    
    city_map이 0이면 자동차 자유롭게 통행 가능하다.
    1이면 자동차 통행이 금지다
    2면 보행자 안전을 위해 회전이 금지다.
    
    자동차로 이동 가능한 전체 경로 수를 출력하자
    20170805로 나눠서 표현하기.
*/

using namespace std;

int MOD = 20170805;

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
int solution(int m, int n, vector<vector<int>> city_map) {
    int answer = 0;
    
    // 방향이 두 개이다. 따라서 아래로 보낼 수 있는 갯수와 오른쪽으로 보낼 수 있는 값을 나눠줘야 한다.
    vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(2, 0)));
    
    // dp로 처리하기. 처음 값은 항상 아래, 오른쪽으로 다 하나씩 보낼 수 있다
    dp[0][0][0] = 1;
    dp[0][0][1] = 1;
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            // 첫 노드는 설정해줬으므로 계산 필요 없음
            if (i == 0 && j == 0) continue;
            
            // 현재 도로가 자유롭게 통행이 가능한 경우
            if (city_map[i][j] == 0) {
                // 통행량 먼저 저장
                int val = 0;
                if (i > 0) val += dp[i - 1][j][0];
                if (j > 0) val += dp[i][j - 1][1];
                
                val %= MOD;
                
                // 이걸 양쪽으로 모두 보내줄 수 있음
                dp[i][j][0] = val;
                dp[i][j][1] = val;
            }
            
            // 통행금지면, 보낼 수 없음
            else if (city_map[i][j] == 1) {
                dp[i][j][0] = 0;
                dp[i][j][1] = 0;
            } 
            
            // 회전이 금지되면, 값을 그대로 써야 함
            else if (city_map[i][j] == 2) {
                if (i > 0) dp[i][j][0] = dp[i-1][j][0];
                else dp[i][j][0] = 0;
                
                if (j > 0) dp[i][j][1] = dp[i][j-1][1];
                else dp[i][j][1] = 0;
            }
        }
    }
    
    // 마지막 값 꺼내기
    answer = dp[m-1][n-1][0];
    
    return answer;
}