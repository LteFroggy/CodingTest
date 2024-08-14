#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*
    1 ~ N까지 차례로 번호가 붙은 바구니 N개가 일렬로 있다
    A ~ B까지 더하고, B + 1 ~ C까지 더하는데, 둘의 값은 같아야 한다
    가장 큰 값을 구하자.
    
    

    중간값을 하나씩 정하고, 늘려가는 방법을 선택한다.    
*/

int solution(vector<int> cookie) {
    int answer = 0;
    int N = cookie.size();
    
    
    for (int i = 0; i < N-1; i++) {
        int left = i;
        int right = i+1;
        
        int lCookies = cookie[left];
        int rCookies = cookie[right];
        
        while (left >= 0 && right < N) {
            if (lCookies == rCookies) {
                answer = max(answer, lCookies);
            }
            
            if (lCookies < rCookies) {
                left--;
                lCookies += cookie[left];
            }
            
            else {
                right++;
                rCookies += cookie[right];
            }
        }
    }
    
    return answer;
}