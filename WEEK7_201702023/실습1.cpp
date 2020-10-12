#include <iostream>
#include <stdexcept>
class Test {
public:

	Test(char id) : id_(id) {}

	~Test() {
		std::cout << "Destructor execution: "

			<< id_ << std::endl;
	}
private:

	char id_;
};
int funcB() {

	Test r('B');
	throw std::runtime_error("Exception from funcB!\n");
	std::cout << "Executed in B" << std::endl;
	return 0;
}
int funcA() {

	Test r('A');

	funcB();

	std::cout << "Executed in A" << std::endl;

	return 0;
}
int main() {

	try {

		funcA();

	}

	catch (std::exception& e) {

		std::cout << "Exception : " << e.what();

	}
}
/* (실습 1-1) 분석결과 : 
Executed in B
Destructor execution: B
Executed in A
Destructor execution: A 

이 결과가 나온 이유는 먼저 메인문에서 funcA 함수를 호출했다.
funcA함수는 A라는 글자를 ID로 가지는 test 객체를 만들었고 funcB 함수를 호출한다.
funcB함수는 B라는 글자를 ID로 가지는 teat 객체를 만들고 excuted in b를 콘솔창에 출력한다.
그 후 funcB함수가 종료되면서 funcB함수 안에 있던 객체가 소멸되면서 Destructor execution: B 를 출력한다.
funcA 함수에서 funcB를 호출해서 funcB 함수가 끝났으므로 그 다음문장 으로 std::cout << "Executed in A" << std::endl;를 출력한다.
그 후 funcA함수도 종료되고 메인문으로 돌아와 funcA 다음 줄부터 실행되나 다음줄이 없으므로 프로그램을 종료한다.
*/


/* (실습 1-2) 분석결과 : Destructor execution: B
Destructor execution: A
Exception : Exception from funcB!funcA함수는 A라는 글자를 ID로 가지는 test 객체를 만들었고 funcB 함수를 호출한다.funcB함수는 B라는 글자를 ID로 가지는 teat 객체를 만들고 runtime error가 났다고 throw 해준다.
그 이후에 대한 문장들은 실행하지 않고 바로 catch문으로 간다. 그 과정에서 앞에 만들어졌던 B객체와 A객체들은 소멸하면서 Destructor execution: B
Destructor execution: A를 출력한다.
catch문에서 throw해준 값을 인자로 받아 Exception : Exception from funcB!를 출력해준다.
*/