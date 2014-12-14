package com.cainiao.recommend;
/**
 * �ַ�༭����
 * 
 * ����һ���ַ�֮�����ƶȼ���ķ�����
 * ���ַ�S��T����Sת��T����Ҫ�Ĳ��롢ɾ������������������S��T�ı༭·����
 * ������̵�·�������༭���롣
 * 
 * ����ʹ����һ�ֶ�̬�滮��˼����༭���롣
 * 
 * @author heartraid
 *
 */
public class  EditDistance{
	
	 private static int isModify(char c1, char c2)
	 {
		 if (c1 == c2)
			 return 0;
		 else
			 return 1;
	 }
	 
	 private static int minDis(int d1, int d2, int d3)
	 {
		 if (d1 < d2)
		 {
			 if (d1 < d3)
				 return d1;
			 else
				 return d3;
		 }
		 else
		 {
			 if (d2 < d3)
				 return d2;
			 else
				 return d3;
		 }
	 }
	
	 public static int getDistance(String s1, String s2)
	 {
		 if (s1.length() == 0 || s2.length() == 0)
			 return Integer.MAX_VALUE;
		 int len1 = s1.length();
		 int len2 = s2.length();
		 int m[][] = new int[len1][len2];
		 for (int i = 0; i < len1; i++)
			 m[i][0] = i;
		 for (int j = 0; j < len2; j++)
			 m[0][j] = j;
		 for (int i = 1; i < len1; i++)
		 {
			 for (int j = 1; j < len2; j++)
			 {
				 m[i][j] = minDis(m[i-1][j-1]+isModify(s1.charAt(i), s2.charAt(j)), m[i-1][j]+1, m[i][j-1]+1);
			 }
		 }
		 return m[len1-1][len2-1];
	 }
	 
	 
	public static void main(String[] args) {
		System.out.println(getDistance("", "���˹zhasdas��˹�ﰡʵ��ʵ��"));
		//System.out.println("�༭�����ǣ�"+new EditDistance("���˹ nba���� ��÷�� ������ �ƶ� �ܿ�ѷ","��� NBA").getDistance());
	}

}
