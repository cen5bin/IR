package com.cainiao.dao;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import com.cainiao.entity.News;

public class DataReader {
	public static ArrayList<News> getNews(List<Integer> list) throws SQLException {
		ArrayList<News> ret = new ArrayList<News>();
		StringBuffer sb = new StringBuffer();
		sb.append("(");
		for (int i = 0; i < list.size(); i++) {
			if (i > 0) sb.append(",");
			sb.append(list.get(i));
		}
		sb.append(")");
		String sql = "select * from news where id in "+ sb.toString();
		ResultSet rs = BaseDao.query(sql);
		while (rs.next()) {
			News news = new News();
			news._abstract = rs.getString("abstract");
			news.id = rs.getInt("id");
			news.content = rs.getString("content");
			news.url = rs.getString("url");
			news.time = rs.getString("time");
			news.title = rs.getString("title");
			news.keywords = rs.getString("keywords");
			ret.add(news);
		}
		
		return ret;
	}
	
	public static ArrayList<String> getList(String s) throws SQLException {
		ArrayList<String> ret = new ArrayList<String>();
		String sql = "select hanzi from keywords where hanzi like '"+s+"%%'";
		ResultSet rs = BaseDao.query(sql);
		while (rs.next()) {
			ret.add(rs.getString("hanzi"));
		}
		return ret;
	}
	
	public static ArrayList<String> getList1(String s) throws SQLException {
		ArrayList<String> ret = new ArrayList<String>();
		String sql = "select hanzi from keywords where pinying like '"+s+"%%'";
		ResultSet rs = BaseDao.query(sql);
		while (rs.next()) {
			ret.add(rs.getString("hanzi"));
		}
		return ret;
	}
	
	public static void main(String[] args) throws SQLException {
//		ArrayList<Integer> docids = new ArrayList<Integer>();
//		docids.add(1);
//		docids.add(2);
//		ArrayList<News> ret = getNews(docids);
//		for (News news : ret) 
//			System.out.print(news.id+" "+ news.url+"\n");
		ArrayList<String> ret = getList("刘");
		for (String s : ret) System.out.print(s + " ");
	}
}
