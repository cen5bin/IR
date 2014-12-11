package com.cainiao.ir;


import java.util.ArrayList;
import java.util.HashMap;
import java.util.Scanner;

import com.cainiao.jni.DocVectorNode;
import com.cainiao.jni.Worker;

public class IREngine {
	private static boolean isInit;
	static{
		isInit = false;
	}
	public static void init(String datapath) {
		if (isInit) return;
		Worker.initEngine(datapath);
		isInit = true;
	}
	public static HashMap<Integer, HashMap<Integer, Double>> getDocVectors(ArrayList<Integer> docids) {
		if (!isInit) return null;
		HashMap<Integer, HashMap<Integer, Double>> ret = new HashMap<Integer, HashMap<Integer,Double>>();
		for (int docid : docids) {
			DocVectorNode[] tmp = Worker.getDocVector(docid);
			HashMap<Integer, Double> vec = new HashMap<Integer, Double>();
			for (DocVectorNode node : tmp)
				vec.put(node.tid, node.tfidf);
			ret.put(docid, vec);
		}
		return ret;
	}
	
	public static ArrayList<Integer> query(ArrayList<Integer> tids) {
		if (!isInit) return null;
		ArrayList<Integer> ret = new ArrayList<Integer>();
		int[] tids1 = new int[tids.size()];
		for (int i = 0; i < tids.size(); i++)
			tids1[i] = tids.get(i);
		int[] tmp = Worker.getDocids(tids1, tids.size());
		for (int docid : tmp) ret.add(docid);
		return ret;
	}
	
	public static ArrayList<Integer> getTids(ArrayList<String> terms) {
		if (!isInit) return null;
		ArrayList<Integer> ret = new ArrayList<Integer>();
		String[] terms1 = new String[terms.size()];
		for (int i = 0; i < terms.size(); i++)
			terms1[i] = terms.get(i);
		int[] tmp = Worker.getTids(terms1, terms.size());
		for (int tid : tmp) ret.add(tid);
		return ret;
	}
	
	public static void main(String[] args) {
		init("deploy/");
		
		Scanner in = new Scanner(System.in);
		while (in.hasNext()) {
			ArrayList<String> terms = new ArrayList<String>();
			int n = in.nextInt();
			for (int i = 0; i < n; i++) {
				String string = in.next();
				terms.add(string);
			}
			ArrayList<Integer> tids = getTids(terms);
			System.out.print("词id:\n");
			for (int i = 0; i < tids.size(); i++)
				System.out.print(terms.get(i)+": "+tids.get(i)+"\n");
			System.out.print("查询得到的docid:\n");
			ArrayList<Integer> docids = query(tids);
			for (int docid : docids) System.out.print(docid+" ");
			System.out.print("\n");
		}
	}
}
