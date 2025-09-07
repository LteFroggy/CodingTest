#include <string>
#include <vector>
#include <iostream>

using namespace std;

/*
    카펫 노란색, 갈색 갯수만 안다.
    갯수 기반으로 카펫 크기 알려달라
    
    노란색은 항상 1이상, 갈색은 항상 8개 이상
    따라서 최소 카펫 사이즈는 3x3
    
    갈색의 총 갯수는 가로 + 가로 + 세로 + 세로 - 4이다.
    
    따라서 다시 보면 총갯수 / 2 = 가로 + 세로 - 2라고 봐도 됨
    다시 말해 총갯수 + 2 = 가로 + 세로 라는 것
    
    노란색은 가로 - 2 * 세로 - 2 * 2가 됨
    
    이걸 기반으로 찾자
*/

vector<int> solution(int brown, int yellow) {
    vector<int> answer;
    
    // 일단 가로 + 세로 / 2 +2 찾기
    int sum = brown / 2 + 2;
    
    // 세로 3부터 시작해서 늘려간다.
    // 세로의 최소 길이는 3, 그리고 가로는 항상 세로보다 길다
    for (int i = 3; i <= sum - i ; i++) {
        cout << (i - 2) * (sum - i - 2) << endl;
        if (yellow == (i - 2) * (sum - i - 2)) {
            answer.push_back(sum - i);
            answer.push_back(i);
            break;
        }
    }
    
    return answer;
}