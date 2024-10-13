#include <string>
#include <vector>
#include <iostream>

using namespace std;

/*  
    양궁대회 열렸다!
    라이언은 저번 대회 우승자, 이번에도 결승까지 왔다.
    결승 상대는 어피치이다.
    
    다양한 선수들이 우승하면 좋겠다고 생각해서, 라이언에게 좀 불리하다.
    
    어치피가 먼저 n발 쏘고, 라이언이 n발 쏜다. 한 구역에 더 많은 화살을 박은 사람이 이긴다!
    같으면, 어피치가 가져간다.
    점수가 같아면, 어피치가 우승한다.
    현재 어피치가 화살 n발을 다 쏘고, 라이언이 쏘려고 한다
    어떻게 쏴야 가장 큰 점수 차로 이길 수 있을까??
    
    우승이 불가능하면 -1을 return한다.
    
    1. 일단 화살 개수대로 얻을 수 있는 점수를 생각한다
    예를 들어, 10점에 어치피 화살이 2개 꽃혀있을 경우, 10점에 최소 3개는 쏴야 한다. 그럼 발당 점수는 3.33점
    
    근데, 6점에 어피치가 한 발도 없다면? 6점 한 발 쏘면 6점이 된다.
    
    점수차가 가장 크면서, 가장 작은 점수를 더 많이 맞힌 경우를 return해야 한다.
    예를 들어 점수차가 같다면, 0점을 더 많이 쏜 것을 return.
    0점을 똑같이 쏜다면, 1점을 더 많이 쏜 것을
    반복...
    
    backtrack으로 모든 경우 확인하자. 어차피 얼마 안 됨(n점을 얻냐, 얻지 않냐)
*/

/*
    백트래킹 수행하는 함수
    vector<int>     info -> 어피치의 화살 점수
    vector<int>     arrowCount -> 라이언이 그 과녁에 몇 발을 꽃았는가?
    vector<int>     answer -> 정답을 저장할 배열
    int             nowScore -> 현재 판단중인 점수
    int             left_arrows -> 남은 화살 개수
*/
void backTrack(const vector<int> &info, vector<int> &arrowCount, vector<int> &answer, int nowScore, int left_arrows);

/*  
    두 결과를 비교하고 더 정답에 적절한 결과를 반환해주는 함수
    vector<int> info -> 어피치가 쏜 화살 수
    vector<int> arrowCount -> 라이언이 이번에 쏜 화살 수
    vector<int> answer -> 원래 정답
*/
vector<int> calc_result(const vector<int> &info, const vector<int> &arrowCount, const vector<int> &answer) {
    // 일단 이번 방법의 승점을 계산한다.
    int new_score(0);
    
    // 둘다 0발이면 아무것도 하지 않고, 그게 아니면 계산을 진행한다.
    for (int i = 0; i < info.size(); i++) {
        if (info[i] == 0 && arrowCount[i] == 0) continue;
        if (info[i] < arrowCount[i]) new_score += (10 - i);
        else new_score -= (10 - i);
    }
    
    // 이번 방법이 이기지 못하는 방법이면, 그냥 answer를 반환한다
    if (new_score <= 0) {
        return answer;
    }
        
    
    // 만약 이번 방법이 이기는 방법이며, 원래 이길 방법이 없었다면 새로 들어온 값을 반환한다
    else if (answer.size() == 1 && new_score > 0) {
        /*
        for (auto v : arrowCount) cout << v << " ";
        cout << " 일 때, 원래 이길 방법이 없었으므로 " << new_score << "점으로 갱신" << endl << endl;
        */        
        return arrowCount;
    }
    
    // 원래 이기는 방법이 있었다면, 점수와 쏜 화살을 비교해야 한다.
    else {
        // 먼저 원래 점수부터 계산한다
        int old_score(0);
        for (int i = 0; i < info.size(); i++) {
            if (info[i] == 0 && answer[i] == 0) continue;
            if (info[i] < answer[i]) old_score += 10 - i;
            else old_score -= 10 - i;
        }
        
        // 만약 점수가 더 높다면, 새로 들어온 방법을 반환한다
        if (new_score > old_score) {
            /*
            for (auto v : arrowCount) cout << v << " ";
            cout << " 일 때, 점수차가 " << new_score << "점으로 더 높으므로 갱신" << endl << endl;
            */
            return arrowCount;
        }
        
        // 점수가 더 낮다면, 원래 방법을 사용한다.
        else if (new_score < old_score) {
            return answer;
        }
        
        // 근데 만약 점수가 같다면? 이제 0점짜리 화살부터 비교해야 한다.
        for (int i = info.size() - 1; i >= 0; i--) {
            if (answer[i] > arrowCount[i]) {
                return answer;
            }
            else if (answer[i] < arrowCount[i]) {
                
                /*
                for (auto v : arrowCount) cout << v << " ";
                cout << " 일 때, " << 10 - i << "번 화살이 더 많아 갱신" << endl << endl;
                */
                
                return arrowCount;
            }
        }
    }
    
    // 만약 다 비교했는데도 반환이 안 됐다면, 같은 화살이었던 것이다.
    // 이런 일은 발생하지 않지만, 그렇다면 원래 값을 쓴다
    return answer;
}

vector<int> solution(int n, vector<int> info) {
    vector<int> answer = {-1};
    vector<int> arrowCount(info.size(), 0);
    
    // backTrack 실행
    backTrack(info, arrowCount, answer, 0, n);
    return answer;
}

void backTrack(const vector<int> &info, vector<int> &arrowCount, vector<int> &answer, int nowScore, int left_arrows) {
    // 이제 0점을 판단할 차례라면, 남은 화살 전부 0점에 꽃고 생각하면 된다.
    if (nowScore == 10) {
        arrowCount[nowScore] = left_arrows;
        
        // 이번 결과와 원래 정답을 비교한다.
        answer = calc_result(info, arrowCount, answer);
        arrowCount[nowScore] = 0;
        return;
    }
    
    // 아직 0점을 판단할 차례가 아니라면, 이번 점수를 얻었을 경우와 얻지 않았을 경우로 나누어서 넘어간다.
    else {
        // 이번 점수를 얻을 경우(화살의 개수가 충분해야 함) 
        if (left_arrows > info[nowScore]) {
            // 화살을 그만큼 썼다 치고, 다음으로 넘어간다.
            arrowCount[nowScore] = info[nowScore] + 1;
            backTrack(info, arrowCount, answer, nowScore + 1, left_arrows - (info[nowScore] + 1));
            arrowCount[nowScore] = 0;
        }
        
        // 이번 점수를 얻지 않는 경우, 그냥 다음으로 넘긴다
        backTrack(info, arrowCount, answer, nowScore + 1, left_arrows);
    }
}