#pragma once
#include <iostream>
#include <string>
#include <stack>
#include <map>
#include <vector>
#include <math.h>
#include <queue>



class Translator {

    std::string infix;
    std::string postfix;
    std::vector<std::string> lexems;
    std::queue<std::string> postfx;
    std::map<std::string, int> priority{ {"(",0}, {"+",1}, {"-",1}, {"*",2}, {"/",2} };
    void Parse() {

        for (int i = 0; i < infix.size(); i++) {

            if (isdigit(infix[i])) {

                std::string tmp;
                tmp = tmp + infix[i];
                for (int j = i + 1; j < infix.size(); j++) {

                    if (isdigit(infix[j])) {
                        tmp = tmp + infix[j];
                        i++;
                    }
                    else {

                        break;
                    }
                }
                lexems.push_back(tmp);
            }
            else {

                std::string other;
                other = other + infix[i];
                lexems.push_back(other);
            }
        }
    };

    bool IsOperation(std::string str) {
        if (str.size() == 1 && ((str == "(") || (str == "+") || (str == "-") || (str == "*") || (str == "/") || (str == ")"))) {

            return 1;//true
        }
        else {

            return 0;//false
        }
    }

    void ToPostfix() {

        Parse();
        std::stack<std::string> st;
        std::string s;
        size_t q = 0;
        postfix = "";
        for (auto i : lexems) {

            if (!(IsOperation(i))) {

                postfx.push(i);
                postfix = postfix + i;
            }

            else if (i == "(") {

                st.push(i);
            }

            else if (i == ".") {

                postfix.pop_back();
                postfix = postfix + i;
            }

            else if (i == ")") {

                while ((!st.empty()) && (st.top() != "(")) {

                    postfx.push(st.top());
                    postfix = postfix + st.top();
                    st.pop();
                }
                st.pop();
            }
            else if ((i == "+") || (i == "-") || (i == "*") || (i == "/")) {

                if ((st.empty()) || (st.top() == "(")) {

                    st.push(i);
                }
                else if (priority[st.top()] < priority[i]) {

                    st.push(i);
                }
                else if (priority[st.top()] >= priority[i]) {

                    while ((!st.empty()) && (priority[st.top()] >= priority[i])) {

                        postfix = postfix + st.top();
                        postfx.push(st.top());
                        st.pop();
                    }
                    st.push(i);
                }
            }
        }
        while (!st.empty()) {

            postfx.push(st.top());
            postfix = postfix + st.top();
            st.pop();
        }
    };

public:

    Translator(const std::string inf) {

        infix = inf;
        ToPostfix();
    };

    std::string GetInfix()const {

        return infix;
    };

    std::string GetPostfix()const {

        return postfix;
    };

    double Calculate() {
        double right_op;
        double left_op;
        std::stack<double> st;
        std::string lex;
        while (!postfx.empty()) {

            lex = postfx.front();
            postfx.pop();
            if (!IsOperation(lex)) {

                st.push(stoi(lex));
            }
            else if (priority.find(lex) != priority.end()) {

                right_op = st.top();
                st.pop();
                left_op = st.top();
                st.pop();
                if (lex == "+") {

                    if (postfix.size() < 3) {

                        throw "error";
                    }

                    else {

                        st.push(left_op + right_op);
                    }
                }
                else if (lex == "-") {

                    if (postfix.size() < 3) {

                        throw "error";
                    }
                    else{
                        
                        st.push(left_op - right_op);
                    }
                    
                }
                else if (lex == "*") {

                    if (postfix.size() < 3) {

                        throw "error";
                    }
                    else{
                        
                        st.push(left_op * right_op);
                    }
                }
                else if (lex == "/") {

                    if (postfix.size() < 3) {

                        throw "error";
                    }
                    else{
                        
                        st.push(left_op / right_op);
                    }                  
                }
            }
        }
        double answer = st.top();
        st.pop();
        return answer;
    };
};