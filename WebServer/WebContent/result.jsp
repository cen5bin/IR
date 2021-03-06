<%@page import="com.cainiao.ir.UrlMap"%>
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
      <input type="text" class="form-control query-input" name="content" id="content" oninput="getlist()"  value="<%
      String content = request.getParameter("content"); 
      content = new String(content.getBytes("ISO8859-1"),"UTF-8");
      out.print(content);
      %>">
      <span class="input-group-btn">
        <button class="btn btn-default searchbtn btn-primary" type="submit">Go!</button>
      </span>
    </div><!-- /input-group -->
    <div id="search-list1">  asd</div>
    
  </div><!-- /.col-lg-6 -->
  </div>

	</form>
	<br><br><br>
</div>
<div id="container" class="container_l">
<div id="content_right" class="cr-offset">
<font style=" font-weight:bold" face="verdana" size="3">友情链接</font>
<br/>
<a style="line-height: 30px;" href="www.google.com" >谷歌</a><br/>
<a style="line-height: 30px;" href="www.baidu.com" >百度</a><br/>
<a style="line-height: 30px;"href="www.bing.com" >bing</a><br/>
<!-- <a style="line-height: 30px;" href="" >St Augustine’s 精神病院</a> -->
</div>
<div id="content_left">

<% 
HashMap<Integer, Integer> clusterInfo = (HashMap<Integer, Integer>)session.getAttribute("clusterinfo");
HashMap<Integer, ArrayList<Integer>> cluster = (HashMap<Integer, ArrayList<Integer>>)session.getAttribute("cluster");
for (Integer key : cluster.keySet()) {
	StringBuffer sb = new StringBuffer();
	ArrayList<Integer> docids1 = cluster.get(key);
	int cnt0 = 0;
	for (Integer docid : docids1) {
		if (cnt0 > 0) sb.append("#");
		cnt0++;
		sb.append(docid);
	}
%>
	<input type="hidden" value="<%=sb.toString() %>" id="cluster<%=key %>">
<% 
	}
ArrayList<News> ret = (ArrayList<News>)session.getAttribute("results"); 
	for (News item : ret) {
%>
<div class="result c-container" >
	<a href="<%=item.getUrl() %>" class="result-title"> 
	<%=item.getTitle() %>  </a>
	<br/>
	<p id="selected" class="result-abstract">
	<%  
		final int len = 1000;
		String ss = item.content;
		if (ss.length() > len)
			ss = ss.substring(0, len) + "...";
		out.print(ss);
	%>
	</p>
	<p class="result-item-bottom">
<%-- 		<a href="<%=item.getUrl()%>">  --%>
			<%
				String url = item.getUrl();
				if (url.startsWith("http://"))
					url = url.substring(7);
				else if (url.startsWith("https://"))
					url = url.substring(8);
				final int urllen = 40;
				if (url.length() > urllen)
					url = url.substring(0, urllen) + "...";
				out.print(url);
			%>
<!-- 		</a> -->
		<%=item.time %> 
		&nbsp;&nbsp;
		<a class="web-cached" href="<%="/snap/"+UrlMap.locate(item.url) %>">网页快照</a>
	&nbsp;&nbsp;<a class="web-cached" 
	onclick="getrelated('<%=clusterInfo.get(item.getId()) %>')">相关文档</a>
	</p>
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
<!-- <input id="srhBtn" type="button" value="ssss"> -->
<!-- <script> -->

<script type="text/javascript">
var tmp = 0;
var getlist = function(){

	var dd  = document.getElementById("content");
	
	
	htmlobj=$.ajax(
			{ 
			  type:"POST",
			  url: "./AutoCompletion",
			  asyn:true,
			  context: document.body,
			  data:"content=" + dd.value,
			  success: function(data){
				 // alert(data);
				//alert($("#content").attr("value"));
				 if (data == "") $("#search-list1").css("display", "none");
				 else {
				  $("#search-list1").css("display", "block");
				  $("#search-list1").html("");// = "";
				  $("#search-list1").html(data);
// 				  $("#search-list").append($(data));
// 				  $("#search-list").innerHTML = data;
				 }
		      	}
			});
	
	
}

var insert = function(s) {
	
	$("#content").val(s); 
	$("#search-list").css("display", "none");
};
var getrelated = function(cluster) {
	var param = "param="+$("#cluster"+cluster).attr("value")+"&page=1&content="+$("content").attr("value");
	
	var form=$("<form method='post' > </form>")
	form.attr({"action":"./RelatedDocs"});
	var input=$("<input type='hidden'>");
	input.attr({"name":"param"});
	input.val($("#cluster"+cluster).attr("value"));
	form.append(input);
	
	input=$("<input type='hidden'>");
	input.attr({"name":"content"});
	input.val($("#content").attr("value"));
	form.append(input);
	
	input=$("<input type='hidden'>");
	input.attr({"name":"page"});
	input.val(1);
	form.append(input);
	
	form.submit();
	
			
}
$(document).ready( function(){
	//alert("hello")
	var arr=[1,2,3,4,5,6];
	var strarr =JSON.stringify(arr);
	//alert("param="+strarr);
	param = "param="+strarr;
	
	
	
	$("#srhBtn").click( function(){
		alert("hell0");
		htmlobj=$.ajax(
		{ 
		  type:"POST",
		  url: "./Test1",
		  asyn:false,
		  context: document.body,
		  data:param,
		  success: function(data){
	      	}
		});
		
	});
}); 	
</script>
  </body>
</html>
