#include "Solution.h"
#include <stack>
#include <cctype>
#include <iostream>

using namespace std;

string Solution::countOfAtoms(string formula) {
    stack<map<string, int>> st;
    st.push(map<string, int>()); 

    int i = 0;
    int n = formula.size();

    while (i < n) {
        if (formula[i] == '(') {
            st.push(map<string, int>());
            i++;
        } else if (formula[i] == ')') {
            map<string, int> topMap = st.top();
            st.pop();
            i++;

            int multiplier = 0;
            while (i < n && isdigit(formula[i])) {
                multiplier = multiplier * 10 + (formula[i] - '0');
                i++;
            }
            if (multiplier == 0) multiplier = 1;

            for (auto const& [atom, count] : topMap) {
                st.top()[atom] += count * multiplier;
            }
        } else {
            int start = i;
            i++;
            while (i < n && islower(formula[i])) {
                i++;
            }
            string atom = formula.substr(start, i - start);

            int multiplier = 0;
            while (i < n && isdigit(formula[i])) {
                multiplier = multiplier * 10 + (formula[i] - '0');
                i++;
            }
            if (multiplier == 0) multiplier = 1;

            st.top()[atom] += multiplier;
        }
    }

    string result = "";
    for (auto const& [atom, count] : st.top()) {
        result += atom;
        if (count > 1) {
            result += to_string(count);
        }
    }

    return result;
}