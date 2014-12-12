package com.cainiao.servlet;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.HashMap;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.cainiao.ir.IRDevideWord;
import com.cainiao.ir.IREngine;
import com.cainiao.vsm.VSMInterface;

/**
 * Servlet implementation class Query
 */
@WebServlet("/Query")
public class Query extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public Query() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		
		IREngine.init("/usr/lib/jni/data/");
		
		
		String query = request.getParameter("content");
		query = new String(query.getBytes("ISO8859-1"),"UTF-8");
//		System.out.print(query);
		
		ArrayList<String> ret = IRDevideWord.work(query);
		for (String s : ret) System.out.print(s+"|");
		System.out.print("\n");
		
		ArrayList<Integer>  tids = IREngine.getTids(ret);
		ArrayList<Integer> docids = IREngine.query(tids);
		
		HashMap<Integer, Integer> tt = IREngine.getDocids(docids);
		System.out.print("-----------------------\n");
		for (Integer key : tt.keySet()) {
			System.out.print(key+":"+tt.get(key)+"\n");
		}
		System.out.print("-----------------------\n");

		HashMap<Integer, HashMap<Integer, Double>> vecs = IREngine.getDocVectors(docids);
		
		ArrayList<Integer> dd = VSMInterface.getTopK(vecs, tids, tt, 10);
		for (Integer tmp : dd) System.out.print(tmp+" ");
		VSMInterface.getCluster(4);
		response.setContentType("text/html; charset=UTF-8");
		response.setCharacterEncoding("UTF-8");
		PrintWriter out = response.getWriter();
		
//		out.print("tids:\n");
//		for (Integer tid : tids) out.print(tid+" ");
//		out.print("\ndocids\n");
//		for (Integer docid : docids) out.print(docid + " ");
//		out.print("\n");
//		out.print(query);
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
	}

}
