package com.cainiao.vsm;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map.Entry;


public class KMeans {
	
	private static HashMap<Integer, Integer> cluserMap = new HashMap<Integer, Integer>();
	private static HashMap<Integer, HashMap<Integer, Double>> clusterCenters = 
									new HashMap<Integer, HashMap<Integer, Double>>();
	
	private static double calculateDistance(HashMap<Integer, Double> vector1, 
									HashMap<Integer, Double> vector2)
	{
		double distance = 0.0;
		Iterator<Entry<Integer, Double>> iterator = vector1.entrySet().iterator();
		while (iterator.hasNext())
		{
			Entry entry1 = iterator.next();
			Integer termID = (Integer)entry1.getKey();
			if (vector2.containsKey(termID))
			{
				double difference = Math.abs(vector1.get(termID) - vector2.get(termID));
				distance += difference * difference;
			}
		}
		return distance;
	}
	
	private static void initSeeds(ArrayList<VSMDoc> docList, int K)					
	{
		int totalNum = docList.size();
		int pos = 0;
		int offset = totalNum / K;
		for (int i = 0; i < K; i++)
		{
			VSMDoc doc = docList.get(pos);
			pos += offset;
			clusterCenters.put(i, doc.getDocVector()); //keyÊÇŽØ±êºÅ£¬valueÊÇÏòÁ¿
		}
	}
	
	private static void partitionToCluster(ArrayList<VSMDoc> docList)								
	{
		for (int i = 0; i < docList.size(); i++)
		{
			HashMap<Integer, Double> vector = docList.get(i).getDocVector();
			Iterator<Entry<Integer, HashMap<Integer, Double>>> iterator = 
											clusterCenters.entrySet().iterator();
			int clusterToBelong = 0;
			double  mindDis = -1.0;
			while (iterator.hasNext())
			{
				Entry center = iterator.next();
				HashMap<Integer, Double> cvector = (HashMap<Integer, Double>)center.getValue();
				double dist = calculateDistance(cvector, vector);
				if (mindDis == -1.0 || dist < mindDis)
				{
					mindDis = dist;
					clusterToBelong = (Integer)center.getKey();
				}	
			}
			cluserMap.put(docList.get(i).getDocId(), clusterToBelong); //ÎªÎÄµµÏòÁ¿·ÖÅäµœ×îœüµÄŽØ
		}
	}
	
	private static void reCalculateCenter(ArrayList<VSMDoc> docList, int K)
	{
		HashMap<Integer, ArrayList<HashMap<Integer, Double>>> clusters = 
				new HashMap<Integer, ArrayList<HashMap<Integer, Double>>>();
		for (int i = 0; i < K; i++)
		{
			ArrayList<HashMap<Integer, Double>> vectors = new ArrayList<HashMap<Integer, Double>>();
			clusters.put(i, vectors); 
		}
		for (int i = 0; i < docList.size(); i++)
		{
			int clusterLabel = cluserMap.get(docList.get(i).getDocId());
			clusters.get(clusterLabel).add(docList.get(i).getDocVector()); 
		}
		
		for (int k = 0; k < K; k++) //ÎªÃ¿Ò»žöŽØŒÆËãÐÂµÄÖÐÐÄÏòÁ¿
		{
			ArrayList<HashMap<Integer, Double>> vectors = clusters.get(k);
			HashMap<Integer, Double> meanVector = new HashMap<Integer, Double>();
			for (int i = 0; i < vectors.size(); i++)
			{
				HashMap<Integer, Double> vector = vectors.get(i);
				Iterator<Entry<Integer, Double>> iterator = vector.entrySet().iterator();
				while (iterator.hasNext())
				{
					Entry entry = iterator.next();
					Integer termID = (Integer)entry.getKey();
					if (meanVector.containsKey(termID))
					{
						double val = meanVector.get(termID);
						val += (Double)entry.getValue();
						meanVector.put(termID, val);
					}
					else 
					{
						meanVector.put(termID, (Double)entry.getValue());
					}
				}				
			}
			Iterator<Entry<Integer, Double>> iterator = meanVector.entrySet().iterator();
			while (iterator.hasNext())
			{
				Entry entry = iterator.next();
				int termID = (Integer)entry.getKey();
				Double newVal = (Double)entry.getValue() / clusters.get(k).size();
				meanVector.put(termID, newVal);
			}
			clusterCenters.put(k, meanVector);
		}
	}
	
	public static boolean isKmeansEnd(HashMap<Integer, Integer> backup)
	{
		Iterator<Entry<Integer, Integer>> iterator = backup.entrySet().iterator();
		while (iterator.hasNext())
		{
			Entry entry = iterator.next();
			int docID = (Integer)entry.getKey();
			int backupCluster = (Integer)entry.getValue();
			int cluster = cluserMap.get(docID);
			if (cluster != backupCluster)
				return false;
		}
		return true;
	}
	
	
	public static void printHelper()
	{
		Iterator<Entry<Integer, Integer>> iterator = cluserMap.entrySet().iterator();
		while (iterator.hasNext())
		{
			Entry entry = iterator.next();
			int docID = (Integer)entry.getKey();
			int clsLabel = (Integer)entry.getValue();
			System.out.println("docID: " + docID + " " + "cluster: " + clsLabel);
		}
	}
	
	public static HashMap<String, String> getJsonMap()
	{
		Iterator<Entry<Integer, Integer>> iterator = cluserMap.entrySet().iterator();
		HashMap<String, String> jsonMap = new HashMap<String, String>();
		while (iterator.hasNext())
		{
			Entry entry = iterator.next();
			int docID = (Integer)entry.getKey();
			int clusterID = (Integer)entry.getValue();
			String key = Integer.toString(docID);
			String value = Integer.toString(clusterID);
			jsonMap.put(key, value);
		}
		return jsonMap;
	}
	
	public static HashMap<Integer, Integer> runKmeans(ArrayList<VSMDoc> docList, int K)
	{
		initSeeds(docList, K);
		while (true)
		{
			HashMap<Integer, Integer> backup = cluserMap;
			partitionToCluster(docList);
			reCalculateCenter(docList, K);		
			if (isKmeansEnd(backup))
				break;
		}
		printHelper();
		//JSONObject json = JSONObject.fromObject(getJsonMap());
		return cluserMap;
	}

}