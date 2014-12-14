package com.cainiao.vsm;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map.Entry;


public class VSMUtil {
	
	private static double argRef = 0.5;
	private static double argTitle = 0.1;
	private static double argHot = 0.15;
	private static double argVec = 0.25;
	
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
	
	public static double calculateDocScore(VSMDoc doc)
	{		
		double score = argRef * doc.getRef() + argTitle * doc.getTitleScore() + 
				      argHot * doc.getHot() + argVec * doc.getVectorScore();
		
		return score;
	}

}
