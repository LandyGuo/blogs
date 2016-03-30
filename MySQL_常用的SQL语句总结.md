# 这是根据最近的工作，整理了一下经常用的SQL语句，等到忘记的时候再回来看看O(∩_∩)O~ #

**这是SQL实际应用的基础教程，如果对SQL原理不是很清晰的童鞋请先了解下SQL的基本操作原理**


## 一、基本用法： ##
 CREATE
-
```sql
    CREATE TABLE IF NOT EXISTS table1(id INTEGER PRIMARY KEY, name varchar(100));
``` 

 INSERT 
- 
```sql
    /*向SQL表中插入数据:若插入时不指定数据会默认为NULL*/
    INSERT INTO table1 (id,name ) VALUES(3,'tom');
	/*向字符串中插入数据*/
    SELECT INSERT('1244',1,2,'dd');
```
UPDATE
- 
```sql
    /*更新一个字段*/
    UPDATE table1 SET name = 'Tom' WHERE id = 2;
    /*更新时表中所有字段信息都可以作为已知量来处理*/
    UPDATE table1 SET id = id +3 WHERE id =2;
    UPDATE table1 SET name = CONCAT(name,'abc') where id= 5;
    update person set departmentId = id % 4 +1;
```

SELECT
- 
```sql
	/*判断某个字段是否为NULL*/
	SELECT id,(case when ISNULL(name) then "没有数据" ELSE name END ) as 'Info' FROM table1;
	/*组合条件选择:找Id在2-4之间的数据*/
	select id from (SELECT id,name FROM table1 WHERE id >= 2 AND id<=10) as t where id != 4 or id>6;
	/*数据删除delete只删除表中数据，drop连同表一起删除*/
```
DELETE
- 
```sql
	DELETE FROM table1;
	DROP TABLE testdata;
```
## 二、具体应用实例 ##


###新建一个person表，并插入数据###
```sql
    	/*新建person表*/
    	CREATE TABLE IF NOT EXISTS person(id INTEGER PRIMARY KEY AUTO_INCREMENT,name varchar(20),slary float, IN_year date);
    	/*插入测试数据*/
    	INSERT INTO person(name,slary,IN_year) VALUES('tom',2800,curdate());
    	INSERT INTO person(name,slary,IN_year) VALUES('Jim',3100,curdate() - interval 20 day);
    	INSERT INTO person(name,slary,IN_year) VALUES('carry',4200,curdate() - interval 30 day);
    	INSERT INTO person(name,slary,IN_year) VALUES('fat',5400,curdate()- interval 600 day);
    	INSERT INTO person(name,slary,IN_year) VALUES('gay',3300,curdate() - interval 800 day);
```
###显示时修改列备注 ###
```sql
	SELECT name as '姓名', slary as '薪水',IN_year as '入职年份' FROM person;
```
	
### 查询表中的一些统计信息 ###
```sql
	/*获得表中数据总条数*/
	SELECT COUNT(*) FROM person;
	/*获得表中工资的最大，最小和平均*/
	select MIN(slary) as '最低工资', MAX(slary) as '最高工资', avg(slary) as '平均工资' from person;
	/*数据排序*/
	select id ,name,slary from person ORDER BY slary ASC;
	/*将工资在2800-4500的优先按id递增排序,若id相同则按slary递减排序*/
	select id,name,slary from person where slary>=2800 and slary<=4500 ORDER BY id ASC,slary DESC;
```

### 通配符匹配，_单通配符匹配，%多通配符匹配 ###
```sql
	/*查找name以m结尾的项*/
	SELECT name FROM person WHERE name LIKE '%m';
	/*查找name中间有一个字符未知的*/
	SELECT name,slary FROM person where name like 'g_y';
```
### 多值匹配 ###
```sql
	SELECT id,name from person where id IN(2,3,4)
	SELECT id,name from person where id BETWEEN 2 AND 4;
```
###数据统计，筛选###
```sql
	/*将id<9的同一个人的各项工资加起来*/
	SELECT name,SUM(slary) FROM person where id<9 GROUP BY name;
	/*当有group by 语句时，select 和 having这里都是对分组后的每组数据而言的*/
	/*where对原始数据进行过滤,Having对分组后的数据进行过滤*/
	SELECT name,SUM(slary) FROM person where id<9 GROUP BY name HAVING SUM(slary)>=8600;
	/*分页时用于筛选范围的数据长度,表示从1开始的后面的2个数据*/
	select id from person limit 1,2;
```

