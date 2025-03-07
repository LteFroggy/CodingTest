#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
    마나커 알고리즘 사용하자
    먼저 사이사이에 #을 넣는다. 넣는 이유는?? 마니커 알고리즘은 항상 양쪽으로 뻗어가는 방식으로 회문을 체크하는데, 그럼 짝수 개의 회문을 체크하지 못하기 때문이다.
    
    mid는 지금까지 발견된 가장 마지막까지 가는 회문의 중심점, last는 발견된 회문 중 가장 마지막 점이다
    last는 따라서 현재 위치(i) + 회문의 길이(P[i]) 가 last보다 커지는 경우에 변화한다.
    mid는 last의 변화에 따라서 변화된다.
    
    현재 회문의 최대 길이 P[i]는 last < i인 경우 0에서 시작하고, last >= i인 경우 min(P[2c - i], r - i)에서 시작한다.
    이게 무슨 의미냐? 이전 회문에 포함되어있는 값인 경우, 나의 대칭ㄹ인 반대쪽(2c - 1)혹은 r - i(현재 찾아져있는 회문의 경계점)중 더 작은 값을 택해야 한다는 것
    
    왜냐? 일단 대칭점은 이해가 된다. 반대쪽에서 이미 가능한지 검사한 회문이 있는데, 그걸 그대로 받아 쓰면 된다. 괜히 내가 또 검사해 볼 필요는 없음
    근데 만약, 대칭점의 회문도 꽤 커서 그 범위를 그대로 적용했을 때 이미 찾은 가장 큰 회문보다 더 멀리 가게 될 수도 있다.
    근데, 더 멀리 가게 되면 그쪽은 내가 확실한지 검사를 해보지 않은 영역이므로, 직접 검사하도록 하는 것.
    
        # a # b # a # c # d # e #
P[i]    0
mid     0 
last    0 
i = 0
첫 값은 앙 옆으로 회문이 생기지 않으니, p[0] = 0, mid, last역시 0으로 기본값이다.

        # a # b # a # c # d # e #
P[i]    0 1
mid     0 1
last    0 2
i = 1
a는 양쪽에 #이 있어서 P[i] = 1이 된다! 그럼 last = P[1] + 1 = 2이므로 갱신되고, mid도 1로 갱신된다.

        # a # b # a # c # d # e #
P[i]    0 1 0
mid     0 1 1
last    0 2 2
i = 2
i == last이므로 직접 양쪽을 봐야 한다. a#b이므로, P[i] = 0이다.
last는 갱신되지 않는다

        # a # b # a # c # d # e #
P[i]    0 1 0 3
mid     0 1 1 3
last    0 2 2 6
i = 3
b가 먼저 자신의 양쪽을 탐색한다. #a#b#a#이다! 무려 양 옆으로 3개나 됨
그럼 last는 P[i] + i = 6으로 갱신된다. 기존 Last는 2였으므로 갱신되어야 함
이 때 mid는 i로 갱신! 따라서 mid = 3, last = 6이다

        # a # b # a # c # d # e #
P[i]    0 1 0 3
mid     0 1 1 3
last    0 2 2 6
i = 4
드디어 처음으로 i <= last이다. 이 경우에는 i가 회문 영역 내부에 포함되어 있는 상황이다. 따라서 반대쪽의 값을 이용하면 된다! 이용하는 방법은
min(P[mid * 2 - i], last - i)를 사용하면 된다. P[mid * 2 - i]는 mid를 기준으로 대칭점에 있는 나의 값이고, r - i는 현재 탐색중인 
위치에서 이미 발견한 회문 끝까지의 거리이다. 더 작은 값을 사용하면 되는 이유는, 대칭점에 있는 내 값이 이미 찾은 회문의 범위를 넘어가게 되는 경우,
거기서부터는 내가 직접 확인해보도록 하기 위함이다. 지금은 #a#b#a#에서 #의 대칭점에 있는 #의 값이 0이므로 P[0]으로 시작하고, 탐색을 직접 해보면 된다
마나커 알고리즘의 핵심은 P[0]부터 일일히 탐색하지 않고, 앞의 P값을 이용할 수 있도록 한다는 것이다.
*/


int solution(string s)
{
    int answer = 0;
    // s의 사이사이에 #을 넣는다.
    string newStr("");
    for (auto v : s) {
        newStr += "#";
        newStr += v;
    }
    newStr += "#";
    
    cout << newStr << endl;

    // 일단 필요한 값을 세팅한다
    int mid(0);
    int last(0);
    vector<int> dp(newStr.length(), 0);
        
    // 이제 각 값을 본다
    for (int i = 0; i < newStr.length(); i++) {
        int move_idx;
        // 현재 내 자리가 회문 범위 내에 있는지 체크한다
        // 회문 범위 내가 아니라면, 바로 옆부터 체크해야한다
        if (last < i) {
            move_idx = 0;
        }
        
        // 회문 범위 내라면, 그 정보를 활용할 수 있다.
        else {
            move_idx = min(last - i, dp[mid * 2 - i]);
        }
        
        // 이제 내 양옆을 비교한다.
        while ((i - ++move_idx) >= 0 && (i + move_idx) < newStr.length() && newStr[i - move_idx] == newStr[i + move_idx]) {}
         
        // 마지막에는 두개가 동일하지 않거나, 범위를 벗어나서 반복문을 빠져나왔을 것이므로, 1을 빼줘야만 진짜 동일한 위치까지가 나온다.
        move_idx--;
        
        dp[i] = move_idx;
        // last의 갱신 조건에 해당하는지 확인한다
        if (dp[i] + i > last) {
            last = dp[i] + i;
            mid = i;
        }
    }
    
    // 이러면 각 자리에서 가장 긴 회문을 모두 찾은 것이다! 가장 큰 dp값을 답으로 반환한다
    for (auto v : dp) {
        if (answer < v) answer = v;
    }

    return answer;
}