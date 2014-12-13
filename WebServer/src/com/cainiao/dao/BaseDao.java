package com.cainiao.dao;

import java.beans.PropertyDescriptor;
import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import com.cainiao.entity.News;

public class BaseDao {
	private static String url ="jdbc:mysql://127.0.0.1:3306/ir";
	private static String name = "root";
	private static String password = "asd123";
	protected static Connection conn;
	private static boolean inited = false;
	static{
		conn = getConnection();
		inited = true;
	}
	public static Connection getConnection(){
		if (inited) return conn;
		Connection conn = null;
		try {
			Class.forName("com.mysql.jdbc.Driver");
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		}
		try {
			conn = DriverManager.getConnection(url,name,password);
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return conn;
	}
	
	public static void main(String[] args) throws Exception {
		News news = new News();
		news.id = 1;
		List<News> ret = find(news);
		System.out.print(ret.get(0).url);
	}
	
	
	public static ResultSet query(String sql) throws SQLException {
		PreparedStatement st = conn.prepareStatement(sql);
		return st.executeQuery();
	}
	
	
	/**
	 * 将查询参数填入
	 * @param o
	 * @return
	 * @throws Exception
	 */
	public static ArrayList find(Object o) throws Exception {
		//获取类
		Class clazz = o.getClass();
		// 获取类的所有属性，返回Field数组
		Field[] fields = clazz.getDeclaredFields();
		
		StringBuffer sql = new StringBuffer("select * ");
//		for (Field field : fields) {
//			if( field.getName().equals("_abstract") )
//			sql.append("abstract"+",");
//			else sql.append(field.getName()+",");
//		}
		sql = new StringBuffer( sql.substring(0,sql.length()-1));
		sql.append(" from	" + clazz.getSimpleName().toLowerCase());
		sql.append(" where 1=1	");
		
		//再遍历一边添加where条件
		for (Field field : fields) {
			//如果属性有值
			System.out.println(field.getName());
			 PropertyDescriptor pd = new PropertyDescriptor(field.getName(), clazz);
			 Method m = pd.getReadMethod();//获得读方法
			 
			 if(m.invoke(o)  != null){
				 if( field.getName().equals("_abstract") ) {
					 sql.append(" and abstract = " + m.invoke(o));
					 System.out.print(sql+"\n");
				 }
				 else {
					 sql.append(" and " + field.getName()+" = " + m.invoke(o));
					 System.out.print("zz\n");
				 }
			}
		}
		System.out.println(sql.toString());
		

		//获得数据库连接
//		Connection conn = getConnection();
		ResultSet resultSet = null;
		PreparedStatement pstmt = null;
		ArrayList resultList = new ArrayList();
		pstmt = conn.prepareStatement(sql.toString());
		resultSet = pstmt.executeQuery();
		while (resultSet.next()) {
			Object instance = clazz.newInstance();
			
			for (Field field : fields) {
				if(field.getType().toString().equals("class java.lang.String")){
					String ss = field.getName();
					if (ss.equals("_abstract")) ss = "abstract";
					 String val = resultSet.getString(ss);
					 String name = field.getName();
					 if( name.equals("abstract") ) name = "_"+name;
					 PropertyDescriptor pd = new PropertyDescriptor(name, clazz);
					 Method m = pd.getWriteMethod();//获得写方法
					 m.invoke(instance, val);
				}
			}
			resultList.add(instance);
		}
		return resultList;
	}

}
