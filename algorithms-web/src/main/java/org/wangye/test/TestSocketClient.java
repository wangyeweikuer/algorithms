package org.wangye.test;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.Socket;
import java.util.Random;

public class TestSocketClient {

	public TestSocketClient() throws IOException {
		Socket socket = new Socket("127.0.0.1", 10000);
		OutputStream out = socket.getOutputStream();
		BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
		while (true) {
			String param = generate();
			out.write(param.getBytes());
			out.flush();
			String res = in.readLine();
			System.out.println(res);
		}
	}

	private String generate() {
		Random r = new Random(System.currentTimeMillis());
		int n = r.nextInt(5);
		StringBuffer sb = new StringBuffer("  ");
		for (int i = 0; i < n; i++) {
			int k = r.nextInt(2);
			if (k == 0) {
				sb.append("kk").append(" ");
			} else {
				int v = r.nextInt(100);
				sb.append(v).append("  ");
			}
		}
		return sb.toString();
	}

	public static void main(String[] args) throws IOException {
		System.out.println("socket client started ...");
		new TestSocketClient();
	}
}
