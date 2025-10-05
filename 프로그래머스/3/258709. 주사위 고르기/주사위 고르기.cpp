#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

/*
    n개의 주사위로 쇼부
    주사위 6개 면에 각각 수가 하나씩 쓰여있다.
    
    각 면이 나올 확률은 모두 동일
    
    각 주사위는 1 ~ n의 번호를 가지며, 쓰인 수의 구성은 모두 다르다
    
    A가 먼저 절반의 주사위 챙겨가면, 나머지는 B가 가져간다.
    굴리고, 나머지를 모두 합해 점수 계산
    
    점수 큰 쪽이 승리한다.
    
    A는 승리 확률이 가장 높아지도록 주사위 가져갈 것
    
    A가 뽑은 주사위를 10C5 로 고른다.
    그 후 A가 뽑은 주사위를 6^5로 계산한 후, 각 경우의 합을 DP에 저장한다.
    
    dp[i] = A가 뽑은 주사위에서 i값이 나오는 경우의 수
    그 후 누적합으로 쭉 합쳐주면 된다. 그럼 "dp[i] = i이하가 나올 경우의 수의 합"으로 바뀐다.
    
    그리고 B주사위에서도 6^5해서 각 숫자가 얼마가 나오는지 확인하고, dp 기반으로 계산하면 된다.
    예를 들어 B주사위 3개의 합이 5가 나왔다면, dp[4]만큼은 이기는 것, 6^5 - dp[4] - dp[5] 만큼은 이긴다(같으면 비김)
    
    1 1 1
    1 2 3
    2 3 4
    
    0 1 2 3 4 5 6 7 8 9 10
    0 0 0 0 0 0 0 0 0 0 0
    
    0 3 0 0 0 0 0 0 0 0 0
    
    0 0 3 3 3 0 0 0 0 0 0
    0 0 0 0 3 3 3 0 0 0 0
    0 0 0 0 3 6 9 9 9 9 9
*/

using namespace std;

// 다이스 리스트 기반으로 값이 나오는 빈도 반환해주는 함수
vector<int> getFrequency(const vector<vector<int>> &dice, vector<int> diceList);

vector<int> solution(vector<vector<int>> dice) {
    vector<int> combination(dice.size(), 0);
    
    for (int i = dice.size() / 2; i < dice.size(); i++) {
        combination[i] = 1;
    }
    
    // 지금까지 나온 최고의 조합 계산용
    vector<int> bestComb;
    // 그 조합일 때 승리 횟수
    int bestWinCount = 0;
    
    do {
        int winCount = 0;

        // 일단 각자가 가져갈 주사위 리스트 만들기
        vector<int> aDiceList;
        vector<int> bDiceList;
        
        for (int i = 0; i < combination.size(); i++) {
            if (combination[i]) aDiceList.push_back(i);
            else bDiceList.push_back(i);
        }
        
        // A의 주사위 빈도 가져오기
        vector<int> aFrequency = getFrequency(dice, aDiceList);
        
        // B의 주사위 빈도 가져오기
        vector<int> bFrequency = getFrequency(dice, bDiceList);
        
        // B는 승/패 판별만 하므로 누적합으로 만들기
        for (int i = 1; i < bFrequency.size(); i++) bFrequency[i] += bFrequency[i-1];
        
        // A의 빈도, B의 누적합 기반으로 승리 횟수 계산하기
        for (int i = 1; i < aFrequency.size(); i++) {
            winCount += aFrequency[i] * bFrequency[i - 1];
        }
        
        // 승리 횟수가 더 크다면, 답 갱신
        if (bestWinCount < winCount) {
            bestWinCount = winCount;
            bestComb = aDiceList;
        }
        
    } while (next_permutation(combination.begin(), combination.end()));
    
    // 실제 주사위 idx는 1부터 시작하므로, 0부터 시작하는 값 변환해줘야 함
    for (auto &v : bestComb) v++;
    return bestComb;
}


vector<int> getFrequency(const vector<vector<int>> &dice, vector<int> diceList) {
    vector<int> frequency(501, 0);
    
    // 이제 각 다이스 모든 경우의 수 탐색해서 dp에 집어넣기
    int diceCount = diceList.size();
    vector<int> diceVal(diceCount, 0);
    int sum;
    while (true) {
        sum = 0;

        // 다이스 5개의 값 더해서 bSum만들기
        for (int i = 0; i < diceCount; i++) {
            sum += dice[diceList[i]][diceVal[i]];
        }

        frequency[sum]++;

        // 이제 다이스 값 다음으로 넘기기
        bool continueFlag = true;
        diceVal[diceCount - 1]++;
        for (int i = diceCount - 1; i >= 0; i--) {
            // 다이스 값이 5보다 커지면 그 앞 값 1 더하기
            if (diceVal[i] > 5) {
                // 5보다 커진 다이스 값이 첫 값이면, 순회 끝난 것이니 종료
                if (i == 0) {
                    continueFlag = false;
                    break;
                }
                // 아니라면, 그 앞 값 1 더해주기
                diceVal[i - 1]++;
                diceVal[i] -= 6;
            }
        }

        if (!continueFlag) break;
    }
    
    return frequency;
}