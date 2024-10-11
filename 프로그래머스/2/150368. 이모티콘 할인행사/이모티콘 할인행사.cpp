#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

/*
    이모티콘 플러스 가입자 수 늘리고, 판매액을 늘리고자 한다.
    
    가입자 늘리기가 제일 먼저임.
    
    n명의 이용자에게 m개의 이모티콘을 할인해서 판매한다.
    이모티콘마다 할인율은 다를 수 있고, 10 ~ 40%중 하나로 설정된다.
    
    1. 각 사용자들은 기준에 따라 일정 비율 이상 할인하는 이모티콘을 모두 산다
    2. 자신의 기준에 따라 이모티콘 구매 비용의 합이 일정 이상이 되면, 이모티콘 플러스에 가입한다.

    input : 사용자, 비율, 가격
    
    비율 이상 할인하는 이모티콘은 사고, 그러다 가격 이상이 되면 플러스에 가입한다.
    행사 목적을 최대한으로 달성했을 때의 이모티콘 플러스 가입 수와 이모티콘 매출액을 1차원 배열에 담아 return
    
    사용자 최대 100명
    이모티콘 최대 7개
    할인은 10 ~ 40%로 4개
    
    모두 체크하면 4^7 * 100으로 문제는 없다.
    따라서 각 할인에 따른 최대값을 저장하자.
*/

// 모든 경우를 체크하면서 행사 목적 최대치를 저장한다.
/*
    user는 사용자 정보
    emoticons는 이모티콘 정보
    index는 몇 번쨰 이모티콘인지
    discount는 이모티콘별로 얼마의 할인을 적용했는지
    answer에는 이모티콘 플러스 가입자수와 그 때의 수익을 저장한다.
*/

using namespace std;

void backTrack(const vector<vector<int>> &users, const vector<int> &emoticons, int index, vector<int> &discount, vector<int> &answer) {
    // 모든 이모티콘의 할인을 적용했다면, 그 때의 가입자 수와 수익을 저장한다
    if (index == emoticons.size()) {
        vector<int> buy_amount(users.size(), 0);
        
        // 이모티콘 하나당 할인율을 보면서 구매자를 찾는다.
        for (int i = 0; i < emoticons.size(); i++) {
            int price_discounted = emoticons[i] - (emoticons[i] * discount[i] /100);
            for (int j = 0; j < users.size(); j++) {
                // 이 유저가 이 상품을 사는지 체크한다.
                if (discount[i] >= users[j][0]) {
                    buy_amount[j] += price_discounted;
                }
            }
        }
        
        // 구매자를 모두 찾았다면, 이모티콘 플러스 가입자 및 수익을 체크한다.
        int plus_member = 0;
        int profit = 0;
        for (int i = 0; i < users.size(); i++) {
            // 이모티콘 플러스에 가입할 것인가?
            if (buy_amount[i] >= users[i][1]) plus_member++;
            else profit += buy_amount[i];
        }
        
        // 최대라면 갱신한다.
        if (answer[0] < plus_member) {
            answer[0] = plus_member;
            answer[1] = profit;
        } else if (answer[0] == plus_member && answer[1] < profit) {
            answer[1] = profit;
        }
        
        
        return;
    }
    
    // 아직 할인을 덜 적용했다면, 할인율을 적용한다
    for (int i = 1; i <= 4; i++) {
        // 10% ~ 40%까지 적용 후 backtrack 해보기
        discount[index] = i * 10;
        backTrack(users, emoticons, index + 1, discount, answer);
        discount[index] = 0;
    }
}

vector<int> solution(vector<vector<int>> users, vector<int> emoticons) {
    vector<int> answer(2, 0);
    vector<int> discount(emoticons.size(), 0);
    
    backTrack(users, emoticons, 0, discount, answer);
    
    return answer;
}