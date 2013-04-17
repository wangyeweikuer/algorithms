/**
 * @author wangye04 笨笨
 * @email wangye04@baidu.com
 * @datetime Jun 29, 2012 11:44:18 PM
 */
public class ImageDithering {

	public int count(String dithered, String[] screen) {
		int c = 0;
		boolean hash[] = new boolean[26];
		for (int i = 0; i < dithered.length(); i++) {
			hash[dithered.charAt(i) - 'A'] = true;
		}
		for (String s : screen) {
			for (int i = 0; i < s.length(); i++) {
				char cc = s.charAt(i);
				if (hash[cc - 'A']) {
					c++;
				}
			}
		}
		return c;
	}
}
