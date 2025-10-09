#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

/*
    1 ~ n사이의 수가 적힌 카드 하나씩 있는 카드 뭉치
    coin개의 코인
    
    카드 뽑는 순서 있다.
    
    1. 처음엔 n/3장 뽑아 가진다.
    2. 각 라운드 시작 시에 카드 두 장 뽑기. 남은 카드가 없다면 게임 종료. 뽑은 카드는 카드 한장당 동전 하나 사용해 가지거나, 버릴 수 있다.
    3. 카드에 적힌 수의 합이 n+1이 되도록 카드 두 장을 내고 다음 라운드로 진행 가능. 카드 두 장을 못 내면 게임 종료
    
    최대 라운드 수를 계산해보자.
    
    라운드를 진행하려면 필요한 카드만을 사용해야 한다.
    최대 사용 가능한 카드는 앞의 n/3개를 제외하고 coin개.
    
    합이 n이 되는 두 값을 쉽게 잡을 수 있어야 한다.
    매 턴 앞에서 2개씩만 사용한다. 그러니 앞의 2개씩만 볼 수 있음.
    
    이 카드를 당장 안 쓰는게 후에 더 큰 이득이 될 수도 있다고 함. 완탐해보자.
*/

int solution(int coin, vector<int> cards) {
    int answer = 0;
    int n = cards.size();
    
    // 카드를 어디까지 받았는지 표현
    int cardIndex = n / 3;
    
    // 처음에 가진 카드 목록
    vector<int> initial(n + 1, 0);
    
    // 코인을 지불하면 가질 수 있는 카드 목록
    vector<int> affordable(n + 1, 0);
    
    // 아직 확인하지 않은 새 카드 목록
    unordered_map<int, int> newCards;
    
    // 앞으로 더 진행 가능한 라운드 수
    // 처음 한 라운드는 일단 진행 가능
    int leftCardPairs = 1;
    
    // 일단, 초반 n/3장의 카드를 가질 수 있다. 거기까진 미리 받아서 저장해두기
    for (int i = 0; i < cardIndex; i++) {
        int cardVal = cards[i];
        int needVal = (n + 1) - cardVal;
        
        // 카드를 새로 받을 때, 합쳐서 목표값이 나오는 수가 있다면 바로 사용한다.
        if (initial[needVal]) {
            initial[needVal]--;
            leftCardPairs++;
        }
        
        else {
            initial[cardVal]++;
        }
    }
    
    // 현재 남은 라운드 기준으로 내가 얻을 수 있는 카드를 쭉 본다.
    while (leftCardPairs) {
        // 어디까지 카드를 볼 수 있는지 계산
        int newCardIndex = cardIndex + (2 * leftCardPairs);
        answer += leftCardPairs;
        leftCardPairs = 0;
        
        // 이미 카드를 다 볼 수 있다면, 최대 라운드에 도달한 것이므로 라운드 최대값을 반환
        if (newCardIndex > n) {
            return (n / 3) + 1;
        }
        
        // 일단 받을 수 있는 숫자 리스트를 저장한다
        for (int i = cardIndex; i < newCardIndex; i++) {
            newCards[cards[i]]++;
        }
        
        cardIndex = newCardIndex;
        
        // 코인이 하나도 없으면 여기서 종료
        if (!coin) break;
        
        // 받을 수 있는 숫자 리스트를 보면서 손패에 사용 가능한 값이 있는지 확인
        for (auto iter = newCards.begin(); iter != newCards.end();) {
            int cardVal = iter->first;
            int needVal = (n + 1) - cardVal;
            
            // 이미 필요한 카드가 있다면, 사용
            if (initial[needVal] && coin) {
                initial[needVal]--;
                coin--;
                leftCardPairs++;
                
                // 만약 숫자를 다 썼으면 삭제
                if (iter->second == 1) {
                    iter = newCards.erase(iter);
                    continue;
                }
                
                // 아니라면 1 빼기만
                else {
                    (iter->second)--;
                }
            }
            
            iter++;
        }
        
        // 코인을 1개만 사용해서 짝이 이루어진 것이 있었다면, 추가 탐색 수행
        if (leftCardPairs) continue;
        
        // 코인 2개가 없다면, 여기서 종료
        if (coin < 2) break;
            
        // 코인 2개를 사용해 두 카드를 사야만 하는 상황이 온다면, 아래의 코드 실행
        for (auto iter = newCards.begin(); iter != newCards.end();) {
            int cardVal = iter->first;
            int needVal = (n + 1) - cardVal;
            
            // 필요한 값이 존재한다면, 구매
            if (affordable[needVal] && coin > 1) {
                affordable[needVal]--;
                coin -= 2;
                leftCardPairs++;
                
                // 추가 카드를 볼 수 있다면, 바로 보러가기
                break;
            }
            
            // 필요한 값이 없다면, 구매 가능에 추가
            else {
                affordable[cardVal]++;
            }
            
            // 값 삭제 처리
            if (iter->second == 1) {
                iter = newCards.erase(iter);
                continue;
            }

            else {
                (iter->second)--;
                iter++;
            }
            
        }
    }
    
    
    return answer;
}