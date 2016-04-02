# c++设计模式-装饰器模式 #

## 一、我对装饰器模式的理解##

### 1）通过包裹一个类(在该类的基础上，调用该类的方法，并加上一些附加的操作，并返回与该类继承自同一个基类的类(**调用装饰器前后可以用同样的基类指针进行接收**))###

**装饰器和被装饰的对象必须有完全一致的方法名**。只是在装饰器的方法中会调用被装饰对象的同名方法
如果装饰器和被装饰的对象方法名不一致，那么将导致装饰之后的结果不能再次被另外一个装饰器装饰(因为方法名已经变了) 

### 2）装饰器和待装饰的组件都继承自同一个基类，这点很重要 ###


## 二.装饰器模式的c++实现 ##

### 1、装饰器模板和组件(被装饰对象)的基类 ###
Base class：装饰器模式的基类，(被装饰对象)组件和装饰器模板都需要继承自基类

```cpp

	class Beverage
	{
	private:
	 std::string description;
	public:
	 Beverage() = default;
	 Beverage(std::string des) //构造方法为了让组件继承，而不是为了让装饰器继承
	 {
	  this->description = des;
	 }
	 virtual std::string getDescription() //让组件继承，而不是为了让装饰器继承
	 {
	  return description;
	 }
	 virtual float cost() = 0; //让子类组件实现
	};

```

### 2、组件的定义 ###
被装饰对象1：饮料1

```cpp

	class OrangeJuice :public Beverage
	{
	public:
	 OrangeJuice() :Beverage("Orange juice"){};
	 float cost() override //子类组件实现具体cost方法
	 {
	  return 1.99;
	 }
	};
```

被装饰对象2：饮料2

```cpp

	class AppleJuice :public Beverage
	{
	public:
	 AppleJuice() :Beverage("Apple juice"){};
	 float cost() override //子类组件实现具体cost方法
	 {
	  return 2.99;
	 }
	};

```


### 3、装饰器的定义 ###
#### 3.1装饰器模板的定义 ####
装饰器模板_特别注意：也要继承base

```cpp

	class Decorator :public Beverage
	{
	protected:
	 std::shared_ptr<Beverage> ptr; //装饰器要保存当前装饰对象的指针，注意只用申明指针，而不需要给对象分配空间
	public:
	 Decorator() = default;
	 Decorator(std::shared_ptr<Beverage> p)
	 {
	  ptr=p;
	 };
	 std::string getDescription() override = 0; //装饰器不继承Beverage的任何方法，把父类覆盖的同时让其本身成为一个抽象接口
	 float cost() override = 0; //装饰器不继承Beverage的任何方法，把父类覆盖的同时让其本身成为一个抽象接口
	};
```

#### 3.2具体装饰器的定义 ####

装饰器1：mocha

```cpp

	class Mocha :public Decorator
	{
	public:
	 Mocha(std::shared_ptr<Beverage> p) :Decorator(p){}; //相同的操作被抽象到基类中，直接委托给基类实现
	 std::string getDescription() override //注意：装饰器的所有函数都是在被装饰对象函数的基础上进行操作的，因此初始化一个装饰器需要保存其装饰对象的指针
	 {
	  return ptr->getDescription() + ";" + "Mocha";
	 }
	 float cost() override
	 {
	  return ptr->cost() + 0.4;
	 }
	};
```


装饰器2:Naiyou

```cpp

	class Naiyou :public Decorator
	{
	public:
	 Naiyou(std::shared_ptr<Beverage> p) :Decorator(p){};
	 std::string getDescription() override
	 {
	  return ptr->getDescription() + ";" + "Naiyou";
	 }
	 float cost() override
	 {
	  return ptr->cost() + 0.8;
	 }
	};
```

### 4、主函数:运用装饰器模式装饰对象 ###

```cpp

	#include "Beverage.h"
	#include <iostream>
	
	using namespace	std;
	int main()
	{
	/*生成OrangeJuice和AppleJuice的对象,用基类对象指针指向*/
	 shared_ptr<Beverage> orangeJuice = make_shared<OrangeJuice>();
	 shared_ptr<Beverage> appleJuice = make_shared<AppleJuice>();
	/*生成Mocha对象，传入orangeJuice智能指针初始化(若传普通指针会报错)，这样就Mocha对象就会装饰orangeJuice*/
	 shared_ptr<Beverage> orangeJuiceWithMocha = make_shared<Mocha>(orangeJuice);
	 shared_ptr<Beverage> orangeJuiceWithNaiyou = make_shared<Naiyou>(orangeJuice);
	 shared_ptr<Beverage> orangeJuiceWithNaiyouAndMocha = make_shared<Naiyou>(orangeJuiceWithMocha);
	
	 cout << "description:" << orangeJuiceWithMocha->getDescription() << endl
	  << orangeJuiceWithMocha->cost() << endl;
	
	 cout << "description:" << orangeJuiceWithNaiyou->getDescription() << endl
	  << orangeJuiceWithNaiyou->cost() << endl;
	
	 cout << "description:" << orangeJuiceWithNaiyouAndMocha->getDescription() << endl
	  << orangeJuiceWithNaiyouAndMocha->cost() << endl;
	
	 system("pause");
	}
```

**编程经验**：

1）把子类中可能通用的操作尽可能放在父类中

2）C++中最好全部使用智能指针，而不要将传统指针和智能指针混用

3)不能把普通指针转换为智能指针，但智能指针可以转换为普通指针，所以要尽可能用智能指针
