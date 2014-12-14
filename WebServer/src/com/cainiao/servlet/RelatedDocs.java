package com.cainiao.servlet;

import java.io.IOException;
import java.sql.SQLException;
import java.util.ArrayList;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.cainiao.dao.DataReader;
import com.cainiao.entity.News;
import com.cainiao.ir.IRDevideWord;
import com.cainiao.ir.KMPMatcher;

/**
 * Servlet implementation class RelatedDocs
 */
@WebServlet("/RelatedDocs")
public class RelatedDocs extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public RelatedDocs() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		
		String query = request.getParameter("content");
		query = new String(query.getBytes("ISO8859-1"),"UTF-8");
		ArrayList<String> ret = IRDevideWord.work(query);
		
		String param = request.getParameter("param");
		String[] pp = param.split("#");
		ArrayList<Integer> dd = new ArrayList<Integer>();
		for (String ss : pp) dd.add(Integer.parseInt(ss));
		String page0 = request.getParameter("page");
		int page = 1;
		if (page0 != null) page = Integer.parseInt(page0);
		System.out.print(page+"\n");
		final int count_per_page = 20;
		int start = count_per_page * (page-1);
		int end = start + count_per_page - 1;
		if (end >= dd.size()) end = dd.size() - 1;
		try {
			ArrayList<News> news = DataReader.getNews(dd.subList(start, end));
			KMPMatcher.setMaxSize(100);
			for (News n1 : news) {
				n1.content = "";//KMPMatcher.match(n1.content, ret);
				n1.title = KMPMatcher.match(n1.title, ret);
			}
			HttpSession session = request.getSession();
			session.setAttribute("results", news);
			session.setAttribute("pagecount", (dd.size()+count_per_page-1)/count_per_page);
			session.setAttribute("content", query);
			System.out.print(query);
			response.sendRedirect("./relateddocs.jsp");
//			request.getRequestDispatcher("./relateddocs.jsp").forward(request, response);

		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	
	}

}
