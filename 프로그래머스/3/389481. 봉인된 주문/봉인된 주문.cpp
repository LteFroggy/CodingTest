#include <cmath>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <unordered_map>

using namespace std;

/*
    각 주문은 알파벳 소문자 11글자 이하
    
    마법 효과 없는 의미 없는 주문들이 규칙에 따라 있다.
    
    글자수 적은 것부터 기록
    글자수 같으면 사전 순으로 기록
    
    그런데 좀 사라진 값이 있다. 사라진 값 고려해서 n번째 주문 찾기
    
    버킷과 카운트가 있음
    마지막 한 글자를 뺸 버킷, 카운트에 정렬
    a -> "" 버킷에 삽입
    "" 카운트 1 증가
    ae -> "a" 버킷에 삽입
    "a" 카운트 1 증가
    aea -> "ae" 버킷에 삽입
    "ae" 카운트 1 증가
    
    30번쨰 찾기
    첫 26개는 ""로 시작하니, "" 카운트 보기 -> 값이 1이니 총 25개
    
    30 > 25이니 30 - 25 = 5로 다음으로 이동
    "a" 접두사
    "a" 접두사의 카운트는 1이므로 총 25개의 값이 있음.
    25 !> 5 이니 이 안에 있음

    그럼 "a" 버킷 보기
    e가 있음.
    a b c d e <- 5번째. 근데 e가 이미 버킷에 있으니 스킵하고 af가 답
    
*/

long long alphaToInt(string target) {
    long long result = 0;
    
    reverse(target.begin(), target.end());

    for (int i = 0; i < target.size(); i++)
        result += pow(26, i) * (target[i] - 'a' + 1);
    
    return result;
}

string intToAlpha(long long target) {
    string result = "";
    
    while (target > 0) {
        target--;
        result = char((target % 26) + 'a') + result;
        
        target /= 26;
    }
    
    return result;
}

string solution(long long n, vector<string> bans) {
    string answer = "";

    vector<long long> bans_int;
    
    // 알파벳 -> 정수 변경, 정렬
    for (auto v : bans) {
        bans_int.push_back(alphaToInt(v));
    }
    
    sort(bans_int.begin(), bans_int.end());
    
    // for (auto v : bans_int) cout << v << " "; cout << endl;
    
    int idx = 0;
    
    while (bans_int[idx] <= n && idx < bans_int.size()) {
        n++;
        idx++;
    }
    
    // cout << "n = " << n << ", 알파벳 변환 결과는 " << intToAlpha(n) << endl;
    
    return intToAlpha(n);
}