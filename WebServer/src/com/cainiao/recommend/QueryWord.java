package com.cainiao.recommend;

public class QueryWord implements Comparable{
	
	private int count;
	private String time;
	private int distance = 0;
	private String str;
	
	public QueryWord(int count, String time, String str)
	{
		this.count = count;
		this.time = time;
		this.str = str;
	}
	
	public void setDistance(int d)
	{
		this.distance = d;
	}
	
	public int getDistance()
	{
		return distance;
	}
	
	public String getStr()
	{
		return str;
	}

	public int compareTo(Object o) {
		// TODO Auto-generated method stub
		QueryWord word = (QueryWord)o;
		if (distance == word.distance)
		{
			if (time.compareTo(word.time) > 0)
				return -1;
			else if (time.compareTo(word.time) == 0)
			{
				if (count > word.count)
					return -1;
				else if (count == word.count)
					return 0;
				else 
					return 1; 
			}
			else
				return 1;
		}
		else 
		{
			if (distance < word.distance)
				return -1;
			else
				return 1;
		}
		
	}
	
	

}
