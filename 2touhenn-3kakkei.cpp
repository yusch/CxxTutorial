#include <iostream>
 void put_stars(int n)
{
	while (n-- > 0)
		std::cout << '*';
}
int main(){
	int n;

	std::cout << "左下直角の二等辺三角形を表示します．";
	std::cout << "段数を入力してください．";

	std::cin >> n;

	for (int i = 1; i <= n; i++){
		put_stars(i);
		std::cout << '\n';
	}
}
