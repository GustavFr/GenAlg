#ifndef SOLVE
#define SOLVE

#include <string>
#include <stack>
#include <map>
#include <functional>
#include <cmath>
#include <cstring>
#include <iostream>

using namespace std;

static int originPrime[] = {2,3,5,7,11,13,17,19,23,29};

struct Node{
    Node(std::string _formula) : formula(_formula), error(0) {};

    std::string StringReplacer(const std::string& inputStr, const std::string& src, const std::string& dst)
    {
        std::string result(inputStr);

        size_t pos = result.find(src);
        while(pos != std::string::npos) {
            result.replace(pos, src.size(), dst);
            pos = result.find(src, pos);
        }

        return result;
    }

    void calc(){
        int N = sizeof(originPrime) / sizeof(originPrime[0]);
        for(int i = 0; i < N; ++i){
            this->formula = StringReplacer(this->formula,"x",std::to_string(i+1));
            char tmp[formula.length() + 1];
            strcpy(tmp, formula.c_str());
            this->error += abs(this->parse(tmp) - originPrime[i]);
        }
    }

    std::string formula;
    int error;

    int parse(char *formula){
        stack<int> s;
        stack< pair<int, char> > ops;

        auto p = [&s, &ops] (function<int (int, int)>& f)
        {int r=s.top();s.pop();r=f(s.top(),r);s.pop();s.push(r);ops.pop();};

        map< char, pair< int, function<int (int, int)> > > m =
        {{'+', {1, [](int a, int b){return a+b;}}},{'-', {1, [](int a, int b){return a-b;}}},
        {'*', {2, [](int a, int b){return a*b;}}},{'%', {2, [](int a, int b){return a%b;}}}};

        const int order = 2; int level = 0;
        for (char* sp = formula;; ++sp) {
            while (*sp == '(') {level += order; ++sp;}
            s.push(strtod(sp, &sp));
            while (*sp == ')') {level -= order; ++sp;}
            if (!*sp) {while(!ops.empty()) p(m[ops.top().second].second); break;}
            const int op =  m[*sp].first + level;
            while (!ops.empty() && ops.top().first >= op) p(m[ops.top().second].second);
            ops.push(make_pair(op, *sp));
        }
        return s.top();
    }
};

struct Solve{
    int count;
    Node *parents;


    Solve(Node *_parents, int _count) : count(_count), parents(_parents){
        for(int i = 0; i < count; ++i){
            parents[i].calc();
            std::cout << parents[i].error << std::endl;

        }
    };

};

#endif
