// By xiplus
#include <bits/stdc++.h>
using namespace std;

void add(long long a, long long b) {
	cout << a << " + " << b << " = " << a + b << endl;
}
void sub(long long a, long long b) {
	cout << a << " - " << b << " = " << a - b << endl;
}
void mul(long long a, long long b) {
	cout << a << " * " << b << " = " << a * b << endl;
}
void div2(long long a, long long b) {
	cout << a << " / " << b << " = " << a / b << " ... " << a % b << endl;
}
typedef void (*ScriptFunction)(long long, long long);

struct div_0_exception {};

void error(int) {
	throw div_0_exception();
}

int main() {
	if (SIG_ERR == signal(SIGFPE, error)) {
		cerr << "failure to setup signal.";
		return 1;
	}

	map<char, ScriptFunction> func;
	func['+'] = add;
	func['-'] = sub;
	func['*'] = mul;
	func['/'] = div2;

	long long a, b;
	char c;
	cin >> a >> c >> b;
	cout << fixed << setprecision(4);
	try {
		func[c](a, b);
	} catch (div_0_exception) {
		cout << "ERROR" << endl;
	}

	return 0;
}
