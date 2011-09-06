//InComplete.
//filename: RE_to_NFA_ver3.cpp
//Fixed: to eliminate the info of overlapping states/node (which are due to dot operation eg.  ab. in postfix)
//Assumptions: 1. Input expression is infix. Example: b.c/(a/b)*.a.b.(c)*
//2. Concatenation OR Dot operator is explicitly entered.
//3. Expression is correct
//4. Precedence of * (Kleene-Closure) is higher and other operators ( / . ) have same precedence.

#include<iostream>
#include"InfixToPostfixForRE.cpp" 
#include<stack>
using namespace std;
string convert(string, int&);
class RegEx{
public:
	RegEx(string reg, int st, int en):re(reg), start(st), end(en){}
	static int nextNodeNum;
	int start, end;
	string re;
};
int RegEx::nextNodeNum = 0;
int existsInCopy(const int& node, const vector<int>& copy){
	for(int i=0; i<copy.size(); i++)
		if(copy[i] == node)
			return 1;
	return 0;
}
void solve(string re){//input: postfix expression
     
	int table[50][4];//table[i][j] : ith node with input as jth symbol. j =0 means a, =1 b, =2,3 epsilon
	memset(table, -1, 50*4*sizeof(int));
	vector<int> copy;//to store the info of overlapping states/node (which are due to dot operation eg.  ab. in postfix)
	//copy the states mentioned into state-1
	stack<RegEx> stk;
	for(int i=0; re.at(i) != '#'; i++){
		switch(re.at(i)){
			case '*':{
				RegEx a(stk.top());
				stk.pop();
				table[a.end][2] = a.start;
				int state1 = (RegEx::nextNodeNum)++;
				table[state1][2] = a.start;
				a.start = state1;
				
				int state2 = (RegEx::nextNodeNum)++;
				table[a.end][3] = state2;
				table[state1][3] = state2;
				a.end = state2;
				a.re += "*";
				stk.push(a);
				break;	}
			case '.':{
				RegEx b(stk.top()); stk.pop();
				RegEx a(stk.top()); stk.pop();
				table[a.end][2] = b.start;
				stk.push(RegEx(a.re+b.re+".", a.start, b.end));
				copy.push_back(b.start); 
				break;}
			case '/':{
				RegEx b(stk.top()); stk.pop();
				RegEx a(stk.top()); stk.pop();
                int state1 = (RegEx::nextNodeNum)++;
				int state2 = (RegEx::nextNodeNum)++;
				table[state1][2] = a.start;
				table[state1][3] = b.start;
				table[a.end][2] = state2;
				table[b.end][2] = state2;
				stk.push(RegEx(a.re +b.re+"/", state1, state2));
				break;}
			default://make RegEx object and push it into stk
				{
                 int state1 = (RegEx::nextNodeNum)++;
				int state2 = (RegEx::nextNodeNum)++;
				//RegEx a(re[i], (RegEx.nextNodeNum)++, (RegEx.nextNodeNum)++);
				table[state1][re.at(i) - 'a'] = state2;
				RegEx b(re[i]+"", state1, state2);
				stk.push(b);	}
		}
	}
	
	//remove states specified in map copy
	for(int i=0; i<copy.size(); i++){
		int tmp_state = copy[i];
		table[tmp_state-1][0] = table[tmp_state][0];
		table[tmp_state-1][1] = table[tmp_state][1];
		table[tmp_state-1][2] = table[tmp_state][2];
		table[tmp_state-1][3] = table[tmp_state][3];
	}	
	
	cout<<"Start state is "<<stk.top().start<<"\nEnd state is "<<stk.top().end<<"\n";
	cout<<" Node\t a\t b\t E\n------\t---\t---\t---\n";
	for(int node =0 ; node < RegEx::nextNodeNum; node++){
		if(existsInCopy(node, copy))
			continue;
		cout<<node<<"\t";
		(table[node][0] == -1)?(cout<<char(176)):(cout<<table[node][0]); cout<<"\t";
		(table[node][1] == -1)?(cout<<char(177)):(cout<<table[node][1]); cout<<"\t";
        (table[node][2] != -1)?(cout<<table[node][2]):(cout<<char(178));
        if(table[node][3] != -1)
			cout<<", "<<table[node][3];
        cout<<"\n";
	}
}
int main(){
	string in;
	cin>>in;
	int i=0;

	string re_postfix = convert(in + ')', i);
	cout<<"Postfix: "<<re_postfix<<"\n";
	solve(re_postfix+"#" );
	
	fflush(stdin);
	getchar();
	return 0;
}

