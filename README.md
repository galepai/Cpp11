# C++11

主要研究C++11的并发，多线程。

文件夹
  Concurrency 并发

***************************************************************************
std::future介绍

简单地说，std::future 可以用来获取异步任务的结果，因此可以把它当成一种简单的线程间同步的手段。std::future 通常由某个 Provider 创建，你可以把 Provider 想象成一个异步任务的提供者，Provider 在某个线程中设置共享状态的值，与该共享状态相关联的 std::future 对象调用 get（通常在另外一个线程中） 获取该值，如果共享状态的标志不为 ready，则调用 std::future::get 会阻塞当前的调用者，直到 Provider 设置了共享状态的值（此时共享状态的标志变为 ready），std::future::get 返回异步任务的值或异常（如果发生了异常）。
 
一个有效(valid)的 std::future 对象通常由以下三种 Provider 创建，并和某个共享状态相关联。Provider 可以是函数或者类，其实我们前面都已经提到了，他们分别是：
 •std::async 函数，本文后面会介绍 std::async() 函数。
 •std::promise::get_future，get_future 为 promise 类的成员函数。
 •std::packaged_task::get_future，此时 get_future为 packaged_task 的成员函数。
 
一个 std::future 对象只有在有效(valid)的情况下才有用(useful)，由 std::future 默认构造函数创建的 future 对象不是有效的（除非当前非有效的 future 对象被 move 赋值另一个有效的 future 对象）。
 
 在一个有效的 future 对象上调用 get 会阻塞当前的调用者，直到 Provider 设置了共享状态的值或异常（此时共享状态的标志变为 ready），std::future::get 将返回异步任务的值或异常（如果发生了异常）。

***************************************************************************
std::packaged_task介绍

std::packaged_task 包装一个可调用的对象，并且允许异步获取该可调用对象产生的结果，从包装可调用对象意义上来讲，std::packaged_task 与 std::function 类似，只不过 std::packaged_task 将其包装的可调用对象的执行结果传递给一个 std::future 对象（该对象通常在另外一个线程中获取 std::packaged_task 任务的执行结果）。
 
std::packaged_task 对象内部包含了两个最基本元素:
一、被包装的任务(stored task)，任务(task)是一个可调用的对象，如函数指针、成员函数指针或者函数对象;
二、共享状态(shared state)，用于保存任务的返回值，可以通过 std::future 对象来达到异步访问共享状态的效果。
 
可以通过 std::packged_task::get_future 来获取与共享状态相关联的 std::future 对象。在调用该函数之后，两个对象共享相同的共享状态，具体解释如下：
 •std::packaged_task 对象是异步 Provider，它在某一时刻通过调用被包装的任务来设置共享状态的值。
 •std::future 对象是一个异步返回对象，通过它可以获得共享状态的值，当然在必要的时候需要等待共享状态标志变为 ready.
 
std::packaged_task 的共享状态的生命周期一直持续到最后一个与之相关联的对象被释放或者销毁为止。
