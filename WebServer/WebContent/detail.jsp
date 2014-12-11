<%@ page language="java" import="java.util.*" pageEncoding="utf-8"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>My JSP 'detail.jsp' starting page</title>
    
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
<font style=" font-weight:bold" face="verdana" size="3">相关文档</font>
<br/>
<a style="line-height: 30px;" href="" >湾湾行---捷运台大医院周边</a><br/>
<a style="line-height: 30px;" href="" >猴子整理台北的二手书店</a><br/>
<a style="line-height: 30px;"href="" >这年头，寄本书也要斗中国邮政</a><br/>
<a style="line-height: 30px;" href="" >你想说的所有道理全都不可说</a>
</div>
<div id="content_left">
<div class="result c-container" >
<p><font style=" font-weight:bold" face="verdana" color="green" size="5">对平庸的恐惧</font></p>

<p ><font  face="verdana" color="blue" size="3">小海的主页   日记     广播    相册      喜欢   </font></p>

<p id="selected">科比曾经写过一句我几年以后才逐渐懂得的话，他说：很多杰出乃至伟大的运动员之所以取得如此高的成就并不是因为他们极度渴望成功，而是因为他们极度畏惧失败。<br/><br/>

       当我读到这句话时，我只是似懂非懂，然而随着时间的流逝我才意识到，对于一个有所畏惧的人来说，做成一件事当然是心满意足的，但那可能只是一种理所当然的感觉，相比面对失败时内心的痛苦和对这种痛苦的恐惧，成功的感觉只是一种微不足道的安慰。<br/><br/>

       当我真正明白这句话时，我就理解了一种天赋。这种天赋人人都有，它就埋藏在那个人一定想要做成而不愿意失败的事情上。人人都有这样的一件事情，人人都对许多的事情毫不在意，但在特定的事情上，他极度渴望成功，以慰籍自己因惧怕失败而造成的伤痛。当我明白这一点以后，我就知道这种天赋是最大的一种馈赠，正确的面对它和利用它，可以激起一个人无尽的潜力。<br/><br/>

       从小我就隐隐的感觉到，我不喜欢和别人一样，即使是在一些微不足道的事情上。我不想和人一样并不是因为我是受到什么思想的影响或认为这样做有什么特别和好处，而是仅仅是一种本能。我很小就意识到，而且随着长大后阅历逐渐丰富更加清晰的认识到，大多数人喜欢和别人一样是因为人们在追求利益自保，追求减少选择和提高做事效率。追随大众是人类的本能，也是一种非常稳妥的方法，但代价在于，这样很无聊。<br/><br/>

       从小，我就无法忍受这种无聊，为了规避这种无聊，我宁愿绕很大的弯走远路。<br/><br/>

       走远路总是要付出很大代价的，最大的代价莫过于面对人类作为社会性动物最难面对的事情：舆论压力。身边的人总是在说，小海，你为何总是和别人不一样呢？小海，为何你就不能学学别人呢？甚至长大以后，相隔千里万里的人也都觉得他们拥有足够的资格来教导我。我必须承认，即使面对和经历过许许多多这样的场景，每当它再度发生，我仍然要承受多多少少的痛苦，但我也知道，我所面对的压力与痛苦只是我人生必须要经历的一部分，它与我要不要做自己和是不是正在追求做自己这些事都没有关系。<br/><br/>

       我深深的明白，任何社会的格局之所以是一个金字塔形而不是倒三角形，根本原因是因为大多数人总是在关键问题上做出了错误的决定，或至少做的不够好。而为了做一个不一样的人，任何一个人都需要付出超乎寻常的努力，面对超乎寻常的压力，忍受更高的失败率和因此滚滚而来的更多的嘲笑。然而仔细想想，对任何需要做自己而且笃信这一点的人而言，这些事实际上又算得上什么呢？仔细想想当自己必须要面对自己一事无成时的那份绝望和恐惧吧，我们今天所面对的一切又算得上什么？<br/><br/>

       人人心中都藏着一个或多个梦想，有的人想做成的是和我一样，只是一个类似于“不甘平庸”的模糊概念，有的人的目标更加具体，是他想做成什么事，或成为什么样的人。现实是，只有少部分人在一生中实现了自己的所愿，而更是只有极少一部分完成了自己希望中堪称伟大的那一部分。当人们习惯性一事无成时他们是如何做的呢，他们总是习惯于自我欺骗和自我安慰，总是夸大自己的目标并称那是不可实现的，总是高估面对的困难并称那是无可跨越的，总是关注于自己所丧失的并称那是不可挽回的，总是着重看着自己所有条件的并称那是不值一提的。人们怎么能学不会自我欺骗呢？如果人类不懂得这一点的技巧，绝大多数的人类将会在自己人生的整个后半段甚至更久的时间陷入无可救药的绝望中。于是人们发明了对自己使用的安慰剂，可我并不知道这是一种幸运，还是一种不幸。很多人在自己明明还能走上很远道路的时候，就已经对自己提前使用了安慰剂，使用了对梦想的阉割药水。<br/><br/>

       人应该活在自我安慰的怡然自得而不是活在对无法达成的恐惧中吗？我不这样认为。所有人的一生都在追求平静，追求一切主客观世界停顿下来，没有什么疑惑和挑战的静止状态。那种状态的确很迷人，它满足了人类最无法克服的懒惰情绪。然而随着一点点长大我一点点发现，静止的美好的状态只不过是一种幻觉，没有任何疑惑和挑战的情况是不可能发生的。如果感觉身在其中，那么人们只不过是在自我欺骗。人永远都在前进，永远都在思索，永远都在追逐成功和畏惧失败，逃避这种情绪是没有意义的。<br/><br/>

       从此我明白，与其退缩和蒙蔽自我的双眼，不如去彻彻底底的拥抱畏惧，拥抱自己对心中渴望不能达成的畏惧，只有这种夹杂着痛苦与使命感的生活才是真实的，而只有真实的生活才是厚重的，只有厚重的生活才能使生活本身充满意义，并助推任何人向使命的目标前行。<br/><br/>

       遵循自己的天赋，遵循自己的潜力，遵循自己的畏惧，这是我后来终于懂得的。即使当我的同辈，当比我更年长或更年轻的人中已经越来越多人低下了头颅，开始寻求妥协，我也应该在其中艰难前行，并再一次遵循自己对陷入平庸的畏惧。<br/><br/>

       心高气傲的都会被现实暴打，但还是要心高气傲。走陌生道路的都会摔的很惨，但还是要走陌生的道路。在激流中前行的都会心神俱疲，但还是要在激流中前行。在绝望中抗争的都会感到孤独的痛苦，但还是要在绝望中抗争。与众不同的都会被人耻笑，但还是要与众不同。像个少年一样左冲右突的都会被人认作幼稚，但还是要像个少年一样左冲右突。因为任何一个人都有他与恐惧相连的命运，一种在希腊神话中连神的旨意都无法改变的命运。一切对命运本身的抗拒，都只是在掩盖自己内心中永远不甘的躁动，并给自己余下的一生留下越来越多无可挽回的遗憾。</p>
</div>

</div>
</div>
</td></tr>
</table>
  </body>
</html>
