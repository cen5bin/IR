package com.cainiao.ir;


import java.io.DataInputStream;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Scanner;

import com.cainiao.jni.DocVectorNode;
import com.cainiao.jni.Worker;

public class IREngine {
	private static ArrayList<HashMap<Integer , Double>> docVecs = new ArrayList<HashMap<Integer,Double>>();
	private static boolean isInit;
	static{
		isInit = false;
	}
	public static void init(String datapath) throws FileNotFoundException {
		if (isInit) return;
		Worker.initEngine(datapath);
//		IREngine.loadDocVecs(datapath+"pre_index.dat");
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
//		for (int docid : docids) {
//			ret.put(docid, docVecs.get(docid-1));
//		}
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
	
	public static HashMap<Integer, Integer> getDocids(ArrayList<Integer> docids) {
		HashMap<Integer, Integer> ret = new HashMap<Integer, Integer>();
		for (Integer docid : docids) {
			if (ret.containsKey(docid)) {
				Integer tmp = ret.get(docid);
				tmp++;
				ret.put(docid, tmp);
			}
			else ret.put(docid, 1);
		}
		return ret;
	}
	public static int bytesToInt2(byte[] src, int offset) {  
		 int value;    
		    value = (int) ((src[offset] & 0xFF)   
		            | ((src[offset+1] & 0xFF)<<8)   
		            | ((src[offset+2] & 0xFF)<<16)   
		            | ((src[offset+3] & 0xFF)<<24));  
		    return value;  
	}  
	
	public static double getDouble(byte[] b, int index) { 
	    long l; 
	    l = b[0+index]; 
	    l &= 0xff; 
	    l |= ((long) b[1+index] << 8); 
	    l &= 0xffff; 
	    l |= ((long) b[2+index] << 16); 
	    l &= 0xffffff; 
	    l |= ((long) b[3+index] << 24); 
	    l &= 0xffffffffl; 
	    l |= ((long) b[4+index] << 32); 
	    l &= 0xffffffffffl; 
	    l |= ((long) b[5+index] << 40); 
	    l &= 0xffffffffffffl; 
	    l |= ((long) b[6+index] << 48); 
	    l &= 0xffffffffffffffl; 
	    l |= ((long) b[7+index] << 56); 
	    return Double.longBitsToDouble(l); 
	} 
	
	
	private static void loadDocVecs(String datapath) throws FileNotFoundException {
		DataInputStream in = new DataInputStream(new FileInputStream(datapath));
		
		try {
			byte[] bb = new byte[100000];
			while (true) {
				int ret = in.read(bb, 0, 4);
				if (ret == -1) break;
				int size = bytesToInt2(bb, 0);
				
				in.read(bb, 0, 4);
				int docid = bytesToInt2(bb, 0);
				//System.out.print(docid+"\n");
//				if (ret > 0) break;
				int count = (size - 4) / 12;
				in.read(bb, 0, size-4);
				HashMap<Integer, Double> tmp = new HashMap<Integer, Double>();
				for (int i = 0; i < count; i++) {
					//in.read(bb, 0, 4);
					int tid = bytesToInt2(bb, 12*i);
//					System.out.print(tid+"\n");
					//in.read(bb, 0, 8);
					double tfidf = getDouble(bb, 12*i+4);
					tmp.put(tid, tfidf);
//					System.out.print(tfidf+"\n");
				}
				docVecs.add(tmp);
//				break;
			}
		} catch (IOException e) {
				// TODO Auto-generated catch block
				
		}
		finally {
			System.out.print("end");
			if (in != null)
				try {
					in.close();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
		}
		
	}
	
	public static void main(String[] args) throws FileNotFoundException {
		System.out.print("zz");
		init("deploy/");
		System.out.print("zz1");
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
