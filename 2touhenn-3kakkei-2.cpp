#include <iostream>
 void put_stars(int c, int n)
{
	while (n-- > 0)
		std::cout << c;
}
int main(){
	int n;

	std::cout << "";
	std::cout << "段数を入力してください．";

	std::cin >> n;

	for (int i = 1; i <= n; i++){
		put_stars(' ', n-1);
		put_stars('*', i);
		std::cout << '\n';
	}
}
