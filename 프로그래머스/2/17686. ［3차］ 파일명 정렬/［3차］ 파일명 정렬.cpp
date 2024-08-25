#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
    저장소 관리 프로그램에 숫자 기준으로 정렬하는 것을  구현할 것!
    1. 먼저 HEAD순으로 사전 정렬한다. 대소문자 구분은 하지 않음
    2. HEAD가 대소문자 차이밖에 없을 경우, 숫자 순으로 정렬한다.
    3. 둘 다 똑같다면, 원래 입력 순서를 유지한다(Stable 하게 정렬한다)
*/

// string을 모두 대문자로 비교해서 변환한다.
string toUpper(string str) {
    int bias = 'a' - 'A';
    string result = "";
    
    for (int i = 0; i < str.length(); i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            result += str[i] - bias;
        }
        
        else {
            result += str[i];
        }
    }
    
    return result;
}

// 정렬용 배열
bool sorting(string a, string b) {
    // 일단 HEAD와 TAIL의 경계를 찾아야 한다.
    int head_length_a, head_length_b;
    for (int i = 0; i < a.length(); i++) {
        if (a[i] >= '0' && a[i] <= '9') {
            head_length_a = i;
            break;
        }
    }

    for (int i = 0; i < b.length(); i++) {
        if (b[i] >= '0' && b[i] <= '9') {
            head_length_b = i;
            break;
        }
    }
    
    // 경계를 찾았다면, 헤드를 비교한다.
    string head_a = toUpper(a.substr(0, head_length_a));
    string head_b = toUpper(b.substr(0, head_length_b));
    
    /*
    cout << "대상 1 : " << a << endl;
    cout << "대상 2 : " << b << endl;
    
    cout << "1의 head : " << head_a << endl;
    cout << "2의 head : " << head_b << endl;
    */
    
    if (head_a != head_b) {
        return head_a < head_b;
    }
    
    // 헤드가 동일하다면, number를 비교해야 한다.
    else {
        // number의 경계를 찾는다
        int number_length_a = 5, number_length_b = 5;
        for (int i = head_length_a + 1; i < head_length_a + 6; i++) {
            if (a[i] > '9' || a[i] < '0') {
                number_length_a = i - head_length_a;
                break;
            }
        }
        
        for (int i = head_length_b + 1; i < head_length_b + 6; i++) {
            if (b[i] > '9' || b[i] < '0') {
                number_length_b = i - head_length_b;
                break;
            }
        }
        
        // number를 가져온다
        string sNumber_a = a.substr(head_length_a, number_length_a);
        string sNumber_b = b.substr(head_length_b, number_length_b);
        int nNumber_a = stoi(sNumber_a);
        int nNumber_b = stoi(sNumber_b);
        
        /*
        cout << "1의 Number : " << nNumber_a << endl;
        cout << "2의 Number : " << nNumber_b << endl;
        */
        
        // 비교한다
        return nNumber_a < nNumber_b;
    }
}

vector<string> solution(vector<string> files) {
    vector<string> answer;
    
    stable_sort(files.begin(), files.end(), sorting);
    
    return files;
}