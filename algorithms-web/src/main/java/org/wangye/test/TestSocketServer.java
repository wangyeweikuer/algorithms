package org.wangye.test;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class TestSocketServer {

	private final ServerSocket ss;

	private void calc(Socket socket) throws IOException {
		BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
		OutputStream out = socket.getOutputStream();
		while (true) {
			String line = in.readLine();
			String[] nums = line.split(" ");
			String res = "";
			if (nums == null || nums.length < 2) {
				res = "input invalid:" + line + "\n";
			} else {
				Integer rr = null;
				for (int i = 0; i < nums.length; i++) {
					try {
						int nn = Integer.parseInt(nums[i]);
						if (rr == null) {
							rr = 0;
						}
						rr += nn;
					} catch (Exception e) {
						res = "exception happened:" + e.getMessage() + "\n";
						rr = null;
						break;
					}
				}
				if (rr != null) {
					res = "result:" + rr + "\n";
				}
			}
			out.write(res.getBytes());
			out.flush();
		}
	}

	public TestSocketServer() throws IOException {
		ss = new ServerSocket(10000);
		Socket socket = ss.accept();
		calc(socket);
		socket.close();
	}

	public static void main(String[] args) throws IOException {
		System.out.println("socket server started ...");
		new TestSocketServer();
	}
}
