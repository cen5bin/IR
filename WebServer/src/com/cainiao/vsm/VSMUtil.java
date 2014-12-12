package com.cainiao.vsm;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map.Entry;


public class VSMUtil {
	
	public static double calculateIDF(int N, int df)
	{
		double factor = df/N;
		return Math.log(factor)/Math.log(2);
	}
	
	public static double fastCosineScore(VSMDoc doc, ArrayList<Integer> queryTermIDList)
	{
		HashMap<Integer, Double> docVector = doc.getDocVector();
		double sum = 0;
		Iterator<Entry<Integer, Double>> iterator = docVector.entrySet().iterator();
		while (iterator.hasNext())
		{
			Entry entry = iterator.next();
			if (queryTermIDList.contains((Integer)entry.getKey()))
			{				
				Double score = (Double)entry.getValue();
				sum += score;
			}
		}
		return sum / doc.getDocLength();
	}
	

}
