#include <queue>
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>

/*
    귤 수확했다.
    수확한 귤 중 k개를 골라 상자에 담아 판매할 것.
    
    그런데 수확한 귤의 크기가 일정치 않아, 보기에 좋지가 않음. 그래서 크기가 서로 다른 귤의 갯수를 최소화하려고 함
    경화가 한 상자에 담으려는 귤의 수 k와 귤의 크기를 담은 배열이 주어진다.
    크기가 다른 서로 다른 종류의 수를 return 하자
    
    쭉 보면서 key-value 기반으로 Map에 넣기
    다 꺼내서 Priority Queue에 넣기
    하나씩 뺴면서 확인
*/

using namespace std;

int solution(int k, vector<int> tangerine) {
    int answer = 0;
    
    unordered_map<int, int> myMap;
    
    for (auto v : tangerine) {
        if (myMap.find(v) == myMap.end()) myMap.insert({v, 1});
        else myMap[v]++;
    }
    
    // 전부 priorityqueue에 넣기
    priority_queue<int> pq;
    
    for (auto iter = myMap.begin(); iter != myMap.end(); iter++) {
        pq.push(iter->second);
    }
    
    while (!pq.empty() && k > 0) {
        int tmp = pq.top();
        pq.pop();
        
        answer++;
        k -= tmp;
    }
    
    
    return answer;
}