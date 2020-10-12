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
/* (�ǽ� 1-1) �м���� : 
Executed in B
Destructor execution: B
Executed in A
Destructor execution: A 

�� ����� ���� ������ ���� ���ι����� funcA �Լ��� ȣ���ߴ�.
funcA�Լ��� A��� ���ڸ� ID�� ������ test ��ü�� ������� funcB �Լ��� ȣ���Ѵ�.
funcB�Լ��� B��� ���ڸ� ID�� ������ teat ��ü�� ����� excuted in b�� �ܼ�â�� ����Ѵ�.
�� �� funcB�Լ��� ����Ǹ鼭 funcB�Լ� �ȿ� �ִ� ��ü�� �Ҹ�Ǹ鼭 Destructor execution: B �� ����Ѵ�.
funcA �Լ����� funcB�� ȣ���ؼ� funcB �Լ��� �������Ƿ� �� �������� ���� std::cout << "Executed in A" << std::endl;�� ����Ѵ�.
�� �� funcA�Լ��� ����ǰ� ���ι����� ���ƿ� funcA ���� �ٺ��� ����ǳ� �������� �����Ƿ� ���α׷��� �����Ѵ�.
*/


/* (�ǽ� 1-2) �м���� : Destructor execution: B
Destructor execution: A
Exception : Exception from funcB!funcA�Լ��� A��� ���ڸ� ID�� ������ test ��ü�� ������� funcB �Լ��� ȣ���Ѵ�.funcB�Լ��� B��� ���ڸ� ID�� ������ teat ��ü�� ����� runtime error�� ���ٰ� throw ���ش�.
�� ���Ŀ� ���� ������� �������� �ʰ� �ٷ� catch������ ����. �� �������� �տ� ��������� B��ü�� A��ü���� �Ҹ��ϸ鼭 Destructor execution: B
Destructor execution: A�� ����Ѵ�.
catch������ throw���� ���� ���ڷ� �޾� Exception : Exception from funcB!�� ������ش�.
*/