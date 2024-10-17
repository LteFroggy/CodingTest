#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

/*  
    n개의 집에 택배를 배달할 것!
    모두 크기가 같은 재활용 상자에 담아 배달하고, 다니면서 이 상자들을 수거한다.
    
    배달할 것들은 물류창고에 있고, 모든 집 사이의 거리는 1이다.
    
    트럭에는 재활용 상자 cap개 실을 수 있다. 배달할 상자를 실어서 물류창고에서 출발해 각 집에 배달하며, 빈 상자들은 수거해서 물류창고에 내린다.
    각 집마다 가야 할 택배 상자 개수와 수거할 개수를 알고 있을때, 트럭 하나로 모든 배달 및 수거를 마치고 돌아올 수 있는 최소 이동 거리는?
    
    실을 수 있는 개수는 50개, 집은 최대 100,000개. 모두 고려하기에는 좀 많아 보인다.
    
    최대한 적은 거리를 이동하기 위해서는, 멀리까지 가는 횟수를 최소화해야 한다. 뭘 생각할 이유가 있나? 그냥 가면서 최대한 많이 떨구고, 올때 최대한 많이 가져오자!
    
    가면서 제일 끝값부터 delivers를 뺀다.
    그리고, 오면서 제일 끝값부터 pickups를 뺸다.
    
    둘 중 더 큰 값까지 왕복한다 치고, 거리 *2를 한다.
*/

long long solution(int cap, int n, vector<int> deliveries, vector<int> pickups) {
    long long answer = 0;
    
    int deliver_idx = deliveries.size() - 1;
    int pickup_idx = pickups.size() - 1;

    
    while (deliver_idx >= 0 || pickup_idx >= 0) {
        int deliver_size = cap;
        int pickup_size = cap;
        int max_idx = -1;
        
        // cout << "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ" << endl;
        // cout << "택배차 출발!" << endl;
        
        // 배달을 간다! 제일 먼 집부터 배달했다 치자.
        while (deliver_size > 0 && deliver_idx >= 0) {
            // 이번 제일 먼 집에 배달할 택배가 없으면, 그 앞집에 택배를 준다.
            if (deliveries[deliver_idx] == 0) {
                // cout << deliver_idx + 1 << "번 집은 배달할 택배 없음" << endl;
                deliver_idx--;
            }
            
            // 택배가 있으면, 택배를 준다.
            else {
                max_idx = max(max_idx, deliver_idx);
                // 남은 택배가 모자라면, 있는만큼만 두고 온다.
                if (deliver_size < deliveries[deliver_idx]) {
                    deliveries[deliver_idx] -= deliver_size;
                    deliver_size = 0;
                    // cout << deliver_idx + 1 << "번 집에 택배 배달함. " << deliveries[deliver_idx] << "개 남음" << endl;
                }
                // 충분하면, 그 앞집도 본다.
                else {
                    // cout << deliver_idx + 1 << "번 집에 택배 배달 완료! 이제 더 배달할 것 없음" << endl;
                    deliver_size -= deliveries[deliver_idx];
                    deliveries[deliver_idx] = 0;
                    deliver_idx--;
                }
            }
        }
        
        // 배달 다 했으면, 수거한다!
        while (pickup_idx >= 0 && pickup_size > 0) {
            // 가장 먼 집에서 수거할 택배가 없다면, idx를 줄인다.
            if (pickups[pickup_idx] == 0) {
                // cout << pickup_idx + 1 << "번 집은 수거할 택배 없음" << endl;
                pickup_idx--;
            }
            // 수거할 택배가 있다면, 수거한다.
            else {
                max_idx = max(max_idx, pickup_idx);
                // 만약 택배차에 공간이 부족하면, 가능한 만큼만 싣는다
                if (pickup_size < pickups[pickup_idx]) {
                    pickups[pickup_idx] -= pickup_size;
                    pickup_size = 0;
                    // cout << pickup_idx + 1 << "번 집에서 택배 수거함. " << pickups[pickup_idx] << "개 남음" << endl;
                }
                // 충분하다면, 다 싣고 다음 집을 본다
                else {
                    // cout << pickup_idx + 1 << "번 집에서 수거 완료! 이제 더 수거할 것 없음" << endl;
                    pickup_size -= pickups[pickup_idx];
                    pickups[pickup_idx] = 0;
                    pickup_idx--;
                }
            }
        }
        // 한 사이클이 끝날때마다, 왔다갔다 거리를 갱신한다.
        // cout << "이번에는 " << max_idx + 1 << "번 집까지 다녀왔으므로, 이동거리 " << 2 * (max_idx + 1) << "만큼 증가!" << endl;
        answer += 2 * (max_idx + 1);
    }
    return answer;
}