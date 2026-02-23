#include <string>
#include <vector>
#include <iostream>

using namespace std;

/*
    부모 노드가 0이라면, 자식 노드는 모두 0의 값을 가져야 한다.
    
    1. Mid값을 확인한다
    2. 왼쪽, 오른쪽 서브트리 값이 0인지 확인한다.
    3. 왼쪽, 오른쪽 서브트리를 재귀적으로 탐색한다.
    
                   8
          4                      12
      2       6           10           14
    1   3   5   7      9      11    13    15
*/

class TreeCheck {
public :
    static bool CheckTree(const string& tree, const int& low, const int& high, bool zeroFlag) {
        
        // zeroFlag가 true인 경우, 값이 0이 아니라면 false 반환
        int mid = (low + high) / 2;
        if (zeroFlag && tree[mid] == '1') return false;
        
        
        // 리프노드면, 문제없을 경우 그냥 반환
        if (low == high) {
            return true;      
        } 
        // 리프노드가 아니라면, 값에 따라 zeroFlag 수정하고 재귀
        else {
            if (tree[mid] == '0') zeroFlag = true;
            return CheckTree(tree, low, mid - 1, zeroFlag) && CheckTree(tree, mid + 1, high, zeroFlag);
        }
    }
};

string converToBin(long val) {
    string result = "";
    
    while (val > 0) {
        result = char((val % 2) + '0') + result;
        val = val >> 1;
    }
    
    return result;
}

vector<int> solution(vector<long long> numbers) {
    vector<int> answer;
    
    for (auto v : numbers) {
        string target = converToBin(v);
        
        // 길이 교정
        int i = 2;
        while (true) {
            if (target.length() <= i - 1) {
                while (target.length() < i - 1) {
                    target = '0' + target;
                }
                break;
            }
            i *= 2;
        }
        
        // cout << target << endl;
        
        // 판단
        if (TreeCheck::CheckTree(target, 0, target.length() - 1, false)) answer.push_back(1);
        else answer.push_back(0);
    }
    
    

    return answer;
}

