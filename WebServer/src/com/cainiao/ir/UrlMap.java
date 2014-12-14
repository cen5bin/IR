package com.cainiao.ir;

public class UrlMap {
	public static String locate(String url){
		if( url.startsWith("http://voice.hupu.com") ){
			int idx = url.lastIndexOf("/");
			String htmlid = url.substring(url.lastIndexOf("/")+1);
			String col = url.substring(url.lastIndexOf("/", idx -1 ) + 1,idx);
			return "hupu_pages/"+ col + "_" + htmlid;
		}else{
			int idx = url.indexOf("http://");
			return url.substring(idx+7,url.length());
		}
	}
}
