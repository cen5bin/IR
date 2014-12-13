package com.cainiao.entity;

public class ResultItem {
	private String title;
	private String abs;
	private String date;
	private String url;
	public ResultItem(String title, String abs, String date, String url) {
		super();
		this.title = title;
		this.abs = abs;
		this.date = date;
		this.url = url;
	}
	public String getUrl() {
		return url;
	}
	public void setUrl(String url) {
		this.url = url;
	}
	public String getTitle() {
		return title;
	}
	public void setTitle(String title) {
		this.title = title;
	}
	public String getAbs() {
		return abs;
	}
	public void setAbs(String abs) {
		this.abs = abs;
	}
	public String getDate() {
		return date;
	}
	public void setDate(String date) {
		this.date = date;
	}
	public ResultItem(String title, String abs, String date) {
		super();
		this.title = title;
		this.abs = abs;
		this.date = date;
	}
	
}
