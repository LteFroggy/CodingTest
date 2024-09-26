#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

/*
    단품 요리를 코스요리로 재구성해서 제공할 것
    
    손님들이 많이 준비한 단품을 코스로 만들것이다!
    
    최소 2가지 이상의 단품으로 구성할 것인데, 2명 이상의 손님으로부터 주문된 메뉴만 코스로 만들 것
    코스는 2개 이상의 단품메뉴로 만들 것이다.
    
    이 친구가 원하는 세트메뉴 구성 단품메뉴 개수를 말하면, 그 개수에 맞춰서 찾아봐야 한다.
    부분집합 만들기.
  
    예를 들어 ABCDE가 있는데 2개짜리를 원한다. 그럼 AB AC AD AE BC BD BE CD CE DE 가 후보가 되는 것
    조합 하는 것이다.
    재귀로 조합 뽑기 해보자
*/

/*
    재귀로 조합을 찾는 함수
    set_menus는 이 사람이 주문한 것 중 세트가 될 수 있는 것을 모두 저장한다
    combination은 조합을 찾기 위한 벡터
    target은 이 사람이 주문한 메뉴
    m은 선택할 개수이다. 
*/
void findSet(vector<string> &set_menus, vector<int> &combination, string target, int start, int m);

vector<string> solution(vector<string> orders, vector<int> course) {
    vector<string> answer;
    
    // 몇 개짜리 세트를 만들지를 기준으로 먼저 시작한다
    for (auto menu_count : course) {
        // 가능한 코스를 저장할 unordered_map
        // unordered_map이 search가 빨라서 사용한다.
        unordered_map<string, int> possible_sets;
        int maxCount_set = 0;
        
        // 각 사람이 시킨 메뉴별로 세트를 저장한다.
        for (auto order : orders) {
            // 이 사람이 시킨 메뉴가 지금 만들고자 하는 세트의 단품메뉴 개수보다 적다면 볼 필요 없음
            if (order.length() < menu_count) continue;
            
            vector<string> person_set;
            vector<int> combinations;
            
            // 이 사람이 시킨 메뉴로 가능한 세트가 person_set에 모두 저장됨
            findSet(person_set, combinations, order, 0, menu_count);
            
            // 그럼 이제 가능한 메뉴 각각을 보면서 저장하기
            for (auto set : person_set) {
                // 이미 있는 세트라면 값을 추가시킨다.
                if (possible_sets.find(set) != possible_sets.end()) {
                    possible_sets[set]++;
                    // 제일 많이 나온 메뉴만 세트가 될 수 있으므로 제일 많이 나온 횟수 세두기
                    maxCount_set = max(possible_sets[set], maxCount_set);
                }
                
                // 없다면 값을 추가한다
                else {
                    possible_sets.insert({set, 0});
                }
            }
        }
        // 한 루프가 끝났다면, possible_sets에 가능한 n개짜리 메뉴들이 저장되어있다.
        // 이 중 가장 큰 값만 저장될 수 있다.
        // 먼저, 가장 많이 나온 횟수가 0이라면 세트가 될 수 있는 것이 없으므로 생략한다
        if (maxCount_set == 0) continue;
        
        // 아니라면, possible_sets를 순회하면서 가장 많이 나온 횟수인 메뉴들을 모두 answer에 넣는다.
        else {
            for (auto v : possible_sets) {
                if (v.second == maxCount_set) {
                    answer.push_back(v.first);
                }
            }
        }
    }

    // 마지막으로, unordered_map이기 때문에 정렬이 되어있지 않으니 answer를 정렬한다.
    sort(answer.begin(), answer.end());
    return answer;
}


void findSet(vector<string> &set_menus, vector<int> &combination, string target, int start, int m) {
    if (m == 0) {
        // 조합을 찾았을 때 저장
        string set = "";
        
        // ABC를 주문했고, 0, 1이 결과라면 AB가 set에 저장되도록 하기 위함
        for (int num : combination) 
            set += target[num];
        
        // 정렬도 수행해서 집어넣는다
        sort(set.begin(), set.end());
        set_menus.push_back(set);
        return;
    }

    for (int i = start; i < target.size(); ++i) {
        combination.push_back(i);  // i를 선택
        findSet(set_menus, combination, target, i + 1, m - 1);  // m을 1 줄여서 이걸 선택했음을 의미
        combination.pop_back();  // 함수가 끝났다면 이걸 선택한 후에 가능한 경우의 수를 모두 탐색했을 것이므로 빼주기
    }
}