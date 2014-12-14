/**
 * This file is part of pinyin4j (http://sourceforge.net/projects/pinyin4j/) 
 * and distributed under GNU GENERAL PUBLIC LICENSE (GPL).
 * 
 * pinyin4j is free software; you can redistribute it and/or modify 
 * it under the terms of the GNU General Public License as published by 
 * the Free Software Foundation; either version 2 of the License, or 
 * (at your option) any later version. 
 * 
 * pinyin4j is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 * GNU General Public License for more details. 
 * 
 * You should have received a copy of the GNU General Public License 
 * along with pinyin4j.
 */

/**
 * 
 */
package com.cainiao.ir;

import net.sourceforge.pinyin4j.PinyinHelper;
import net.sourceforge.pinyin4j.format.HanyuPinyinCaseType;
import net.sourceforge.pinyin4j.format.HanyuPinyinOutputFormat;
import net.sourceforge.pinyin4j.format.HanyuPinyinToneType;
import net.sourceforge.pinyin4j.format.HanyuPinyinVCharType;

/**
 * A demostration to show how does the pinyin4j work
 * 
 * @author Li Min (xmlerlimin@gmail.com)
 * 
 */
public class MainDemo {

    /**
     * @param args
     */
    public static void main(String[] args) {

        // deal with Chinese sentence
        {
            HanyuPinyinOutputFormat outputFormat = new HanyuPinyinOutputFormat();

            // defautlt output format
          

            // without tone numbers or tone marks
            System.out.println("without tone numbers or tone marks");
            outputFormat.restoreDefault();
            outputFormat.setToneType(HanyuPinyinToneType.WITHOUT_TONE);
            System.out.println(PinyinHelper.toHanyuPinyinString("我的中国心", outputFormat, " "));
            System.out.println("***");

           
            System.out.println("***");
        }

        // deal with Chinese character
       
    }
}
