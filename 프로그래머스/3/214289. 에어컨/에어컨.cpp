#include <cmath>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

/*
    실내공조 제어 시스템, 차내에 승객이 탑승하면 t1 ~ t2를 유지하게 한다
    실내, 희망이 다르면 1분 뒤 실내가 희망하는 방향으로 1도 상승 또는 하강한다.
    
    전원을 끄면 실내가 실외와 같아지는 방향으로 1도 상승 또는 하강
    소비전력은 실내온도에 따라 다름. 희망과 실내가 다르면 매분 전력 a 소모, 희망과 실내가 같다면 매 분 b 소모
    
    실내공조 제어 시스템은 차내 승객 탑승 중일 시 실내온도를 t1 ~ t2사이로 유지하면서, 소비전력을 최소화한다.
    차에 타기 전부터 미리 온도를 내리기 시작해야, 승객이 탔을 때 온도를 적절하게 설정해줄 수 있음.
    

    a, b를 생각해서 온도를 어디까지 내릴지 정해야 한다.
    1. 최저온도로 유지하기
    2. 내렸다가, 다시 올리기
    
    두 가지 경우를 고려해서, Greedy하게 선택해야 함
    
    혹은 DP? n시간에 A도인 경우의 최소 전력을 DP로 저장할 수 있음.
    1. 이전 시간에서 온도 1도 올리기/내리기
    2. 이전 시간에서 온도 유지하기
    3. 에어컨 끄기
*/
int solution(int temperature, int t1, int t2, int a, int b, vector<int> onboard) {
    int answer = 0;
    
    // 온도가 영하 10도까지 가능하므로, 이를 보정
    temperature += 10;
    t1 += 10;
    t2 += 10;
    
    vector<vector<int>> dp(onboard.size(), vector<int>(51, 1e9));
    
    // dp 초기화
    dp[0][temperature] = 0;
    
    // dp 진행
    for (int i = 0; i < onboard.size(); i++) {
        for (int j = 0; j < 51; j++) {
            // 현재 사람이 타고 있는데, 희망온도 내가 아닐 경우 지금의 dp값은 고려되면 안됨
            if (onboard[i] && (j < t1 || j > t2)) {
                dp[i][j] = 1e9;
                continue;
            }
            
            // 현재가 마지막 시간이라면, i + 1값 계산이 불가능하므로 아래의 계산은 수행하지 않음
            if (i == onboard.size() - 1) continue;
            
            // 1분 후에 현재온도에서 1도를 내릴 경우
            if (j > 0 && dp[i][j] + a < dp[i + 1][j - 1]) {
                dp[i + 1][j - 1] = dp[i][j] + a;
            }
            
            // 1분 후에 현재온도에서 1도를 올릴 경우
            if (j < 50 && dp[i][j] + a < dp[i + 1][j + 1]) {
                dp[i + 1][j + 1] = dp[i][j] + a;
            }
            
            // 1분 후에 현재온도에서 유지할 경우
            if (dp[i][j] + b < dp[i + 1][j]) {
                dp[i + 1][j] = dp[i][j] + b;
            }
            
            // 1분 후에 에어컨을 껐을 경우
            if (j < temperature) {
                // 현재온도가 실외온도보다 낮으면, 1도 올라간다
                if (dp[i][j] < dp[i + 1][j + 1]) {
                    dp[i + 1][j + 1] = dp[i][j];
                }
            } else if (j > temperature) {
                // 현재온도가 실외온도보다 높으면, 1도 내려간다
                if (dp[i][j] < dp[i + 1][j - 1]) {
                    dp[i + 1][j - 1] = dp[i][j];
                }
            } else {
                // 현재온도와 실외온도가 같으면, 유지된다
                if (dp[i][j] < dp[i + 1][j]) {
                    dp[i + 1][j] = dp[i][j];
                }
            }
        }
    }
    
    // dp 확인
    /*
    fo1r (int i = 0; i < onboard.size(); i++) {
        cout << i << "분" << endl;
        for (int j = 0; j < 51; j++) {
            if (dp[i][j] == 1e9) continue;
            cout << j - 10 << "도 : " << dp[i][j] << endl;
        }
        cout << endl << endl;
    }
    */
    
    // 마지막 시간대에서 제일 작은 값 가져오기
    answer = 1e9;
    for (int i = 0; i < 51; i++) {
        answer = answer > dp[onboard.size() - 1][i] ? dp[onboard.size() - 1][i] : answer;
    }
    
    return answer;
}