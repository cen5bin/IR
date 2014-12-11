package com.cainiao.servlet;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.cainiao.jni.DocVectorNode;
import com.cainiao.jni.Worker;


/**
 * Servlet implementation class Test
 */
@WebServlet("/Test")
public class Test extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public Test() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		Worker.initEngine("/usr/lib/jni/data/");;
		PrintWriter out = response.getWriter();
		out.print("zz\n");
		int[] ret = Worker.getTids(new String[]{"刘国梁"}, 1);
		//	System.out.print(ret[0]);
			ret = Worker.getDocids(ret, 1);
			for (int i : ret)
				out.print(i+" ");
			DocVectorNode[] tt = Worker.getDocVector(1);
			out.print("\n"+tt.length+"\n");
			for (DocVectorNode tmp : tt)
				out.print(tmp.tid+","+tmp.tfidf+"\n");
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
	}

}
