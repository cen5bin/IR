package com.cainiao.jni;

public class Worker {
	static
	{
		System.loadLibrary("IR");
	}
	public static native int[] getTids(String[] terms, int n);
	public static native int[] getDocids(int[] tids, int n);
	public static native DocVectorNode[] getDocVector(int docid);
	public static native void initEngine(String datapath);
	public static void main(String[] args) {
		
		initEngine("deploy/");
		//System.out.print("zz");;
		int[] ret = getTids(new String[]{"刘国梁"}, 1);
	//	System.out.print(ret[0]);
		ret = getDocids(ret, 1);
		for (int i : ret)
			System.out.print(i+" ");
		DocVectorNode[] tt = getDocVector(1);
		System.out.print("\n"+tt.length+"\n");
		for (DocVectorNode tmp : tt)
			System.out.print(tmp.tid+","+tmp.tfidf+"\n");
	}
}
