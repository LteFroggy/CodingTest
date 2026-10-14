#include <string>
#include <vector>
#include <cmath>

using namespace std;

/*
    프로그래머스 팀 기능 개선 작업 수행 중
    
    각 기능은 진도가 100%일 때만 서비스에 반영 가능하다.
    기능별 개발속도는 모두 다르므로, 두가 앞보다 먼저 개발될 수 있음.
    
    하지만 뒤 기능은 앞 기능이 배포될 때 함께 배포되어야 함
    
    먼저 배포되어야 하는 순서대로 작업 진도가 적힌 배열, 그리고 각 작업상 개발속도가 적힌 배열이 주어지면 각 배포마다 몇 개가 배포되는지 return하자.
    
    제일 앞에것이 몇 번째 날에 배포되는지 확인, 뒤도 그대로 적용해보고 가능하면 같이하기, 아님말기
*/

class ReleaseCounter {
    private : 
    vector<int> progresses;
    vector<int> speeds;
    int releaseIndex;
    
    public :
    ReleaseCounter(vector<int> progresses_input, vector<int> speeds_input) : progresses(progresses_input), speeds(speeds_input) {
        releaseIndex = 0;
    }
    
    vector<int> GetCalculationResult() {
        vector<int> results;
        do {
            int releaseCount = 1;
            
            int dayCountNeeded = (100 - progresses[releaseIndex] + speeds[releaseIndex] - 1) / speeds[releaseIndex];  
            releaseIndex++;            

            while (releaseIndex < progresses.size()) {
                
                int nextCountNeeded = (100 - progresses[releaseIndex] + speeds[releaseIndex] - 1) / speeds[releaseIndex];  
                
                if (nextCountNeeded > dayCountNeeded) { break; }
                
                releaseCount++;
                releaseIndex++;
            }
            
            results.push_back(releaseCount);
        } while (releaseIndex < progresses.size());
            
        return results;
    }
};

vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<int> answer;
    
    ReleaseCounter counter(progresses, speeds);
    
    return counter.GetCalculationResult();
}
