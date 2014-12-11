package entity;

import java.util.HashMap;


public class VSMDoc implements Comparable{
	
	private double docLength;
	private  double docScore;
	//private String docAbstract;
	private int ref;
	private int docID;
	private HashMap<Integer, Double> docVector = new HashMap<Integer, Double>(); 
	
	private void calculateDocLength()
	{
//		double sum = 0;
//		for (int i = 0; i < 500; i++)
//		{
//			double tmp = docVector.get(i);
//			sum += tmp * tmp;
//		}
//		double len = Math.sqrt(sum);
		this.docLength = 1;
//		double sum = 0;
//		for (int i = 0 ;i < indexList.size(); i++)
//		{
//			double tf = VSMEngine.getTFFromEngine(indexList.get(i));
//			sum += tf * tf;
//		}
//		double len = Math.sqrt(sum);
//		this.docLength = len;
	}
	
	private void initDocVector(HashMap<Integer, Double> vector)
	{
		docVector = vector;
//		Random random = new Random();
//		for (int i = 0; i < 500; i++)
//		{			
//			docVector.put(i, random.nextDouble()%100);
//		}
//		for (int i = 0; i < queryTermIDList.size(); i++) 
//		{
//			double wf;
//			TFIndex index = new TFIndex(docID, queryTermIDList.get(i));
//			double tf = VSMEngine.getTFFromEngine(index);
//			if (tf > 0)
//				wf = 1 + Math.log(tf)/Math.log(2);
//			else
//				wf = 0.0;
//			double idf = VSMEngine.getIDFFromEngine(queryTermIDList.get(i));
//			double weight = idf * wf;
//			if (weight != 0)
//			{
//				docVector.put(index.getTermID(), weight);
//			}
//		}
	}
	
	public VSMDoc(int docId, HashMap<Integer, Double> vector, int ref)
	{	
		this.docID = docId;
		this.ref = ref;
		initDocVector(vector);
		calculateDocLength();
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
	
	public double getScore()
	{
		return docScore;
	}
	
	public void setScore(double score)
	{
		docScore = score;
	}

	public int compareTo(Object o) {
		// TODO Auto-generated method stub
		VSMDoc doc = (VSMDoc)o;
		if (ref > doc.ref)
		{
			return -1;
		}
		else if (ref < doc.ref)
		{
			return 1;
		}
		else 
		{
			if (docScore > doc.docScore)
				return -1;
			else if (docScore == doc.docScore)
				return 0;
			else 
				return 1;
		}
		
	}

}
