#include <iostream>
#include <vector>
using namespace std;

/*  
    원형 스티커에서 몇 장의 스티커를 뜯어내어 뜯어낸 스티커의 숫자의 합이 최대가 하도록 하고 싶다.
    단, 스티커 한 장을 뜯어내면 양쪽 인접한 스티커는 찢어져서 사용이 불가능해진다.
    숫자가 배열 형태로 주어질때, 뜯어내어 얻을 수 있는 숫자의 합의 최대값을 return 해라.
    
    한 값을 떼어냈을 때 양 옆의 값은 사라진다. 따라서 인접한 두 값을 모두 사용할 수는 없다.
    그럼 A B C D가 있을때 어떻게 해야 최대 값을 뜯을까?
    어떤 한 값을 뜯으면 그 뒤의 값이 사용 불가능하게 된다.
    그럼에도 뒤의 값을 뜯어야 하는 상황은??
    A, C를 뜯으면 B, D가 사용 불가능해진다.
    그렇다고 B, D를 뜯으면 A, C, E가 사용 불가능해진다.
    
    항상 홀수번째만을 뜯어내는가, 짝수번째만을 뜯어내는가로 답이 나오나??
    안나온다.
    
    일단, 첫번째 값을 쓰냐 안쓰냐가 중요하다. 첫번째 값을 쓰면 마지막 값이 사라짐
    그래서 두 번 확인해야 할 듯
    
    1. 첫번째 값을 사용했을 경우
    14 6  5  11 3  9  2
    14 6  19 25 22 34 24 
    
    2. 첫번째 값을 사용하지 않을 경우
    6  5  11 3  9  2  10
    6  5  17 9  26 11 36
    
    둘 중 큰 값을 쓴다. DP 느낌으로
*/

int solution(vector<int> sticker)
{
    int answer = 0;
    // 첫 값을 사용할 경우와 사용하지 않을 경우를 나누어서 3개의 값을 미리 세팅해둔다 (DP[i] = max(DP[i-2], DP[i-3]) + sticker[i]) 로 구성할 것이기 때문.
    vector<int> DP_useFirst(sticker.size(), 0);
    DP_useFirst[0] = sticker[0];
    DP_useFirst[1] = sticker[1];
    DP_useFirst[2] = DP_useFirst[0] + sticker[2];
    
    // 첫 값을 사용하지 않는 경우에는 첫 값은 0으로 세팅한다.
    vector<int> DP_noUseFirst(sticker.size(), 0);
    DP_noUseFirst[0] = 0;
    DP_noUseFirst[1] = sticker[1];
    DP_noUseFirst[2] = sticker[2];
    
    
    
    
    // 두 경우가 존재한다. 1번째 값을 사용했을 경우와 사용하지 않았을 경우
    for (int i = 3; i < sticker.size(); i++) {
        // i가 마지막 값이 아닌 경우에는, 본인 - 2와 본인 - 3값을 보고 더 큰 값을 적용해 사용하면 된다.
        if (i != sticker.size() - 1) {
            DP_useFirst[i] = max(DP_useFirst[i - 2], DP_useFirst[i - 3]) + sticker[i];
            DP_noUseFirst[i] = max(DP_noUseFirst[i - 2], DP_noUseFirst[i - 3]) + sticker[i];
        }
        
        // 마지막 값이라면, 첫 값을 사용한 친구는 마지막 값이 뜯어져 나갈 것이니 사용이 불가능하다! 따라서 이를 적용해줘야 함
        else {
            DP_useFirst[i] = max(DP_useFirst[i - 2], DP_useFirst[i - 3]);
            DP_noUseFirst[i] = max(DP_noUseFirst[i - 2], DP_noUseFirst[i - 3]) + sticker[i];
        }
    }
    
    // for문이 끝나면, 각 DP의 마지막 두 값중 큰 값을 각각 고르고, 그 둘중 더 큰 값을 return한다.
    int useFirst_max = max(DP_useFirst[sticker.size() - 1], DP_useFirst[sticker.size() - 2]);
    int noUseFirst_max = max(DP_noUseFirst[sticker.size() - 1], DP_noUseFirst[sticker.size() - 2]);
    
    
    return max(useFirst_max, noUseFirst_max);
}