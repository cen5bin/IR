package com.cainiao.servlet;

import java.io.IOException;
import java.io.PrintWriter;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.cainiao.dao.DataReader;

/**
 * Servlet implementation class AutoCompletion
 */
@WebServlet("/AutoCompletion")
public class AutoCompletion extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public AutoCompletion() {
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
		//query = new String(query.getBytes("ISO8859-1"),"UTF-8");
		System.out.print(query+"\n");
		try {
			List<String> ret = DataReader.getList(query);
			response.setContentType("text/html; charset=UTF-8");
			response.setCharacterEncoding("UTF-8");
			PrintWriter out = response.getWriter();
			System.out.print(ret.size());
			if (ret.size() == 0) ret = DataReader.getList1(query);
			if (ret.size() == 0 || query.equals("")) out.print("");
			else {
				//out.print("zz");
				//out.print("<ul>");
				if (ret.size() > 10) ret = (ret.subList(0, 9));
				for (String s : ret) {
					String ss = String.format("<div onclick=\"insert('%s')\">%s</div>", s, s);
					out.print(ss);
				}
				//out.print("</ul>");
			}
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}

}
