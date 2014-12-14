package com.cainiao.recommend;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Iterator;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.Set;

public class QueryRecommend {
	
	private static String logfile = "/usr/lib/jni/data/querylog.txt";
	private static Queue<QueryWord> wordQueue = new PriorityQueue<QueryWord>();
	static boolean isInited = false;
	
	
	private static void getWordsFromLog(String qString) throws IOException
	{
		if(isInited) return;
		isInited = true;
		String encoding="UTF-8";
        File file=new File(logfile);
        if (file.isFile() && file.exists())
        { 
            InputStreamReader read = new InputStreamReader(
            new FileInputStream(file),encoding);//���ǵ������ʽ
            BufferedReader bufferedReader = new BufferedReader(read);
            String lineTxt = null;
            while ((lineTxt = bufferedReader.readLine()) != null)
            {
                String[] contents = lineTxt.split("\t");
                String time = contents[0];
                String countStr = contents[3];
                int count = Integer.parseInt(countStr);
                
                String[] keywords = contents[2].split(" ");
                Set<String> set=new HashSet<String>();
                for (int i = 0; i < keywords.length; i++)
                	set.add(keywords[i]);
                String wordStr = "";
                Iterator<String> it=set.iterator();
        		while (it.hasNext())
        		{
        			String string  = (String)it.next();
        			wordStr += string;
        			wordStr += " ";
        		}
                
                QueryWord word = new QueryWord(count, time, wordStr);
                word.setDistance(EditDistance.getDistance(word.getStr(), qString));
                wordQueue.add(word);
            }
            read.close();
        }
	}
	
	private static String getQueryString(ArrayList<String> querys)
	{
		String retString = "";
		Set<String> set=new HashSet<String>();
		for (int i = 0; i < querys.size(); i++)
		{
			set.add(querys.get(i));
		}		
		Iterator<String> it=set.iterator();
		while (it.hasNext())
		{
			String string  = (String)it.next();
			retString += string;
			retString += " ";
		}		
		return retString;
	}
	
	public static ArrayList<String> getRecommendations(ArrayList<String> querys, int K)
	{
		ArrayList<String> recommendsArrayList = new ArrayList<String>();
		try {
			String qString = getQueryString(querys);
			getWordsFromLog(qString);
			int count = 0;
			while (count < K)
			{
				QueryWord word = wordQueue.poll();
				recommendsArrayList.add(word.getStr());
				count++;
			}
			
			
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return recommendsArrayList;
		
	}
	
	public static void main(String[] args)
	{
		ArrayList<String> arrayList = new ArrayList<String>();
		arrayList.add("�Ʊ�");
		arrayList.add("nba");
		arrayList.add("����");
		
		ArrayList<String> ret = getRecommendations(arrayList, 5);
		for (String s: ret)
		{
			System.out.println(s);
		}
		
	}

}
