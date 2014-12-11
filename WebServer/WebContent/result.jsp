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
<link rel="stylesheet" href="./css/result.css" type="text/css">
  </head>
  
<body>
<table bgcolor="#FFFFFF">
<tr><td>
<div>
<font style=" font-weight:bold" face="verdana" color="#1F1F1F" size="4">菜鸟</font><a href="./index.jsp"><img  height="50" width="60" src="./img/logo1.jpg"  align="bottom" border="0"></a><font style=" font-weight:bold" face="verdana" color="#1F1F1F" size="4">搜索</font>&nbsp;&nbsp;&nbsp;&nbsp;<input type="text" style="width:400px;height:38px" id="content" name="content" size=30 ><input type="button" style="width:100px;height:38px;color:white;font-size:16px;font-family:SimHei;border:none;background:#1F1F1F;cursor:pointer; " value="菜鸟搜索" onclick="window.location='result.jsp'" >
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
<div class="result c-container" >
<a href="detail.jsp" >对平庸的恐惧</a>
<br/>
<p id="selected">科比曾经写过一句我几年以后才逐渐懂得的话，他说：很多杰出乃至伟大的运动员之所以取得如此高的成就并不是因为他们极度渴望成功，而是因为他们极度畏惧失败。当我读到这句话时，我只是似懂非懂，然而随着时间的流逝我才意识到，对于一个有所畏惧的人来说，做成一件事当然是心满意足的，但那可能只是一种理所当然的感觉，相比面对失败时内心的痛苦和对这种痛苦的恐惧，成功的感觉只是一种微不足道的安慰。</p>
</div>
<div class="result c-container">
<a href="detail.jsp">在湾湾淘旧书</a>
<br/>
<p id="selected">事实上，说到在湾湾买书，几天逛下来，我真的推荐大家第一选择不是诚品，而是湾湾的那些旧书店。众所周知，湾湾书籍的纸张印制都好于大陆，而书价也远比大陆高，选择旧书，一是能以半价或更低的价格入手，这样价格就不会比大陆的新书高太多；二是因为往往湾湾的旧书品相都很好，甚至与新书无疑，一圈逛下啦，手都不会太脏，这是在大陆的旧书店完全做不到的，除非你去贵到死的中国书店，否则在一般的旧书店摸一圈，爪儿基本和挖煤的也差不多了；三是湾湾旧书店里有不少新书榜上的书，再算上进口图书湾湾的上架时间往往早于大陆，所以很多书在湾湾已被卖到旧书店，而大陆还未出版，仍可尝鲜；而第四，就是台湾的旧书店真的够多。</p>
</div>
<div class="result c-container" >
<a href="detail.jsp">其他的都可有可无</a>
<br/>
<p id="selected">最近一次回国，我把国内家里放着的那一大堆漫画都带了过来。这么多年下来，这些漫画书的纸张已经微微发黄，翻开其中几本竟还发现有干脆面或者薯片的碎屑掉出，猛然想起自己学生时代暑假里一边吹空调，一边趴在床上看漫画的日子。而这些久远的单纯心情，却成为了我现在最宝贵的指引着我在这个纷杂的世界里，尽可能愉快地活下去的灯塔。</p>
</div>
<div class="result c-container">
<a href="detail.jsp" >一个人的生死场</a>
<br/>
<p id="selected">逆来顺受，你说我的生命可惜，我自己却不在乎。你看着很危险，我却自以为得意。不得意又怎样？人生本来就是苦多乐少。从耶路撒冷回来之后，我拉着朋友第一时间看了《黄金时代》，途中看到影院内睡倒一片，散场时听到一些抱怨声。朋友问我好看么。我说答不上来，没办法说。但可以肯定的是，电影不适合所有的人，比如你。</p>
</div>
<div class="result c-container">
<a href="detail.jsp">他品尝到的火苗都是冰冷的</a>
<br/>
<p id="selected">眼前的纸张微微发黄 我用钢笔在上面凿下深浅不一的黑 里面盛满打工的词汇 车间，流水线，机台，上岗证，加班，薪水…… 我被它们治得服服贴贴 我不会呐喊，不会反抗 不会控诉，不会埋怨 只默默地承受着疲惫 驻足时光之初 我只盼望每月十号那张灰色的薪资单 赐我以迟到的安慰 为此我必须磨去棱角，磨去语言 拒绝旷工，拒绝病假，拒绝事假 拒绝迟到，拒绝早退 流水线旁我站立如铁，双手如飞 多少白天，多少黑夜 我就那样，站着入睡</p>
</div>
</div>
</div>
</td></tr>

  </body>
</html>
