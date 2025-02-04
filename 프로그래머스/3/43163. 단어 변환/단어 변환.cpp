#include <string>
#include <vector>

using namespace std;

/*
    begin, target과 words가 있다.
    begin에서 target으로 변환하는 가장 짧은 과정은??
    
    1. 한 번에 한 개의 알파벳만 바꿀 수 있다
    2. words에 있는 단어로만 바꿀 수 있다.
    3. 모든 단어의 길이는 같다.
    
    어떤 상태에서 갈 수 있는 다음 상태를 모두 찾고, 다 가보면 된다!
    제일 짧게 변환 성공하면 끝내면 됨
*/

void Search(const vector<string> &words, vector<bool> &isUsed, string now, const string &target, int count, int &answer) {
    // 만약 함수를 반복해보다가 완성했으면, 현재의 count를 세고 answer에 저장한다
    if (now == target) {
        if (count < answer) answer = count;
        return;
    }

    // 지금 단어를 바탕으로 변환 가능한 단어들을 모두 탐색하고, 가능하면 변환해본다.
    for (int i = 0; i < words.size(); i++) {
        // 이미 변환해본 단어면, 해보지 않는다.
        if (isUsed[i]) continue;
        
        int diff_count = 0;
        // 서로 다른 알파벳이 몇 개인지 확인한다!
        for (int j = 0; j < words[i].size(); j++) {
            if (now[j] != words[i][j]) diff_count++;
        }
        
        // 알파벳이 한 개만 다르다면 변환 가능하다. 변환 시켜서 넘겨본다.
        if (diff_count == 1) {
            isUsed[i] = true;
            Search(words, isUsed, words[i], target, count + 1, answer);
            isUsed[i] = false;
        }
    }
}

int solution(string begin, string target, vector<string> words) {
    int answer = 1e9;
    vector<bool> isUsed(words.size(), false);
    
    Search(words, isUsed, begin, target, 0, answer);
    
    // 탐색을 돌리고, 불가능하면 0, 가능하다면 그 값을 돌려준다.
    if (answer == 1e9) return 0;
    else return answer;
}