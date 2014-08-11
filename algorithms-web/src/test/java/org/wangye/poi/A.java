package org.wangye.poi;

import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PipedInputStream;
import java.io.PipedOutputStream;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

/**
 * TODO 请注释：
 * @author wangye04 笨笨
 * @email wangye04@baidu.com
 * @datetime May 13, 2014 9:36:12 AM
 */
public class A {
	
	public static void main(String[] args) throws IOException {
		final PipedOutputStream src = new PipedOutputStream();
		PipedInputStream pis = new PipedInputStream(src, 100);
		ExecutorService pool = Executors.newFixedThreadPool(5);
		for (int i = 0; i <= 10; i++) {
			final int k = i;
			pool.submit(new Runnable() {
				
				@Override
				public void run() {
					try {
						while (true) {
							src.write(("" + k + k + k + k + k + k + k + k + k + k + k + k + "\n").getBytes());
							Thread.sleep(100);
						}
					} catch (Exception e) {
						e.printStackTrace();
					}
				}
			});
		}
		InputStreamReader isr = new InputStreamReader(pis, "UTF-8");
		char[] cs = new char[10];
		while (true) {
			int i = isr.read(cs);
			if (i == -1) {
				break;
			}
			for (int k = 0; k < i; k++) {
				System.out.print(cs[k]);
			}
		}
	}
}
