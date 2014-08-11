package org.wangye.poi;

import java.io.FileOutputStream;
import java.io.IOException;
import java.lang.reflect.Field;
import java.text.SimpleDateFormat;
import java.util.Date;

import org.apache.poi.hssf.usermodel.HSSFRow;
import org.apache.poi.hssf.usermodel.HSSFSheet;
import org.apache.poi.hssf.usermodel.HSSFWorkbook;
import org.apache.poi.ss.usermodel.Cell;
import org.junit.Test;

/**
 * TODO 请注释：
 * @author wangye04 笨笨
 * @email wangye04@baidu.com
 * @datetime Dec 27, 2013 5:17:36 PM
 */
public class TestClass {
	
	@Test
	public void test() throws Exception, IOException {
		System.err.println("xx");
		HSSFWorkbook hw = new HSSFWorkbook();
		HSSFSheet sheet = hw.createSheet("某站点总体情况");
		HSSFRow r = sheet.createRow(0);
		r.createCell(0, Cell.CELL_TYPE_STRING).setCellValue("文件名");
		r.createCell(1, Cell.CELL_TYPE_STRING).setCellValue("编辑次数");
		r.createCell(2, Cell.CELL_TYPE_STRING).setCellValue("访问地址");
		for (int i = 1; i <= 10; i++) {
			r = sheet.createRow(i);
			r.createCell(0, Cell.CELL_TYPE_STRING).setCellValue("file" + i);
			r.createCell(1, Cell.CELL_TYPE_NUMERIC).setCellValue(i);
			r.createCell(2, Cell.CELL_TYPE_STRING).setCellValue("http://" + i);
		}
		sheet = hw.createSheet("某站点详细情况");
		r = sheet.createRow(0);
		r.createCell(0, Cell.CELL_TYPE_STRING).setCellValue("文件名");
		r.createCell(1, Cell.CELL_TYPE_STRING).setCellValue("用户名");
		r.createCell(2, Cell.CELL_TYPE_STRING).setCellValue("编辑次数");
		r.createCell(3, Cell.CELL_TYPE_STRING).setCellValue("最后时间");
		r.createCell(4, Cell.CELL_TYPE_STRING).setCellValue("访问地址");
		for (int i = 1; i <= 10; i++) {
			r = sheet.createRow(i);
			r.createCell(0, Cell.CELL_TYPE_STRING).setCellValue("file" + i);
			r.createCell(1, Cell.CELL_TYPE_STRING).setCellValue("user" + i);
			r.createCell(2, Cell.CELL_TYPE_NUMERIC).setCellValue(i);
			r.createCell(3, Cell.CELL_TYPE_STRING).setCellValue(new SimpleDateFormat().format(new Date()));
			r.createCell(4, Cell.CELL_TYPE_STRING).setCellValue("http://" + i);
		}
		hw.write(new FileOutputStream("/tmp/a.xlsx"));
	}
	
	@Test
	public void test2() throws NoSuchFieldException, SecurityException, IllegalArgumentException,
			IllegalAccessException {
		String h = "xxxxxxx";
		String hello = "hello world";
		System.out.println("Hello: " + hello);
		String xx = new String("hello world");
		String yy = "hello world";
		System.out.println("xx==hello : " + (xx == hello));
		Field hello_field = String.class.getDeclaredField("value");
		hello_field.setAccessible(true);
		char[] value = (char[]) hello_field.get(hello);
		value[5] = '_';// 修改hello所指向的值
		System.out.println("Hello: " + hello);
		System.out.println("xx==hello : " + (xx == hello));
		System.out.println("yy==hello:" + (hello == yy));
		System.out.println("xx==yy:" + (xx == yy) + "\n");
		System.out.println("xx: " + xx);
		System.out.println("yy: " + yy);
		System.out.println("Hello: " + hello);
		System.out.println(h);
	}
}
