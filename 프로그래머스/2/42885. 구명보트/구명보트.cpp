#include <string>
#include <vector>
#include <algorithm>

/*
    구명보트를 이용해 사람을 구한다
    사람은 2명밖에 못타고, 무게제한도 있음
    
    구명보트를 최대한 적게 사용, 모든 사람을 구출하자
    그냥 Proitoriy Queue를 사용하면 뒤를 보러 갈 수가 없다.
    그렇다고 하나하나 계산하자니, 25 * 10^8이라 안됨.
    일단 몸무게를 정렬한다
    그리고 left, right 기준으로 pointer를 옮겨가며 보기
    
    
    50 50 70 80 
    l        r
    weight[l] + weight[r] > limit 이므로 우측 포인터 당기기
    
    50 50 70 80 
    l     r
    weight[l] + weight[r] > limit 이므로 우측 포인터 당기기
    
    50 50 70 80 
    l  r
    weight[i] + weight[r] <= limit 이므로 이대로 한 팀 태우기
    
    총 필요한 구명보트 3대
*/

using namespace std;

int solution(vector<int> people, int limit) {
    int answer = 0;
    
    sort(people.begin(), people.end());
    
    int idx_l = 0;
    int idx_r = people.size() - 1;
    
    while (idx_l <= idx_r) {        
        // 제일 가벼운 사람과 제일 무거운 사람을 하나에 태울 수 있는가?
        if (people[idx_l] + people[idx_r] <= limit) {
            // 가능하다면 두명 태우고, 인덱스 당기기
            answer++;
            
            idx_l++;
            idx_r--;
        }
        
        // 못 태운다면? 무거운 사람 그냥 혼자 태우고 인덱스 당기기
        else {
            answer++;
            idx_r--;
        }
        
        
        // 한명 남았으면 태우고 계산 없이 끝내기
        if (idx_l == idx_r) {
            answer++;
            break;
        }
    }
    
    return answer;
}