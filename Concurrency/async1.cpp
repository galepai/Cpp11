//在VS2013运行通过

#include <future>
#include <thread>
#include <chrono>
#include <random>
#include <iostream>
#include <exception>


int doSomething(char c)
{
	std::default_random_engine dre(c);
	std::uniform_int_distribution<int> id(10, 1000);

	for (int i = 0; i < 10; i++){
		std::this_thread::sleep_for(std::chrono::milliseconds(id(dre)));
		std::cout.put(c).flush();
	}

	return c;
}

int func1()
{
	return doSomething('.');
}

int func2()
{
	return doSomething('+');
}
/*
int main()
{
	std::cout << "staring func1() in background"
		<< "and func2() in foreground:" << std::endl;

	//立即以异步方式启动目标函数（开启新线程）
	//std::future<int> result1(std::async(std::launch::async, func1));

	//以异步方式开启目标函数（开启新线程），延缓执行func1()直到对result调用get()
	std::future<int> result1(std::async(std::launch::deferred,func1));
	
	int result2 = func2();

	int result = result1.get() + result2;

	std::cout << std::endl << "result of func1() + func2():"
		      << result << std::endl;

	system("PAUSE");

	return 0;
}
*/