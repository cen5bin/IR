package com.cainiao.vsm;

import java.util.HashMap;


public class VSMDoc implements Comparable{
	
	private static double threshold = 0.1;
	private double docLength = 1;
	private double vectorScore = 0.0;
	private double docScore = 0.0;
	//private String docAbstract;
	private int ref = 0;
	private int titleScore = 0;
	private int hot = 0;
	private int docID = 0;
	private HashMap<Integer, Double> docVector = new HashMap<Integer, Double>(); 
	

	private void initDocVector(HashMap<Integer, Double> vector)
	{
		docVector = vector;
	}
	
	public VSMDoc(int docId, HashMap<Integer, Double> vector, int ref, 
				  int titleScore, int hot)
	{	
		this.docID = docId;
		this.ref = ref;
		this.titleScore = titleScore;
		this.hot = hot;
		initDocVector(vector);
	}
	
	public HashMap<Integer, Double> getDocVector()
	{
		return docVector;
	}
	
	public double getDocLength()
	{
		return docLength;
	}
	
	public int getDocId()
	{
		return docID;
	}
	
	public double getVectorScore()
	{
		return vectorScore;
	}
	
	public void setVectorScore(double score)
	{
		vectorScore = score;
	}
	
	public double getDocScore()
	{
		return docScore;
	}
	
	public void setDocScore(double score)
	{
		this.docScore = score;
	}
	
	
	public int getRef() {
		return ref;
	}

	public int getTitleScore() {
		return titleScore;
	}

	public int getHot() {
		return hot;
	}

	public void setHot(int hot) {
		this.hot = hot;
	}

	public int compareTo(Object o) {
		// TODO Auto-generated method stub
		VSMDoc doc = (VSMDoc)o;
		if (docScore - doc.docScore > threshold)
		{
			return -1;
		}
		else if (docScore < doc.docScore - threshold)
		{
			return 1;
		}
		else 
		{
			if (docID > doc.docID)
				return -1;
			else if (docID == doc.docID)
				return 0;
			else 
				return 1;
		}
		
	}

}
