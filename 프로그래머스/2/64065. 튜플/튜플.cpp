#include <string>
#include <vector>
#include <unordered_set>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

/*
    n개의 요소를 가진 튜플을 n-튜플이라고 한다.
    
    튜플은 중복된 원소가 있을 수 있고, 원소의 순서가 다르면 다른 튜플이다.
    원소 개수는 유한하다.
    
    원소의 개수가 n이고, 중복되는 원소가 없는 튜플이 주어졌을 때 집합을 이용해 표현 가능하다!
    그런데, 집합은 순서가 바뀌어도 괜찮으므로 안에 원소가 몇 개 있느냐만 중요하다.
    
    그럼, 일단 집합을 자르고 길이 순서대로 정렬한 후 새로운 원소를 파악하면 되겠다!
    튜플 길이는 최대 500개이므로 최대 500개의 부분집합이 존재할 수 있다.
    따라서 조회는 최대 250,000 / 2 번 발생 10^5
    
    unordered set의 조회 시간복잡도는 1이므로 문제없음
*/

vector<string> split(string str, char delimeter) {
    stringstream ss(str);
    string tmp;
    vector<string> result;
    
    while (getline(ss, tmp, delimeter)) {
        result.push_back(tmp);
    }
    
    return result;
}

// 정렬 기준 함수(문자열 길이)
bool compare_std(vector<int> a, vector<int> b) {
    return a.size() < b.size();
}

// 입력 문자열 s를 벡터들로 바꿔주는 함수
vector<vector<int>> string_to_vectors(string s) {
    
    
    // 먼저 s의 앞, 뒤(첫 중괄호, 마지막 중괄호)를 자른다.
    s = s.substr(1, s.length() - 2);
    /*  
        Before :    {{2},{2,1},{2,1,3},{2,1,3,4}}
        
        After :     {2},{2,1},{2,1,3},{2,1,3,4}
    */
    
    
    
    // 그리고 중괄호 안의 반점들은 띄어쓰기로 변환한다.
    bool in_bracket = false;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '{') in_bracket = true;
        else if (s[i] == '}') in_bracket = false;
        
        if (s[i] == ',' && in_bracket) s[i] = ' ';
    }
    /*
        Before :    {2},{2,1},{2,1,3},{2,1,3,4}
        
        After :     {2},{2 1},{2 1 3},{2 1 3 4}
    */
    
    
    
    
    // 이제 반점들을 기준으로 split한다
    vector<string> splited = split(s, ',');
    /* 
        Before :    {2},{2 1},{2 1 3},{2 1 3 4}
        
        After :     [[{2}], [{2 1}], [{2 1 3}], [{2 1 3 4}]] 
    */
    
    
    
    
    // split된 결과의 앞, 뒤 하나씩(중괄호)를 자르고, 띄어쓰기 기준으로 split한다
    vector<vector<int>> result;
    for (auto v : splited) {
        v = v.substr(1, v.length() - 2);
        
        vector<string> tmp = split(v, ' ');
        
        // split된 이후에는, 저장된 각각의 값을 int로 바꿔 result에 저장한다
        result.push_back(vector<int>());
        
        for (auto value : tmp) {
            result[result.size() - 1].push_back(stoi(value));
        }
    }
    /*
        Before :    [[{2}], [{2 1}], [{2 1 3}], [{2 1 3 4}]] 
        
        After :     [[[2]], [[2] [1]], [[2] [1] [3]], [[2] [1] [3] [4]]] 
    */
    
    // 이 결과를 반환한다
    return result;
}

vector<int> solution(string s) {
    vector<int> answer;
    
    // 잘린 결과 가져오기
    vector<vector<int>> result = string_to_vectors(s);
    
    // 이제, 이걸 길이순으로 정렬한다
    sort(result.begin(), result.end(), compare_std);
    
    // 확인용 출력
    /*
    for (auto v : result) {
        for (auto v_ : v) {
            cout << v_ << " ";
        }
        cout << endl;
    }
    */
    
    // 이제 각 원소를 unordered_set에 저장하면서 처음 나오는 원소를 찾으면 된다.
    unordered_set<int> mySet;
    for (vector<int> set : result) {
        for (int value : set) {
            if (mySet.find(value) == mySet.end()) {
                mySet.insert(value);
                answer.push_back(value);
                continue;
            }
        }
    }
    
    return answer;
}