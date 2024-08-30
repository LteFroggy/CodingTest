#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

/*
    속보를 보면 비슷한 제목의 가사가 너무 많다. 
    이를 구분하기 위해 중복을 허용하는 자카드 유사도 진행한다.
    
    두 문자열이 들어온다, 각 길이는 2이상, 1000이하이다.
    두 글자씩 끊어서 집합의 원소로 만든다. 이 때, 영문자로 된 글자 쌍만 유효하게 처리한다.
    또한 비교 시에 대소문자의 차이는 무시한다.
    
    유사도는 교집합 / 합집합 으로 계산한다.
    
    먼저 string을 다 잘라서 vector<string>에 집어넣고, 이걸 오름차순 정렬한다.
    left와 right중 작은 값을 계속 읽어가면서 두 개에서 동일한 값이 나오면 교집합으로, 다르다면 합집합으로 만들면 된다.
    
    ex)
    A : 1 1 2 2 3
    B : 1 2 2 4 5
    
    1. A, B의 값이 서로 같음
        합집합 : (1)
        교집합 : (1)
        A : 1 2 2 3
        B : 2 2 4 5
    
    2. A의 값이 더 작으므로 A값만 사용
        합집합 : 1 1
        교집합 : 1
        A : 2 2 3
        B : 2 2 4 5
    
    3. A, B값이 동일하므로 둘 다 사용
        합집합 : 1 1 2
        교집합 : 1 2
        A : 2 3
        B : 2 4 5
    
    4. 둘 다 사용
        합집합 : 1 1 2 2
        교집합 : 1 2 2
        A : 3
        B : 4 5
    
    5. A가 작음
        합집합 : 1 1 2 2 3
        교집합 : 1 2 2
        A : 
        B : 4 5
    
    6. 이제 A를 모두 사용해서, B 그대로 모두 합집합에 넣기
        합집합 : 1 1 2 2 3 4 5
        교집합 : 1 2 2
        A :
        B :
    
    유사도 : 3/7
*/

int bias = 'a' - 'A';

bool isEnglish(char target) {
    return (target <= 'Z' && target >= 'A') || (target >= 'a' && target <= 'z');
}

int solution(string str1, string str2) {
    int answer = 0;
    
    vector<string> str1_words;
    vector<string> str2_words;
    
    for (int i = 0; i < str1.length() - 1; i++) {
        string tmp = str1.substr(i, 2);
        
        // 일단, 두 자리 값이 모두 영문자인지 확인해야 한다.
        if (!isEnglish(tmp[0]) || !isEnglish(tmp[1])) {
            continue;
        }
        
        // 그렇다면, vector에 넣는다. 그런데 대소문자 차이를 무시해야 하므로, 대문자 값들에 대해서는 bias을 더해서 모두 소문자로 만든다.
        if (tmp[0] < 'a') tmp[0] += bias;
        if (tmp[1] < 'a') tmp[1] += bias;
        
        str1_words.push_back(tmp);
    }
    
    for (int i = 0; i < str2.length() - 1; i++) {
        string tmp = str2.substr(i, 2);
        
        // 일단, 두 자리 값이 모두 영문자인지 확인해야 한다.
        if (!isEnglish(tmp[0]) || !isEnglish(tmp[1])) {
            continue;
        }
        
        // 그렇다면, vector에 넣는다. 그런데 대소문자 차이를 무시해야 하므로, 대문자 값들에 대해서는 bias을 더해서 모두 소문자로 만든다.
        if (tmp[0] < 'a') tmp[0] += bias;
        if (tmp[1] < 'a') tmp[1] += bias;
        
        str2_words.push_back(tmp);
    }
    
    sort(str1_words.begin(), str1_words.end());
    sort(str2_words.begin(), str2_words.end());
    
    /*
    for (auto v : str1_words) cout << v << " ";
    cout << endl;
    
    for (auto v : str2_words) cout << v << " ";
    cout << endl;
    */
    
    
    // 이제 정렬하고, 하나씩 보자
    int idx_1(0), idx_2(0);
    int union_count(0), intersection_count(0);
    
    while (idx_1 < str1_words.size() && idx_2 < str2_words.size()) {
        string word1 = str1_words[idx_1];
        string word2 = str2_words[idx_2];
        
        // str1과 str2의 단어를 비교한다.
        // str1이 더 작다면, str1의 단어를 먼저 읽는다
        if (word1 < word2) {
            union_count++;
            idx_1++;
        }
        
        else if (word1 > word2) {
            union_count++;
            idx_2++;
        }
        
        else if (word1 == word2) {
            union_count++;
            intersection_count++;
            idx_1++;
            idx_2++;
        }
    }
    
    // 위의 과정이 끝났을 때, 끝난 값이 있는지 보고, 그렇다면 나머지는 모두 합집합으로 더한다
    if (idx_1 == str1_words.size()) {
        union_count += str2_words.size() - idx_2;
    }

    else if (idx_2 == str2_words.size()) {
        union_count += str1_words.size() - idx_1;
    }

    double fAnswer(1);
    if (union_count != 0) 
        fAnswer = intersection_count / double(union_count);
    
    else if (union_count == 0)
        return 65536;
    
    fAnswer *= 65536;
    answer = int(fAnswer);
    
    return answer;
}