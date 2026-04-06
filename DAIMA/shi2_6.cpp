#include <iostream>
#include <stack>
#include <unordered_map>
#include <string>

using namespace std;

stack<int> num;   // 操作数栈，使用 STL stack
stack<char> op;   // 运算符栈，使用 STL stack
// 定义运算符优先级，使用 STL unordered_map，值越大优先级越高[reference:1]
unordered_map<char, int> pr{{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}};

// 计算函数：从栈顶取两个操作数和一个运算符进行计算[reference:2]
void eval() {
    // 注意顺序：栈顶是右操作数，先弹出的是 b
    int b = num.top(); num.pop();
    int a = num.top(); num.pop();
    char c = op.top(); op.pop();
    int x;
    switch (c) {
        case '+': x = a + b; break;
        case '-': x = a - b; break;
        case '*': x = a * b; break;
        case '/':
            if (b == 0) {
                cerr << "Error: Division by zero!" << endl;
                return;
            }
            x = a / b;
            break;
    }
    num.push(x);
}

int main() {
    string s;
    cin >> s; // 例如输入： (2+3)*4
    for (int i = 0; i < s.size(); i++) {
        if (isdigit(s[i])) { // 解析数字（支持多位数）
            int x = 0, j = i;
            while (j < s.size() && isdigit(s[j])) x = x * 10 + (s[j++] - '0');
            num.push(x);
            i = j - 1;
        } else if (s[i] == '(') { // 左括号直接入栈
            op.push(s[i]);
        } else if (s[i] == ')') { // 右括号，计算直到遇到左括号
            while (op.top() != '(') eval();
            op.pop(); // 弹出左括号
        } else { // 遇到运算符
            // 当运算符栈非空，且栈顶不是左括号，且栈顶运算符优先级大于等于当前运算符时，先计算[reference:3]
            while (op.size() && op.top() != '(' && pr[op.top()] >= pr[s[i]]) eval();
            op.push(s[i]); // 当前运算符入栈
        }
    }
    while (op.size()) eval(); // 计算栈中剩余的运算
    cout << num.top() << endl; // 输出最终结果
    return 0;
}