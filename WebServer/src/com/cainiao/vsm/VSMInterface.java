package com.cainiao.vsm;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map.Entry;

public class VSMInterface {
	
	private static ArrayList<VSMDoc> docs = null;
	
	private static void printHelper(HashMap<Integer, HashMap<Integer, Double>> vectors, 
			ArrayList<Integer> queryTermList, int K)
	{
		System.out.println("======inputTest======");
		System.out.println("K is " + K);
		System.out.println("queryTerm are ");
		for (int i = 0; i < queryTermList.size(); i++)
			System.out.println(queryTermList.get(i));
		Iterator<Entry<Integer, HashMap<Integer, Double>>> iterator = vectors.entrySet().iterator();
		while (iterator.hasNext())
		{
			Entry entry = iterator.next();
			Integer docID = (Integer)entry.getKey();
			System.out.println("docID: " + docID);			
		}
		System.out.println("======inputTestEnd======");
	}
	
	public static ArrayList<Integer> getTopK(HashMap<Integer, HashMap<Integer, Double>> vectors, 
											ArrayList<Integer> queryTermList, 
											HashMap<Integer, Integer> refMap, 
											HashMap<Integer, Integer> titleMap,
											HashMap<Integer, Integer> hotMap,
											int K)
	{
//		printHelper(vectors, queryTermList, K);
		VSMEngine vEngine = new VSMEngine(vectors, queryTermList, refMap, titleMap, hotMap);
		docs = vEngine.getTopKDocuments(K);
		ArrayList<Integer> docIDs = new ArrayList<Integer>();
		for (int i = 0; i < docs.size(); i++)
		{
			docIDs.add(docs.get(i).getDocId());
		}
		return docIDs;
	}
	
	public static HashMap<Integer, Integer> getCluster(int K)
	{
		if (docs == null)
			return null;
		else 
		{
			return KMeans.runKmeans(docs, K);
		}
	}

}
