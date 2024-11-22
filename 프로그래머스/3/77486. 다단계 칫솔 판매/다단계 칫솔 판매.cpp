#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

/*  
    민호가 다단계로 칫솔을 판다.
    판매원이 판매하면, 이익이 피라미드를 타고 조금씩 분배된다.
    
    근데 중간에, 누가 얼마만큼의 이득을 봤나 좀 궁금해졌다.
    
    이익 분배 방법은, 이익에서 10%를 계산하여 나를 참여시킨 추천인에게 배분하고, 나머지는 자신이 가진다.
    여기서의 이익은 판매이익뿐만이 아니라, 피라미드를 타고 올라온 모든 수익에 포함된다.
    10%가 1원 미만인 경우라면, 분배하지 않고 모두 자신이 가진다.
    
    각 판매원의 이름을 담은 배열과 나를 참여시킨 판매원의 이름을 담은 referral, 판매원 이름을 나열한 seller, amount가 주어지면 각 판매원별 이익금을 return해보자.
    
    enroll에 민호의 이름은 없다. 따라서 enroll은 민호를 제외한 조직 구성원의 총 수이다.
    민호는 판 돈에 자신의 이름이 들어갈 필요 없음
*/

vector<int> solution(vector<string> enroll, vector<string> referral, vector<string> seller, vector<int> amount) {
    vector<int> answer(enroll.size(), 0);
    
    // 이름별로 index를 저장하는 map
    unordered_map<string, int> person_loc;
    
    for (int i = 0; i < enroll.size(); i++) {
        person_loc.insert({enroll[i], i});
    }
    
    // 각자가 판 갯수를 저장하는 map
    unordered_map<string, int> sell_amount;
    
    // 각자 판매한 것 별로 수익을 위로 올려준다.
    for (int i = 0; i < seller.size(); i++) {
        // 이 사람이 판 실적을 확인한다
        string name = seller[i];
        string refer_name = referral[person_loc[name]];
        int profit = amount[i] * 100;
        int charge = profit / 10;
        
        // 내가 이번에 낸 수익을 위로 올려보내준다.
        while (refer_name != "-" && profit > 0) {
            // 내 선임에게 10%를 줘야 하니, 나는 90%만 받는다.
            answer[person_loc[name]] += (profit - charge);
            
            // 값을 갱신한다
            profit = charge;
            charge = profit / 10;
            name = refer_name;
            refer_name = referral[person_loc[name]];
        }
        
        // 내 상사가 민호라면, 일단 돈 받고 charge만큼 깐다
        answer[person_loc[name]] += profit;
        answer[person_loc[name]] -= charge;
    }
    return answer;
}