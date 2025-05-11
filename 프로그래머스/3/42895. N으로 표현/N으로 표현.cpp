#include <string>
#include <vector>
#include <set>


using namespace std;

/*
    5와 사칙연산으로 값을 표현하자.
    가장 적은 5를 사용하면 됨
    
    주어진 숫자 N과 number가 주어지면, 숫자 사용 횟수를 최소화하도록 작성하기
    
    근데 내가 꼭 모든 값을 다 봐야 하나? 그냥 최대한 주어진 값으로 다가가도록 하면 안되나?
    근데 최소 횟수를 따지기 위해서는 모든 횟수를 보는 것이 필요하긴 하다.
    
    아니다. i번 사용해서 만들 수 있는 모든 값들을 처리하면 되는 거였음...............
    
    dp[1] ~ dp[8]까지 기본값은 다 넣어준다 (ex : 5, 55, 555 ...)
    dp[i]를 만드는 방법은 dp[i - j] (사칙연산) dp[j] 이다.
*/

int solution(int N, int number) {   
    // dp는 최대 8까지, 그 안에 만들지 못하면 -1을 리턴한다.
    vector<set<long>> dp(9);
    
    // 기본값들 넣기
    for (int i = 1; i <= 8; i++) {
        string str(i, N + '0');
        // 만약 기본값이 답이라면, 바로 값을 돌려주면 됨
        if (stoi(str) == number) return i;
        dp[i].insert(stoi(str));
    }
    
    // 이제, 찾기
    for (int i = 2; i <= 8; i++) {
        for (int j = 1; j < i; j++) {
            
            // 모든 값들 기반으로 탐색한다.
            for (auto num1 : dp[i - j]) {
                for (auto num2 : dp[j]) {
                    // 더하기, 빼기, 곱하기, 나누기 수행
                    long sum = num1 + num2;
                    if (sum == number) return i;
                    else dp[i].insert(sum);
                    
                    long sub = num1 - num2;
                    if (sub == number) return i;
                    else dp[i].insert(sub);
                    
                    long mul = num1 * num2;
                    if (mul == number) return i;
                    else dp[i].insert(mul);
                    
                    if (num2 != 0) {
                        long div = num1 / num2;
                        if (div == number) return i;
                        else dp[i].insert(div);
                    }  
                }
            }
        }
    }
    
    // 8까지 다 봤는데도 안 걸리면, -1 돌려주기
    return -1;
}