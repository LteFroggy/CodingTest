#include <string>
#include <vector>
#include <map>
#include <iostream>

/*
    메세지 압축하기
    먼저 대문자 배열만 가지고, 두 글자씩 보면서 새로 나오는 문자열을 등록하는 방식
    
    hashmap 활용하자.
*/
using namespace std;

int findValueInMap(const map<string, int> &myMap, string target) {
    // 찾고자 하는 값이 없으면, 0을 리턴한다
    auto iter = myMap.find(target);
    if (iter == myMap.end()) {
        return 0;
    } 
    else {
        return iter->second;
    }
}

vector<int> solution(string msg) {
    vector<int> answer;
    
    map<string, int> myMap;
    
    // 먼저 알파벳 대문자 집어넣기
    for (int i = 0; i < 26; i++) {
        string str = "";
        str += i + 'A';
        myMap.insert({str, i + 1});
    }
    
    // 값을 추가로 넣을 때 사용할 변수
    // 현재 A ~ Z까지 26개가 들어가있으니 26으로 설정해둔다.
    int map_size = 26;
    
    // 알파벳을 하나씩 보면서 가능한 문자열인지 찾기
    int cursor = 0;
    int span = 0;
    int zippedVal;
    
    while (cursor < msg.size()) {
        string now = "";
        span = 0;
        
        // 먼저 알파벳을 하나씩 늘려본다
        while (cursor + span < msg.size()) {
            now += msg[cursor + span];
            
            // 현재 단어가 사전에 존재한다면 추가로 탐색해본다
            int value = findValueInMap(myMap, now);
            if (value != 0) {
                zippedVal = value;
            }
            
            // 현재 단어가 사전에 존재하지 않는 단어라면, 반복을 종료한다.
            else {
                break;
            }
            span++;
        }
        // 반복문이 종료되었다면, 먼저 zippedVal을 답안에 추가하고 map에 문자열을 추가한다
        answer.push_back(zippedVal);
        myMap.insert({now, ++map_size});
        
        // 그 후, cursor를 수정한다.
        cursor += span;
    }
    
    return answer;
}