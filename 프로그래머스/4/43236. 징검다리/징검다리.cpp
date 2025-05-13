#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

/*
    출발지에서 Distance만큼 떨어진 곳에 도착지가 있다.
    그 사이엔 바위들이 있다.
    
    바위를 좀 없애자. 바위를 없애서 각 지점 사이의 거리의 최솟값 중 가장 큰 값을 return하게 하자.
    그러니, 최소거리를 가장 최대화하자는 것
    
    바위는 총 50000개, 거리는 10^9이니 거리가 아니라 바위 가지고 해야 한다.
    
    최소거리를 priority_queue에 넣는다.
    그리고 값을 제거한다 (그 바위를 없앰)
    
    ChatGPT 활용 결과, 이진 탐색을 활용하라고 한다.
    그 근거는 다음과 같음
    1. 확실한 범위를 가진 수
    2. 각각의 값에 대한 성공, 실패 판별 가능
    3. 단조성(A가 성공한다면 A이하의 값은 모두 성공 가능)
    그래서 이진 탐색으로 범위를 빠르게 좁히며 탐색하면 된다.
    
    탐색하는 방법은 안 되는 바위 빼면서 찾기.
*/

using namespace std;

int solution(int distance, vector<int> rocks, int n) {
    int answer = 0;
    
    // 바위 정렬
    sort(rocks.begin(), rocks.end());
    
    // 바위 출력
    //// for (auto v : rocks) cout << v << " "; cout << endl;
    
    // 이진탐색을 위한 값
    int start = 1;
    int end = distance;
    
    // start가 end 이하일 동안만 하면 된다. 그 범위를 넘어가면 끝난 것
    while (start <= end) {
        int mid = (start + end) / 2;
        
        // 징검다리를 넘어가면서 체크한다
        int skippedCount = 0;
        int lastLoc = 0;
        
        //// cout << "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ" << endl;
        ////cout << "거리 " << mid << "로 잡고 탐색 시작" << endl;
        
        for (int i = 0; i < rocks.size(); i++) {
            // 이전 지점까지와의 거리
            int dist = rocks[i] - lastLoc;
            //// cout << "현재 돌의 위치 : " << rocks[i] << endl;
            
            // 근데 이게 안된다면, 이 돌은 빼야 한다
            if (dist < mid) {
                //// cout << rocks[i] << "의 위치값을 가지는 " << i << "번 돌 빠짐" << endl;
                skippedCount++;
            }
            
            // 빼지 않아도 된다면, 이 돌의 위치를 lastLoc으로 설정한다
            else {
                lastLoc = rocks[i];
            }
            
            // 마지막 돌이라면, 거기서부터 끝 지점까지도 체크해줘야 한다
            if (i == rocks.size() - 1) {
                dist = distance - lastLoc;
                
                if (dist < mid) skippedCount++;
            }
            
            // 가지치기용 중간종료
            if (skippedCount > n) break;
        }
        
        // 끝났다면, skippedCount를 세서 가능한지 확인한다.
        // 가능하다면, left를 수정하고 mid값을 answer로 준다
        if (skippedCount <= n) {
            //// cout << "가능, answer를 " << mid << "로 수정" << endl;
            answer = mid;
            start = mid + 1;
        }
        
        // 불가능하면, 그 아래 범위를 보러 간다.
        else {
            //// cout << "불가능, end를 " << mid - 1 << "로 수정" << endl;
            end = mid - 1;
        }
    }
    
    return answer;
}