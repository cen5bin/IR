package com.cainiao.ir;

import java.io.IOException;
import java.io.StringReader;
import java.util.ArrayList;

import org.wltea.analyzer.core.IKSegmenter;
import org.wltea.analyzer.core.Lexeme;

public class IRDevideWord {
	public static ArrayList<String> work(String s) throws IOException {
		ArrayList<String> ret = new ArrayList<String>();
		StringReader sr = new StringReader(s);
		IKSegmenter ik = new IKSegmenter(sr, true);
		Lexeme le  = null;
		while ((le = ik.next()) != null) ret.add(le.getLexemeText());
		return ret;
	}
}
