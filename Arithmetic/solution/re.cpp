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

int main() {
	map<char, ScriptFunction> func;
	func['+'] = add;
	func['-'] = sub;
	func['*'] = mul;
	func['/'] = div2;

	long long a, b;
	char c;
	cin >> a >> c >> b;
	cout << fixed << setprecision(4);
	func[c](a, b);

	return 0;
}
