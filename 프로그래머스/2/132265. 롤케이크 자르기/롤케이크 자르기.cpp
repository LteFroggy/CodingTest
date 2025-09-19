#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

/*
    롤케이크 토핑에 관심이 많다.
    잘린 크기 관계없이, 동일한 가지수의 토핑이 올라가면 공평하다
    
    공평하게 자르는 방법의 수 return
    
    토핑의 "가지수"만 같으면 된다. N개의 종류가 있음만 체크하면 됨
    따라서 양쪽의 unordered_map을 만든다. 오른쪽에 다 채운 후에, 삭제해가면서 볼 것
*/

int solution(vector<int> topping) {
    int answer = 0;
    
    int leftCount = 0;
    int rightCount = 0;
    
    unordered_map<int, int> leftMap;
    unordered_map<int, int> rightMap;
    
    // 처음엔 다 오른쪽으로 가게 잘랐다고 가정
    for (auto now : topping) {
        if (rightMap.find(now) == rightMap.end()) {
            rightCount++;
            rightMap.insert({now, 1});
        }
        
        else {
            rightMap[now]++;
        }
    }
    
    // 하나씩 왼쪽으로 옮겨가면서 갯수가 같아지는 지점 모두 체크
    for (auto now : topping) {
        // 어떤 토핑 갯수가 0개가 되면, 종류가 줄어든다
        if (--rightMap[now] == 0) {
            rightCount--;
        }
        
        // 토핑 왼쪽으로 옮기기
        if (leftMap.find(now) == leftMap.end()) {
            leftCount++;
            leftMap.insert({now, 1});
        }
        
        else {
            leftMap[now]++;
        }
        
        
        if (leftCount == rightCount) {
            answer++;
        }
    }
    
    return answer;
}