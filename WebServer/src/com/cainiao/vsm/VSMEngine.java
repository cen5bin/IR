package com.cainiao.vsm; 

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.Random;
import java.util.Map.Entry;


public class VSMEngine {
	
	private Queue<VSMDoc> vsmDocQueue = new PriorityQueue<VSMDoc>();
	
	private void initVSMDocList(HashMap<Integer, HashMap<Integer, Double>> vectors, 
			ArrayList<Integer> queryTermList, HashMap<Integer, Integer> refMap)
	{
		Iterator<Entry<Integer, HashMap<Integer, Double>>> iterator = vectors.entrySet().iterator();
		while (iterator.hasNext())
		{
			Entry entry = iterator.next();
			Integer docID = (Integer)entry.getKey();
			HashMap<Integer, Double> vector = (HashMap<Integer, Double>)entry.getValue();
			VSMDoc doc = new VSMDoc(docID, vector, refMap.get(docID));
			
			double score = VSMUtil.fastCosineScore(doc, queryTermList);
			doc.setScore(score);
			vsmDocQueue.add(doc);
		}
		
	}
	
	public VSMEngine(HashMap<Integer, HashMap<Integer, Double>> vectors, 
			ArrayList<Integer> queryTermList, HashMap<Integer, Integer> refMap)
	{
		initVSMDocList(vectors, queryTermList, refMap);
	}
	
	public ArrayList<VSMDoc> getTopKDocuments(int K)
	{
		int count = 0;
		ArrayList<VSMDoc> docs = new ArrayList<VSMDoc>();
		while (count < K)
		{
			VSMDoc doc = vsmDocQueue.poll();
			docs.add(doc);
			System.out.println(doc.getScore());
			count++;
		}
		return docs;
	}
	
}