### 更改表中字段数据  ###
```sql
	/*在表中增加一个字段department*/
	ALTER TABLE person ADD department VARCHAR(100);
	/*在person中新加字段departmentId,并设置缺省值0*/
	ALTER TABLE person ADD departmentId int DEFAULT 0;
	/*在表中删除一个已有的字段department*/
	ALTER TABLE person DROP  department;
	/*去除重复的数据，duplicate对所有字段的整体有效*/
	SELECT DISTINCT id,slary FROM person
```
## 三、更多的一些用法 ##
### 重新生成测试数据 ###
```sql
	CREATE TABLE IF NOT EXISTS department(departNumber INT PRIMARY KEY AUTO_INCREMENT,departName varchar(100));
	INSERT INTO department(departName) VALUES('IT');
	INSERT INTO department(departName) VALUES('sales');
	INSERT INTO department(departName) VALUES('service');
	INSERT INTO department(departName) VALUES('management');
```
### 表连接操作 ###
将person表和department表根据departmentId字段进行连接
注意:使用join进行拼接时，select t1.字段，t2.字段 from (table1 as t1 join table2 as  t2 on t1.字段=t2.字段
```sql
	select name,slary,departmentId,d.departName from (person  as p JOIN  department as d ON p.departmentId = d.departNumber)
```
union将第一个查询的数行结果与第二个查询的数行结果在列方向上进行拼接,要求每个查询将拼接在一起的对应列应为相容的类型,如果不加ALL会有去重
```sql
	select * from department
	UNION  ALL
	select id,name from person;
```
### SQL中关于日期的处理 ###
```sql
	select DATE_ADD(now(),INTERVAL 2 DAY)
	select DATEDIFF(date(now()),date('2014-08-05'))
	SELECT DATE_SUB(NOW(),INTERVAL -2 MINUTE)
	select DAYOFMONTH(date('2014-09-23'))
```
### 关于case when的使用 ###
```sql
	SELECT id,name,(case when slary<3500 then '低收入'
	when slary>3500 and slary<5000 then '正常收入'
	else '高收入'
	END) as '收入水平' from person;
```

### 关于索引的操作 ###
```sql	
	/*创建单个普通索引*/
	ALTER TABLE person ADD INDEX my_index(name);
	/*同时创建多个字段组合的索引*/
	ALTER TABLE person ADD INDEX multi_INDEX(id,name,slary);
	/*创建唯一索引*/
	Alter TABLE department ADD UNIQUE(departNumber);
	/*添加主键索引*/
	/*添加主键索引*/
	Alter table department add PRIMARY key(departName)
```

## 四、说了这么多，一起来练习一下吧O(∩_∩)O~ ##
根据以下语句创建SQL表：
```sql
	CREATE TABLE IF NOT EXITS EX3(num varchar(10) primary key,price int);
	INSERT INTO EX3(num,price) values('Rk1',10);
	INSERT INTO EX3(num,price) values('Rk2',20);
	INSERT INTO EX3(num,price) values('Rk3',-30);
	INSERT INTO EX3(num,price) values('Rk4',-10);
```
写出输出以下格式的SQL语句:
```sql
	单号 收入 支出
	Rk1 10 0
	Rk2 20 0
	Rk3 0 30
	Rk4 0 10
```
注意: 采用case when 时一定要记得加end
```sql
	select num as '单号',case when ex3.price>0 then price else 0 end as '收入',case when price<0
	then ABS(price) else 0 end as '支出' from ex3;
```
再来一个练习，已有根据以下SQL语句创建的表：
```sql
	CREATE TABLE T_SCORES(Datet date,Name varchar(10), Score varchar(10));
	INSERT INTO T_SCORES(Datet ,Name,Score) values(date('2008-08-08','拜仁','胜'));
	INSERT INTO T_SCORES(Datet ,Name,Score) values(date('2008-08-09','奇才','胜'));
	INSERT INTO T_SCORES(Datet ,Name,Score) values(date('2008-08-09','湖人','胜'));
	INSERT INTO T_SCORES(Datet ,Name,Score) values(date('2008-08-10','拜仁','负'));
	INSERT INTO T_SCORES(Datet ,Name,Score) values(date('2008-08-08','拜仁','负'));
	INSERT INTO T_SCORES(Datet ,Name,Score) values(date('2008-08-12','奇才','胜'));
```
写出输出以下格式的sql语句：
```sql
	Name 胜 负
	拜仁 1 2
	湖人 1 0
	奇才 2 0
```
注意:sum()是怎样作用于每一项的
```sql
	SELECT Name,SUM(case when Score='胜' then 1 else 0 end) as '胜',
	SUM(case when Score='负' then 1 else 0 end) as '负' from t_scores
	GROUP BY Name
```

