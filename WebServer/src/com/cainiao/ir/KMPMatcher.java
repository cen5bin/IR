package com.cainiao.ir;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.List;
import java.util.Set;


public class KMPMatcher {
	private static class Pair implements Comparable<Pair>{
		int a;
		int b;
		public Pair(int l,int r){
			a = l;
			b = r;
		}
		@Override
		public int compareTo(Pair o) {
			
			if( o.a ==  a )
				return b - o.b;
			else return a - o.a;
		}
		
	}
	private static final int MAXLEN = 1000;
	private static int maxSize = 300;//允许构建的串的最大长度
	private static int maxMatch = 3;
	private static int[] next = new int[MAXLEN];
	
	public static void setMaxSize(int m){
		maxSize = m;
	}
	private static void getNext(char[] ptn){
		int k,j;
		j = 0;
		k = next[0] = -1;
		int len = ptn.length;
		while( j < len ){
			
			if( k == -1 || ptn[k] == ptn[j] ){
				k ++; j ++;
				next[j] = k;
			}else{
				k = next[k];
			}
		}
	}
	
	private static List<Integer> kmp(char [] ptn, char []mth){
		int len2 = mth.length;
		int len1 = ptn.length;
		int i,j;
		i = j = 0;
		getNext(ptn);
		List<Integer> list = new ArrayList<Integer>();
		while( i < len2 ){
			
			while( i < len2 && j < len1 ){
				if( j == -1 || ptn[j] == mth[i] ){
					i ++; j ++;
				}else{
					j = next[j];
				}
			}
			
			if( j >= len1 ){
				list.add(i-len1);
				j = next[j];
			}
		}
		return list;
	}
	
	public static String match(String cnt,List<String> keywords){
		List<Pair> list = new ArrayList<Pair>();
		char []mth = cnt.toCharArray();
		//获取所以可能的匹配串的区间
		for(String key: keywords){
			char []ptn = key.toCharArray();
			List<Integer> res = kmp(ptn,mth);
			int len = ptn.length;
			for( Integer i: res){
				Pair p = new Pair(i,i+len-1);
				list.add(p);
			}
		}
		Object[] order_region = list.toArray();
		Arrays.sort(order_region);//先按照匹配区间的左边界排序，再按照右边界排序
		int i,j;
		i = 0;
		j = -1;
		list.clear();
		//根据左边界递增的匹配区间列表，去除 处理互相嵌套重合 的区间，使得最后得到的每个区间都是分离的，并且覆盖原来的各个区间。
		for(Object o: order_region){
			Pair p = (Pair)o;
			if( j < p.a ){
				list.add(new Pair(j - i + 1,i));//加入一个处理好的区间
				//System.out.println(j - i + 1+" "+i);
				i = p.a;
				j = p.b;
			}else if( p.b > j ){
				j = p.b;
			}
			
		}
		list.add(new Pair( j - i + 1 , i));
		//System.out.println(list.size());
		list.remove(0);//第0个元素没有实际意义
		//System.out.println(list.size());
		order_region = list.toArray();
		//System.out.println(order_region.length);
		Arrays.sort(order_region);
		int k = 0; 
//		for( Object o: order_region){
//			System.out.println(">>>"+((Pair)o).b);
//		}
		list.clear();
		for( Object o: order_region){
			k ++;
			if( k > maxMatch ) break;
			Pair p = (Pair)o;
			list.add(new Pair( p.b, p.a + p.b - 1));
		//	System.out.println(">>" +  p.b+" "+( p.a + p.b - 1));
		}
		order_region = list.toArray();
		Arrays.sort(order_region);//按照左边界排序(left,right)
		
		i = 0;
		j = -1;
		//list.clear();
		List<Pair> gap = new ArrayList<Pair>();//每两个匹配子串的中间的间隔，加上首位两端
		int size = 0;
		int idx = 0;
		
		for(Object o: order_region){
			Pair p = (Pair)o;
			size += j - i + 1;//匹配子串的总长度
			//System.out.println(size);
			//System.out.println("**"+p.a +" " + p.b);
			//System.out.println("***"+(p.a - j - 1) +" " + idx);
			gap.add(new Pair(p.a-j-1,idx++));//加入一个区间间隔，(len,idx) = (区间长度，区间顺次)
			i = p.a;
			j = p.b;
			
		}
		size += j - i;
		gap.add(new Pair(mth.length-j-1,idx));
		//list.add(new Pair( i,j));
	//	list.remove(0);//第0个元素没有实际意义
		
		
		
		Object []order_gap = gap.toArray();//按照间隔长度排序
		Arrays.sort(order_gap);
		int num = order_gap.length;
		int div = ( maxSize - size )/num;//每个间隔平均能够得到的最长长度
		gap.clear();
		size = maxSize - size;//剩余空间长度
		for( Object o: order_gap){
			Pair p = (Pair)o;
			if( p.a <= div ){
				gap.add( new Pair(p.b,p.a) );//加入分配好的区间长度，(idx,len) = (顺次，分配的间隔长度)
				size -= p.a;
				num --;
				if( num != 0)
					div = size /num;//更新每个间隔平均能够得到的最长长度
			}else{
				gap.add( new Pair(p.b,div) );//加入分配好的区间长度，(idx,len) = (顺次，分配的间隔长度)
				size -= div;
				num --;
				if( num != 0)
					div = size /num;//更新每个间隔平均能够得到的最长长度
			}
		//	System.out.println(num);
		//	System.out.println(p.a +" " + p.b);
		}
		
		Object[] gapArray = gap.toArray();
		Arrays.sort(gapArray);//按照顺次排序
		
		//System.out.println(construct(mth,list,gapArray));
		return construct(mth,list,gapArray);
	}
	
