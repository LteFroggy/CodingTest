#include <unordered_map>
#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

/*
    검색어 자동완성을 구현하고자 한다.
    한번 입력된 문자열을 학습해서 사용할 것
    
    단, 학습에 사용된 단어들 중 앞부분이 같은 경우에는 어쩔 수 없이 다른 문자가 나올 때까지 입력해야 함.
    
    효과를 테스트하기 위해 학습된 단어를 찾을 때 몇 글자를 입력해야 하는지 궁금하다
    
    Trie를 사용한다고 한다. 이는 접두에 공통을 판단하는 데에 굉장히 효과적인 자료구조이다.
*/

struct TrieNode {
    unordered_map<char, TrieNode*> children;
    int count = 0;
    /// string word = "";
    bool isEnd = false;
    
    // 기본 생성자와, 노드용 생성자 모두 치원
public :
    TrieNode() {};
    /// TrieNode(string str) : word(str) {};
    
    ~TrieNode() {
        for (auto iter = children.begin(); iter != children.end(); iter++) {
            delete iter->second;
        }
    }
};

class Trie {
private :
    TrieNode* root;
    
public :
    Trie() {
        root = new TrieNode();
    }
    
    /*
    void checkTrie() {
        stack<TrieNode*> stk;
        
        // 스택에 루트 넣기
        stk.push(root);
        
        while (!stk.empty()) {
            TrieNode* node = stk.top();
            stk.pop();
            // 먼저 자기 정보 표시
            cout << "word : " << node->word << ", count = " << node->count << ", isEnd = " << node->isEnd << endl;
            // 자기 children 모두 넣기
            for (auto v : node->children) {
                stk.push(v.second);
            }
        }
    }
    */
    
    
    void insert(string word) {
        TrieNode* node = root;
    
        for (auto var : word) {
            // 값을 한 글자씩 찾는다. 없으면 넣고, 있으면 추가함.
            if (node->children.find(var) == node->children.end()) {
                /// node->children.insert({var, new TrieNode(str)});
                node->children.insert({var, new TrieNode()});
            }
            
            // 이동하고, Count 추가하기
            node = node->children[var];
            node->count++;
        }
        
        // 마지막 노드였다면, isEnd True로 바꿔주기
        node->isEnd = true;
    }
    
    // 어떤 String이 몇 글자나 쳐야 나오나?
    int checkCharCount(string str) {
        int count = 0;
        TrieNode* node = root;
        for (auto v : str) {
            count++;
            // 일단 Trie 다음 노드 찾기
            node = node->children[v];
            
            // 만약, 카운트가 1이라면 하나밖에 없는거니 이대로 진행
            if (node->count == 1) break;
        }
        
        return count;
    }
    
    ~Trie() {
        delete root;
    }
};


int solution(vector<string> words) {
    
    int answer = 0; 
    // 먼저 트라이 만들기
    Trie myTrie = Trie();
    
    for (auto v : words) {
        myTrie.insert(v); 
    }
    
    // 답 구하기
    for (auto v : words) {
        answer += myTrie.checkCharCount(v);
    }
    
    return answer;
}