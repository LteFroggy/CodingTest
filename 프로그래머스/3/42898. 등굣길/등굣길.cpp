#include <string>
#include <vector>

using namespace std;

/*
      폭우가 와서 길이 잠겼다 헉
      집에서 학교까지는 격자모양으로 나타낸다.
      
      집은 1,1 학교는 m,n이다.
      
      오른쪽, 아래쪽으로만 움직여서 갈 수 있는 최단경로 개수를 100000007로 나눈 나머지 return하자.
      
      벡터 만든다. DP와 Bool로
      나에게로 올 수 있는 길은 나의 왼쪽, 나의 위쪽밖에 없으니 그걸 활용하면 됨
*/

int solution(int m, int n, vector<vector<int>> puddles) {
    
    vector<vector<int>> DP(n, vector<int>(m, 0));
    vector<vector<bool>> drowned(n, vector<bool>(m, false));
    
    DP[0][0] = 1;
    
    // 먼저 침수된 곳 확인
    for (auto v : puddles) 
        drowned[v[1] - 1][v[0] - 1] = true;
    
    
    // 모든 칸 DP로 확인한다. 값 기준은 0, 0이 집이고, m-1, n-1이 학교이다.
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            /* 침수구역이면 계산할 필요 없다 */
            if (drowned[i][j]) continue;
            
            /* 내 위에서 오는 값 계산한다 */
            // 0번째 열이면 생략함.
            if (i == 0) {}
            
            // 침수구역이어도 생략함
            else if (drowned[i - 1][j]) {}
            
            // 둘 다 아니라면 계산한다.
            else DP[i][j] += DP[i - 1][j];
            
            
            /* 내 왼쪽에서 오는 값을 계산한다 */
            // 0번째 행이면 생략함
            if (j == 0) {}
            // 침수구역이어도 생략함
            else if (drowned[i][j - 1]) {}
            // 둘 다 아니라면 계산한다.
            else DP[i][j] += DP[i][j - 1];
            
            /* 1000 000 007로 나눈다 */
            DP[i][j] %= 1000000007;
        }
    }
    
    
    return DP[n-1][m-1];
}