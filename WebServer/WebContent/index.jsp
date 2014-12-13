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
<link rel="stylesheet" href="./css/result.css" type="text/css">
<link rel="stylesheet" href="http://cdn.bootcss.com/bootstrap/3.3.0/css/bootstrap.min.css">
<script src="http://cdn.bootcss.com/jquery/1.11.1/jquery.min.js"></script>
<script src="http://cdn.bootcss.com/bootstrap/3.3.0/js/bootstrap.min.js"></script>
  </head>
  
<body>
<form name="myform" method="get" action="Query">
<input type="hidden" name="page" value="1">
<!-- <input type="hidden" name="flag" value="0"> -->
<div id="main_container">
<div id="logo-container">
<div class="main-head"> <img height="200" width="200" src="./img/logo.jpg"></div>
<div id="title0" class="main-head">菜鸟搜索</div>
</div>
<div class="col-lg-8 query-form">
    <div class="input-group">
      <input type="text" class="form-control query-input" name="content">
      <span class="input-group-btn">
        <button class="btn btn-default searchbtn btn-primary" type="submit">Go!</button>
      </span>
    </div><!-- /input-group -->
  </div><!-- /.col-lg-6 -->
</div>
</form>


</body>
</html>
