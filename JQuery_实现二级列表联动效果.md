# JQuery_实现二级列表联动效果 #
在很多填个人信息网页中，往往要根据用户前面的选择项，动态的去改变下一个选择项的选项，这就是二级列表联动效果，下面是我用Jquery做了一个简单的联动效果代码：

```HTML

	<html>
	<head>
		<title>下拉列表框联动</title>
		<script src="http://libs.baidu.com/jquery/1.9.1/jquery.min.js"></script>
		<script type="text/javascript">
		//实现下拉选框的二级联动，当选择select1的值为1时，select2的选项为11和12；当选择select1的值为2时，select2的选项为21和22；
		function appendToOption(textk,v,selected)
		{
			var obj = $("<option>").text(textk).val(v);
			if(selected)
			{
				obj.attr("selected","true");
			}
			obj.appendTo($("#select2"));
		}
		//根据第一个框的选项获取第二个下拉框的可选值
		function getItemsToAppend(selectedValue)
		{
			var options = new Array();
			if(selectedValue=="1")
			{
				options.push("11","12");
			}
			else if(selectedValue=="2")
			{
				options.push("21","22");
			}
			else
			{
				options.push("31","32");
			}
			return options;
	
		}
		//用console.log进行调试
		$(function(){
			$("#select1").change(function(){
				var selectedValue = $("#select1 option:selected").val();
				var items = getItemsToAppend(selectedValue);
				console.log(items);
				$("#select2 option").remove();
				for (var i in items) {
					appendToOption(items[i],items[i],(i==0)?true:false);
				};
			});
			});
	
		</script>
	</head>
	<body>
	<div id="test">
		<select name="select1" id="select1">
			<option value="1" selected="selected">1</option>
			<option value="2">2</option>
			<option value="3">3</option>
		</select></div>
		<select name="select2" id="select2">
			<option value="11">11</option>
			<option value="12">12</option>
		</select>
	</body>
	</html>
```
