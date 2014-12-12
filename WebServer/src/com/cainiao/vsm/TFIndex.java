package com.cainiao.vsm;

public class TFIndex {
	private int docID;
	private int termID;
	
	public TFIndex(int docID, int termID)
	{
		this.docID = docID;
		this.termID = termID;
	}

	public int getDocID() {
		return docID;
	}

	public void setDocID(int docID) {
		this.docID = docID;
	}

	public int getTermID() {
		return termID;
	}

	public void setTermID(int termID) {
		this.termID = termID;
	}

}
