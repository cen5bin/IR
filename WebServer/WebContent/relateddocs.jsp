<%@page import="com.cainiao.entity.News"%>
<%@ page language="java" import="java.util.*" pageEncoding="utf-8"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>My JSP 'result.jsp' starting page</title>
    
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="This is my page">
	<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	-->
	<link rel="stylesheet" href="http://cdn.bootcss.com/bootstrap/3.3.0/css/bootstrap.min.css">
<script src="http://cdn.bootcss.com/jquery/1.11.1/jquery.min.js"></script>
<script src="http://cdn.bootcss.com/bootstrap/3.3.0/js/bootstrap.min.js"></script>
 
<link rel="stylesheet" href="./css/result.css" type="text/css">
  </head>
  
<body>
<table bgcolor="#FFFFFF">
<tr><td>
<div>
<form name="myform" method="get" action="Query">
	<div id="query-container">
	<div class="result-head"> <img src="./img/logo.jpg" height="50" width="50"> </div>
	<div class="result-head result-head-label">菜鸟搜索</div>
	<div class="col-lg-6 result-head">
    <div class="input-group">
      <input type="text" class="form-control query-input" name="content" value="<%
      String content =   session.getAttribute("content").toString();//request.getParameter("content"); 
      //content = new String(content.getBytes("ISO8859-1"),"UTF-8");
      out.print(content);
      %>">
      <span class="input-group-btn">
        <button class="btn btn-default searchbtn btn-primary" type="submit">Go!</button>
      </span>
    </div><!-- /input-group -->
  </div><!-- /.col-lg-6 -->
  </div>

	</form>
	<br><br><br>
</div>
<div id="container" class="container_l">
<div id="content_right" class="cr-offset">
<font style=" font-weight:bold" face="verdana" size="3">其他人还搜</font>
<br/>
<a style="line-height: 30px;" href="" >It's just that it's delicate</a><br/>
<a style="line-height: 30px;" href="" >为什么日记要有题目</a><br/>
<a style="line-height: 30px;"href="" >千禧年事件</a><br/>
<a style="line-height: 30px;" href="" >St Augustine’s 精神病院</a>
</div>
<div id="content_left">

<% ArrayList<News> ret = (ArrayList<News>)session.getAttribute("results"); 
	for (News item : ret) {
%>
<div class="result c-container" >
	<a href="<%=item.getUrl() %>" class="result-title"> 
	<%=item.getTitle() %>  </a>
	<br/>
</div>
<%} %>


</div>
</div>
</td></tr>
</table>

<div id="page-navigate">
<nav>
  <ul class="pagination">
  <% String page0 = request.getParameter("page");
  	int pageNum = 1;
  	if (page0 != null) pageNum = Integer.parseInt(page0);
  	int pageCount = Integer.parseInt(session.getAttribute("pagecount").toString());
  	String href = "Query?page="+1+"&content="+content;
  	if (pageNum != 1) {
  %>
    <li><a href="<%=href%>">首页</a></li>
    <% }
  		int start = 1;
  		int end = 0;
    	if (pageNum > 5) start = pageNum - 5;
    	if (start + 9 <= pageCount) end = start + 9;
    	else  {
    		end = pageCount;
    		if (end - 9 >= 1) start = end - 9;
    		else start = 1;
    	}
    	for (int i = start; i <= end; i++) {
    		href = "Query?page="+i+"&content="+content;
    		if (i == pageNum) {
    %>
    <li class="active"><a href="#"><%=i %> <span class="sr-only">(current)</span></a></li>
    <%}
    		else { %>	
    		 <li><a href="<%=href%>"><%=i %></a></li>
    	<% } }%>
    
    <% if (pageNum != pageCount) {
    	href = "Query?page="+pageCount+"&content="+content;
    %>
    
     <li><a href="<%=href%>">尾页</a></li>
     <%} %>
    
  </ul>
</nav>
</div>
  </body>
</html>
