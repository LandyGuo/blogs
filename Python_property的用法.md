# Python_property的用法 #

最近因为项目原因一直在python和c++中切换，记下一些python的基本用法，以免以后忘记(不过肯定会忘的哈哈。。)~~
## 1.属性可以拦截对普通成员变量的访问和设值 ##

示例：

```python

	class TestClass(object):	   
	    def __init__(self,age):
	        self._age = age
	   
	    @property #用property装饰器来指明该方法表示属性，随后该方法会被隐藏，下次再调用TestClass().age()会出错，因为age已经是属性了
	    def age(self):
	        return self._age
	   
	    @age.setter #用age.setter装饰器来拦截对属性的设值，可以在这里加上对属性的设值逻辑
	    def age(self,val):
	        if val >100:
	            raise Exception("Too old")
	        self._age = val
	
	    @age.getter#用age.getter装饰器来拦截对属性的访问，可以在这里加上对属性的访问控制逻辑(一般不需要)
	    def age(self):
	        return self._age
```

## 2.在主程序中调用属性访问和赋值方法 ##

```python
	if __name__=="__main__":
	    test = TestClass(20)
	    test.age = 150 #调用属性赋值方法
	    print("age:{}".format(test.age))#调用属性访问方法
```
