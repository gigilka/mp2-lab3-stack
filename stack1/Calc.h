#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include "Stack.h"
using namespace std;

class Calc {
	string exp;
	string post;
	TStack<char> stc;
	TStack<double> stdo;
	int priority(char op);
public:
	Calc();
	~Calc();
	Calc(const Calc& smt);
	Calc& operator=(const Calc& smt);
	void SetExp(string exp);
	string GetExp();
	string GetPost();
	bool CheckExp();
	void PostEdit();
	double CalcPost();
	double Calculate();
};
int Calc::priority(char op) {
	switch(op){
	case '(': return 0;
	case '+': return 1;
	case '-': return 1;
	case '*': return 2;
	case '/': return 2;
	case '^': return 3;
	}
	return 0;
}
Calc::Calc() {}
Calc::~Calc() {}
Calc::Calc(const Calc& smt) {
	exp = smt.exp;
	post = smt.post;
}
Calc& Calc::operator=(const Calc& smt) {
exp = smt.exp;
post= smt.post;
return *this;
}
void Calc::SetExp(string expr) {
	exp = expr;
}
string Calc::GetExp() {
	return exp;
}
string Calc::GetPost() {
	return post;
}
bool Calc::CheckExp() {
	for (int i = 0; i < exp.size(); i++) {
		if (exp[i] == '(') {
			stc.Push(exp[i]);
		}
		else if (exp[i] == ')') {
			if (stc.IsEmpty()) {
				return false;
			}
			else(stc.Pop());
		}
	}
	return stc.IsEmpty();
}
void Calc::PostEdit() {
	string in = "(" + exp + ")";
	post = "";
	stc.Clear();
	for (int i = 0; i < in.size(); i++) {
		if (isdigit(in[i])) {
			size_t idx;
			double tmp = stod(&in[i], &idx);
			ostringstream ss;
			ss << tmp;

			post += ss.str();
			post += " ";
			i += idx - 1;
		}
		else if (in[i] == '(') {
			stc.Push(in[i]);
		}
		else if (in[i] == ')') {
			while (stc.Top() != '(') {
				post += stc.Pop();
				post += " ";
			}
			stc.Pop();
		}
		else if (in[i] == '+' || in[i] == '-' || in[i] == '*' || in[i] == '/' || in[i] == '^') {
			while (priority(in[i]) <= priority(stc.Top())) {
				post += stc.Pop();
				post += " ";
			}
			stc.Push(in[i]);
		}
	}
	if (!post.empty()) {
		post.pop_back();
	}
}
double Calc::CalcPost() {
	if (post.empty()) {
		throw "Empty postfix";
	}
	for (int i = 0; i < post.size(); i++) {
		if (isdigit(post[i])) {
			size_t idx;
			double tmp = stod(&post[i], &idx);
			stdo.Push(tmp);
			i += idx - 1;
		}
		if (post[i] == '+' || post[i] == '-' || post[i] == '*' || post[i] == '/' || post[i] == '^') {
			double first, second;
			if (!stdo.IsEmpty()) {
				second = stdo.Pop();
			}
			else {
				throw "Postfix operations overflow";
			}

			if (!stdo.IsEmpty()) {
				first = stdo.Pop();
			}
			else {
				throw "Postfix operations overflow";
			}

			switch (post[i]) {
			case '+':
				stdo.Push(first + second);
				break;
			case '-':
				stdo.Push(first - second);
				break;
			case '*':
				stdo.Push(first * second);
				break;
			case '/':
				stdo.Push(first / second);
				break;
			case '^':
				stdo.Push(pow(first, second));
				break;
			}
		}
	}
	if (!stdo.IsEmpty()) {
		double result = stdo.Pop();
		if (!stdo.IsEmpty()) {
			throw "Operands overflow";
		}
		return result;
	}
	else {
		throw "Operands is missing";
	}
}
double Calc::Calculate() {
	string in = "(" + exp + ")";
	stdo.Clear();
	stc.Clear();
	for (int i = 0; i < in.size(); i++) {
		if (in[i] == '(') {
			stc.Push(in[i]);
		}
		else if (isdigit(in[i])) {
			size_t idx;
			double tmp = stod(&in[i], &idx);
			stdo.Push(tmp);
			i += idx - 1;
		}
		else if (in[i] == '+' || in[i] == '-' || in[i] == '*' || in[i] == '/' || in[i] == '^') {
			while (priority(in[i]) <= priority(stc.Top())) {
				double first, second;
				if (!stdo.IsEmpty()) {
					second = stdo.Pop();
				}
				else {
					throw "Operations overflow";
				}

				if (!stdo.IsEmpty()) {
					first = stdo.Pop();
				}
				else {
					throw "Operations overflow";
				}
				char oper = stc.Pop();

				switch (oper) {
				case '+':
					stdo.Push(first + second);
					break;
				case '-':
					stdo.Push(first - second);
					break;
				case '*':
					stdo.Push(first * second);
					break;
				case '/':
					stdo.Push(first / second);
					break;
				case '^':
					stdo.Push(pow(first, second));
					break;
				}
			}
			stc.Push(in[i]);
		}
		else if (in[i] == ')') {
			while (stc.Top() != '(') {
				double first, second;
				if (!stdo.IsEmpty()) {
					second = stdo.Pop();
				}
				else {
					throw "Operations overflow";
				}

				if (!stdo.IsEmpty()) {
					first = stdo.Pop();
				}
				else {
					throw "Operations overflow";
				}
				char oper = stc.Pop();

				switch (oper) {
				case '+':
					stdo.Push(first + second);
					break;
				case '-':
					stdo.Push(first - second);
					break;
				case '*':
					stdo.Push(first * second);
					break;
				case '/':
					stdo.Push(first / second);
					break;
				case '^':
					stdo.Push(pow(first, second));
					break;
				}
			}
			stc.Pop();
		}
	}

	if (!stdo.IsEmpty()) {
		double result = stdo.Pop();
		if (!stdo.IsEmpty()) {
			throw "Operands overflow";
		}
		return result;
	}
	else {
		throw "Operands is missing";
	}
}