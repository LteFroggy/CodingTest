#include <string>
#include <vector>
#include <unordered_map>
#include <set>

using namespace std;

/*
    시소가 있다.
    
    2m, 3m, 4m구간에 좌석이 있다.
    두 명이 마주보고 탄다.
    토크의 크기가 상쇄되어 균형이 이뤄진다면, 두 명이 시소 짝궁이다!
    토크 = 무게 x 좌석간의 거리
    
    시소 짝꿍의 쌍을 구하자
    
    사람은 최대 10만명
    
    사람마다 자리별로 토크를 구해야 한다.
    unordered_map에 넣고, 개수를 세자!
    
    그런데, 같은 무게를 가진 사람은 2m, 3m, 4m에서 모두 중복되는 문제 발생
    같은 무게를 가진 사람들은 한 번만 계산할 수 있도록 정렬하기
*/

long long solution(vector<int> weights) {
    long long answer = 0;
    int dist[] = {2, 3, 4};
    
    unordered_map<int, int> weight_count;
    unordered_map<int, int> map_torque;
    
    set<int> set_weights;
    
    // 같은 무게를 가진 사람은 한 번만 카운트되도록 한다
    for (auto weight : weights) {
        if (weight_count.find(weight) == weight_count.end()) {
            weight_count.insert({weight, 1});
        }
        
        else {
            // 같은 무게를 가진 사람이 있다면, 이들은 이미 시소짝꿍이다.
            answer += weight_count[weight];
            weight_count[weight]++;
        }
        
        set_weights.insert(weight);
    }
    
    for (auto weight : set_weights) {
        // 이 사람이 2, 3, 4거리에 앉았을 때의 토크를 저장해서 torque에 넣는다
        // 이 무게를 가진 사람이 몇 명 있는지 확인하기
        int person_count = weight_count[weight];
        for (int k = 0; k < 3; k++) {
            int torque = dist[k] * weight;
            
            // 이 key값이 저장되어있지 않다면, 추가한다
            if (map_torque.find(torque) == map_torque.end()) {
                map_torque.insert({torque, person_count});
            }
            
            // 이미 저장되어있는 값이라면, answer를 증가시키고 value를 1 늘린다
            else {
                answer += long(person_count) * long(map_torque[torque]);
                map_torque[torque] += person_count;
            }
        }
    }
    
    return answer;
}