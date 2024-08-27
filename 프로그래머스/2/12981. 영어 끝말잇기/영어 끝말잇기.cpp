#include <map>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

/*
    1. 한 글자는 아닌지 체크한다
    2. 끝말이 맞는지 본다.
    3. 이미 사용한 단어인지 체크한다.
    
    사용한 단어 목록을 기억하려면, search가 빠른 자료형을 쓰는 것이 좋을 듯 함.
    -> MAP 사용하자.
*/

vector<int> solution(int n, vector<string> words) {
    vector<int> answer;
    
    // 나온 문자열과 순서 기억하기
    map<string, int> appeared_words;
    int stopped_i = -1;
    char last_alphabet;
    
    for (int i = 0; i < words.size(); i++) {
        // 먼저 문자열을 보고, 위의 세 가지를 검사해야 한다.
        // 1. 한 글자가 아닌가?
        if (words[i].length() == 1) {
            stopped_i = i;
            break;
        }
        
        // 2. 끝말이 맞는가?
        if (i != 0 && last_alphabet != words[i][0]) {
            stopped_i = i;
            break;
        }
        
        // 3. 이미 나왔던 단어가 아닌가?
        auto iter = appeared_words.find(words[i]);
        if (iter != appeared_words.end()) {
            stopped_i = i;
            break;
        }
        
        // 세 가지 모두에 해당하지 않았다면, 문제 없는 것이다.
        // 나온 단어에 추가하고 last_alphabet을 변경한다.
        last_alphabet = words[i][words[i].length() - 1];
        appeared_words.insert({words[i], i});
    }
    
    // 루프가 종료되었다면, stopped_i를 사용해 값을 갱신한다.
    if (stopped_i == -1) {
        return vector<int>{0, 0};
    }
    
    answer.push_back((stopped_i % n) + 1);
    answer.push_back((stopped_i / n) + 1);

    return answer;
}