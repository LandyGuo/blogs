# 规范Python程序配置文件读写 #
### 为了程序的规范性，推荐采用ConfigParser来读取配置文件 ###
在程序中常常需要去将一些经常修改的变量写到配置文件中，配置文件一般形式是这样的: 

```python
	[section1] 
	item1 = value1 
	item2 = value2 
	[section2] 
	item1 = value1 
	item2 = value2
```
 
有了section的好处是，不同section中可以有重名的变量(item,section下的每一项称为item)，这会给我们编程带来很多便利。下面是一个配置文件的实例: 

```python
	[gameGlobol]  
	gameTime=1.3             
	Flask=0.10.1 
	[time]      
	requests=2.3.0         
	M2Crypto=0.22.3 
```

自己去一行行读配置文件，获取每个item的名称和"="后面的值未免不够规范,直接用python提供的读配置文件的标准方法： 

```python
 
	import ConfigParser 	  
	config = ConfigParser.ConfigParser() 
	config.readfp(open("/home/qpguo/a.py", "rb"))//读取的配置文件的位置 
	print config.get("time", "M2Crypto") //获取time域下的项M2Crypto的值 
	print config.get("global","Flask")//获取global域下的项Flask的值
```
