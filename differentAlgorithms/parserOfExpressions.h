#ifndef INFIXTOPOSTFIX_H_
#define INFIXTOPOSTFIX_H_

#include <stdexcept>
#include <string>
#include <string_view>
#include "MyStack.h"

bool isRightBrackets(std::string_view s);

class infToPost
{
private:
	std::string input;
	int position;
	//size == 64 (in default)
	MyStack<int> digits;
	MyStack<char> operations;

	bool isEnd() const { return position == input.size(); };
	bool isDigit() const { return input[position] >= '0' && input[position] <= '9'; }
	bool isOperation(char ch) const { return ch == '+' || ch == '-' || ch == '*' || ch == '/'; }
	bool isLeftBrac(char ch) const { return ch == '('; }
	bool isRightBrac(char ch) const { return ch == ')'; }
	
	int priority(char ch) const {
		if (ch == '+' || ch == '-') return 1;
		else if (ch == '*' || ch == '/') return 2;
		else throw std::runtime_error("underfind operation!");
	}
	
	int get_num(){
		int value = 0;
		while (!isEnd() && isDigit()) {
			value = value * 10 + (input[position] - 48); //Собираем число
			++position;
		}
		--position;
		return value;
	}
	
	void get_res(char operation) {
		int r = digits.pop();
		int l = digits.pop();
		switch (operation) {
			case '+': 
				digits.push(l + r); 
				break;
			case '-': 
				digits.push(l - r); 
				break;
			case '*': 
				digits.push(l * r); 
				break;
			case '/': 
				digits.push(l / r); 
				break;
		}
	}

	

public:
	infToPost(std::string inp) {
		if (isRightBrackets(inp)) {
			input = inp;
			position = 0;
		}
		else {
			throw std::runtime_error("The sequence of brackets is not right!");
		}
	}

	int calculate() {
		while (!isEnd()) {
			if (isRightBrac(input[position])) {
				while (!isLeftBrac(operations.peek())) {
					get_res(operations.pop());
				}
				operations.pop();
			}
			else if (isLeftBrac(input[position]))
				operations.push(input[position]);
			else if (isOperation(input[position])) {
				char cur_op = input[position];
				int cur_pr = priority(input[position]);
				while (!operations.isEmpty() && isOperation(operations.peek()) && priority(operations.peek()) >= cur_pr) {
					get_res(operations.pop());
				}
				operations.push(cur_op);
			}
			else if (isDigit())
				digits.push(get_num());
			else if (input[position] == ' ') {
				++position;
				continue;
			}
			++position;
		}
		while (!operations.isEmpty()) {
			get_res(operations.pop()); 
		}
		return digits.peek();
	}
};


bool isRightBrackets(std::string_view s) {
	MyStack<char> stackForBrackets(s.size());
	for (const char& c : s) {
		switch (c) {
		case '(':
		case '{':
		case '[':
			stackForBrackets.push(c);
			break;
		case ')':
		case '}':
		case ']':
			if (!stackForBrackets.isEmpty()) {
				char ch = stackForBrackets.pop();
				if ((c == '}' && ch != '{') || (c == ']' && ch != '[') || (c == ')' && ch != '(')) {
					return false;
				}
			}
			else {
				return false;
			}
		default:
			break;
		}
	}
	if (!stackForBrackets.isEmpty()) {
		return false;
	}
	return true;
}

#endif // !INFIXTOPOSTFIX_H_
