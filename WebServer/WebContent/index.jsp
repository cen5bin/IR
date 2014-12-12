<%@ page language="java" import="java.util.*" pageEncoding="utf-8"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>My JSP 'index.jsp' starting page</title>
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="This is my page">
	<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	-->

  </head>
  
<body>
<form name="myform" method="get" action="Query">
<table bgcolor="#FFFFFF">
<tr><td>

<div  id="ico" style="position:absolute;left:520px;top:100px;height:200px; border:2px">
<a href=""><img  height="200" width="250" src="./img/logo1.jpg"  align="bottom" border="0"></a>
</div>

<div id="circle" style="position:absolute;left:420px;top:320px;height:200px; border:0px">
<input type="text" style="width:450px;height:38px" id="content" name="content" size=30><input type="submit" style="width:100px;height:37px;color:white;font-size:16px;font-family:SimHei;border:none;background:#1F1F1F;cursor:pointer; " value="菜鸟搜索"  onclick="window.location='result.jsp'" >
</div>

</td></tr>
</table>
</form>
</body>
</html>
