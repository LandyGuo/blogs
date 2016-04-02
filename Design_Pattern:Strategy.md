# 设计模式-策略模式(c++实现) #
策略模式核心思想：
 	定义算法家族，将不同的算法封装起来，使得算法彼此之间可以相互替换

实现方法：
提供接口作为基类，让派生类（算法）绑定在基类对象上，通过调用基类对象来调用不同派生类的方法,从而实现面向接口编程

以下是用我用C++写的一个小demo:

给出两个接口Iflyable和IQuackable，然后每种接口都提供两种策略来实现。主程序在不同的实现策略组合中进行切换

## Iflyable接口##

### 1）接口Iflyable接口定义 ###

```cpp

	class Iflyable
	{
	public:
	 virtual void fly() = 0; //在c++中用纯虚函数来当接口用
	 Iflyable()=default;
	 ~Iflyable()=default;
	};
```

### 2）实现接口Iflyable的策略###

#### Iflyable实现策略一： ####

```cpp

	class flyWithWing :public Iflyable
	{
	public:
	 void fly() override
	 {
	  using std::cout;
	  cout << "I can fly with my wing" << std::endl;
	 };
	 flyWithWing() = default;
	 ~flyWithWing() = default;
	};
```

#### Iflyable实现策略二： ####

```cpp

	class flywithRocket :public Iflyable
	{
	public:
	 void fly() override
	 {
	  using std::cout;
	  cout << "I can fly with a rocket" << std::endl;
	 };
	 flywithRocket() = default;
	 ~flywithRocket() =default;
	};

```

## IQuackable接口 ##


### 1）IQuackable接口定义 ###

```cpp

	class IQuackable
	{
	public:
	 virtual void quack()=0; //纯虚函数当接口
	 IQuackable()=default;
	 ~IQuackable()=default;
	};
```


### 2）实现接口IQuackable的策略###

#### IQuackable实现策略一： ####

```cpp

	class Quackgua :public IQuackable
	{
	public:
	 void quack() override
	 {
	  std::cout << "I can gua gua gua" << std::endl;
	 };
	 Quackgua()=default;
	 ~Quackgua()=default;
	};
```



#### IQuackable实现策略二： ####
```cpp

	class QuackLalala :public IQuackable
	{
	public:
	 void quack() override
	 {
	  std::cout << "I can quack lalala"<<std::endl;
	 };
	 QuackLalala() = default;
	 ~QuackLalala() = default;
	};

```

## 调用IQuackable接口和Iflyable接口的对象##
###调用接口对象基类定义：###
Duck.h

```cpp

	#pragma once
	#include "Iflyable.h"
	#include "IQuackable.h"
	class Duck
	{
	protected:
	 Iflyable* flyability; //两个接口，对接口进行编程
	 IQuackable* quackablity;
	public:
	 void setFlyBehavior(Iflyable* fly)//可以动态更改接口行为
	 {
	  flyability = fly;
	 };
	 void setQuackBehavior(IQuackable* quack)
	 {
	  quackablity = quack;
	 };
	
	 void performFly() //与对象无关的通用操作，写在基类中
	 {
	  flyability->fly();
	 };
	 void performQuack() //与对象无关的通用操作，写在基类中
	 {
	  quackablity->quack();
	 };
	
	 virtual void display() = 0; //纯虚函数，具体实现不清楚，因此交给子类去实现
	
	 Duck() = default;
	 ~Duck()=default;
	
	};
```

###调用接口对象的定义：###

```cpp

	class XiangpiDuck :public Duck
	{
	public:
	 XiangpiDuck()=default;
	 ~XiangpiDuck()=default;
	 void display() override
	 {
	  std::cout << "I am a xiangpiDuck" << std::endl;
	 }
	};

```

## 主程序：使用策略模式进行不同策略调整与组合##

```cpp

	#include "Duck.h"
	#include "Iflyable.h"
	#include "IQuackable.h"
	#include <memory>
	using namespace  std;
	int main()
	{
	 shared_ptr<Duck> p = make_shared<XiangpiDuck>();
	/*选择不同的方法相当于选择不同的策略——策略模式*/
	 p->setFlyBehavior(new flywithRocket()); //这里的行为可以动态更改
	 p->setQuackBehavior(new QuackLalala()); //这里的行为可以动态更改
	/*下面都是通用操作*/
	 p->display();
	 p->performFly();
	 p->performQuack();
	 system("pause");
	}

```

关于C++编程中注意的地方：

**在C++编程中通常为了简便，直接把对象的实现也放在头文件中，这是可以的~
但是要切记，如果想只引入头文件就引入相应的对象，一定要确保类中所有的函数都是有方法体的，
即使是空的方法体也可以，但C++不允许申明一个没有方法体的成员函数。**

