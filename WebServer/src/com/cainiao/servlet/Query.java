package com.cainiao.servlet;

import java.io.IOException;
import java.io.PrintWriter;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.HashMap;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.cainiao.dao.DataReader;
import com.cainiao.entity.News;
import com.cainiao.entity.ResultItem;
import com.cainiao.ir.IRDevideWord;
import com.cainiao.ir.IREngine;
import com.cainiao.ir.KMPMatcher;
import com.cainiao.recommend.QueryRecommend;
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
		String page0 = request.getParameter("page");
		int page = 1;
		if (page0 != null) page = Integer.parseInt(page0);
//		int flag = Integer.parseInt(request.getParameter("flag"));
		
//		if (flag == 1)
		
		
		ArrayList<String> ret = IRDevideWord.work(query);
		for (String s : ret) System.out.print(s+"|");
		System.out.print("\n");
		
		//ArrayList<String> tmp1 =  QueryRecommend.getRecommendations(ret, 4);
		
		
		ArrayList<Integer>  tids = IREngine.getTids(ret);
		ArrayList<Integer> docids = IREngine.query(tids);
//		System.out.print("zzz\n");
		HashMap<Integer, Integer> tt = IREngine.getDocids(docids);
//		System.out.print("-----------------------\n");
//		for (Integer key : tt.keySet()) {
//			System.out.print(key+":"+tt.get(key)+"\n");
//		}
//		System.out.print("-----------------------\n");
//		System.out.print("zzz3\n");

		HashMap<Integer, HashMap<Integer, Double>> vecs = IREngine.getDocVectors(docids);
//		System.out.print("zzz4\n");

		
		
		ArrayList<Integer> dd = VSMInterface.getTopK(vecs, tids, tt, null, null, 300);

		//		for (Integer tmp : dd) System.out.print(tmp+" ");
		final int clusterNum = 4;
		HashMap<Integer, Integer> ret1 = VSMInterface.getCluster(clusterNum);
		HashMap<Integer, ArrayList<Integer>> clusters = new HashMap<Integer, ArrayList<Integer>>();
		for (Integer docid : ret1.keySet()) {
			Integer key = ret1.get(docid);
			if (clusters.containsKey(key)) {
				((ArrayList<Integer>)(clusters.get(key))).add(docid);
			}
			else {
				ArrayList<Integer> tt1 = new ArrayList<Integer>();
				tt1.add(docid);
				clusters.put(key, tt1);
			}
		}
		
		
		//for (String ss : tmp1)System.out.print(ss+"\n");
//		System.out.print("zzz2\n");
		response.setContentType("text/html; charset=UTF-8");
		response.setCharacterEncoding("UTF-8");
		PrintWriter out = response.getWriter();
	
		
		try {
			final int count_per_page = 10;
			int start = count_per_page * (page-1);
			int end = start + count_per_page - 1;
			if (end >= dd.size()) end = dd.size() - 1;
			ArrayList<News> news = DataReader.getNews(dd.subList(start, end));
			KMPMatcher.setMaxSize(100);
			for (News n1 : news) {
				n1.content = KMPMatcher.match(n1.content, ret);
				n1.title = KMPMatcher.match(n1.title, ret);
		
			}
			HttpSession session = request.getSession();
			session.setAttribute("results", news);
			session.setAttribute("pagecount", (dd.size()+9)/10);
			session.setAttribute("cluster", clusters);
			session.setAttribute("clusterinfo", ret1);
			request.getRequestDispatcher("/result.jsp").include(request, response);
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		
		
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
	}

}