	private static String construct(char[] cnt,List<Pair> list,Object[] gapArray){
		String lspan ="<span class='red'>";
		String rspan ="</span>";
		StringBuffer sb = new StringBuffer("");
		int i = 0;
		int j = 0;
		for( j = 0; j != list.size(); j ++ ){
			Pair p = list.get(j);
			Pair gap = (Pair)gapArray[j];
			if( p.a - i > gap.b ){
				int l = gap.b - 3;
				if( l < 0 ) l = 0;
				sb.append(cnt,i,l);
				sb.append("...");
			}else{
				sb.append(cnt,i,p.a-i);
			}
			sb.append(lspan);
			sb.append(cnt,p.a,p.b-p.a+1);
			sb.append(rspan);
			i = p.b+1;
		}
		Pair gap = (Pair)gapArray[j];
		if( cnt.length - i > gap.b ){
			int l = gap.b - 3;
			if( l < 0 ) l = 0;
			sb.append(cnt,i,l);
			sb.append("...");
		}else{
			sb.append(cnt,i,cnt.length-i);
		}
		return sb.toString();
	}
	public static void main(String args[]){
		String str = "中新社厦门3月10日电 (记者 陈悦)中国乒乓球男队10日在厦门福隆中国乒乓球训练基地挂起备战横幅。在中国乒乓球队总教练刘国梁看来，此次备战不仅仅是为了4月28日将开幕的东京世锦赛团体赛，亦是为了里约奥运周期，“将男队阵容打造完成”。　　组建冲击里约奥运阵容　　此次男乒厦门封闭集训将从3月10日持续到4月17日。刘国梁说，这次来到厦门备战，是为了“专心、安静”静下心来备战，把“基础打得扎实”。　　他坦言，2012年伦敦奥运结束后，男乒队员“流动性大，状态反复”，因而此次封闭集训就是为了帮助队员们找到感觉和气氛。　　对于团体实力强大、已经男团六连冠的中国男队而言，东京世锦赛卫冕固然是本次集训的一大目标，而两年后的里约奥运会备战也已起跑。　　刘国梁说，希望利用这次集训，从奥运周期出发，“发掘出有力竞争者”，重新组建有利冲击里约奥运会的阵容。　　德日韩是卫冕主要对手　　王皓、张继科、马龙、许昕、樊振东，这是中国男乒此次出征东京的阵容，是一个老中青“三代同堂”的阵容。　　“王皓是老一代代表，起到稳定军心的作用”，刘国梁说，作为中坚力量，张继科和马龙要“接过马琳、王皓的班，成为真正的领军人物”。　只有17岁的樊振东则是这个阵容中最小的球员。他在2013年快速崛起，曾一举夺下中国全运会男单亚军。刘国梁期待樊振东“成为里约奥运会的一匹‘黑马’”。　　在刘国梁眼中，这个三代球员联袂出击的阵容要想实现男团卫冕，德国、日本、韩国是最有威胁的对手。他专门点评了东道主日本队，认为其是主场作战，队员比较年轻，具备了冲击奖牌的实力，“不能掉以轻心”。　　新老交替，王皓难圆大满贯梦　　中国乒乓球人才辈出，马琳、王励勤以及王皓这些曾写下辉煌的老将，如今或已退役，或已“退居二线”。　　对还在拼搏的王皓而言，三度在奥运男单决赛中屈居亚军，让不少球迷唏嘘不已。但刘国梁坦言，虽然王皓一直保持着不错的竞技状态，但三度获得亚军，对于乒乓球选手心理损耗是非常巨大的，要想在里约圆梦不容易。　　至于已经退役并且分别在上海、广东担纲乒羽(乒乓球)管理中心主任的王励勤和马林。刘国梁则透露，在本次集训期间，两人都将重返训练基地，一方面作为顾问组成员为“师弟”们贡献经验，一方面也学习国家队先进的管理经验，以更好担负管理工作。　　乒乓球推广欲设立训练营　　随着乒乓球中国“一花独放”，如何普及推广乒乓球，保持其在国际体坛的地位，亦成为近年来乒乓球界关注的焦点。　　刘国梁坦言，乒乓球推广是所有乒乓球人要共同来完成的，但中国是乒乓球大国，也是乒乓球强国，“有更多责任把乒乓球项目推广好”。　他透露，乒乓球界有设想组建训练营，让欧美国家运动员、爱好者共同来参与。";
		String ptn = "刘国梁";
		List<String> set = new ArrayList<String>();
		set.add(ptn);
		setMaxSize(80);
		System.out.println( match(str,set) );
//		int len = ptn.length();
//		List<Integer> list = KMP(ptn.toCharArray(),str.toCharArray());
//		
//		for( Integer o:list){
//			//System.out.println(o +" " + o+len);
//			System.out.println(str.substring(o,o+len));
//		}
	}
}
