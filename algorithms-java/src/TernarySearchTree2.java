import java.util.List;

/**
 * TODO 请注释：
 * 
 * @author wangye04 笨笨
 * @email wangye04@baidu.com
 * @datetime Nov 19, 2012 4:47:44 PM
 */
public class TernarySearchTree2 {

	private class TstNode {

		TstNode lef;
		TstNode rig;
		TstNode mid;
		boolean leaf;
		char now;

		// int childNum;

		public TstNode(char c) {
			now = c;
		}

		public TstNode() {
		}

		private TstNode findRigAndOthers(char c) {
			if (rig == null || rig.now == c) {
				return rig = (rig == null ? new TstNode(c) : rig);
			} else if (rig.now < c) {
				return rig.findLefAndOthers(c);
			} else {
				return rig.findRigAndOthers(c);
			}

		}

		private TstNode findLefAndOthers(char c) {
			if (lef == null || lef.now == c) {
				return lef = (lef == null ? new TstNode(c) : lef);
			} else if (lef.now < c) {
				return lef.findRigAndOthers(c);
			} else {
				return lef.findLefAndOthers(c);
			}
		}

		public void insert(char[] chars, int idx) {
			if (idx >= chars.length) {
				leaf = true;
				return;
			}
			if (mid == null) {
				mid = new TstNode(chars[idx]);
				mid.insert(chars, idx + 1);
			} else if (chars[idx] < mid.now) {
				if (lef == null || chars[idx] == lef.now) {
					lef = (lef == null ? new TstNode(chars[idx]) : lef);
					lef.insert(chars, idx + 1);
				} else if (chars[idx] < lef.now) {
					TstNode node = lef.findLefAndOthers(chars[idx]);
					node.insert(chars, idx + 1);
				} else {
					TstNode node = lef.findRigAndOthers(chars[idx]);
					node.insert(chars, idx + 1);
				}
			} else {
				if (rig == null || chars[idx] == rig.now) {
					rig = (rig == null ? new TstNode(chars[idx]) : rig);
					rig.insert(chars, idx + 1);
				} else if (chars[idx] < rig.now) {
					TstNode node = rig.findRigAndOthers(chars[idx]);
					node.insert(chars, idx + 1);
				} else {
					TstNode node = rig.findLefAndOthers(chars[idx]);
					node.insert(chars, idx + 1);
				}
			}
		}

		/**
		 * @return
		 */
		public void findAll(List<String> suffixList, StringBuilder sb) {
			if (leaf) {
				suffixList.add(sb.toString());
			}
			TstNode[] ts = new TstNode[]{lef, mid, rig};
			for (TstNode t : ts) {
				if (t != null) {
					sb.append(t.now);
					findAll(suffixList, sb);
					sb.deleteCharAt(sb.length() - 1);
				}
			}
		}

		/**
		 * @param chars
		 * @param i
		 * @return
		 */
		public TstNode searchOne(char[] chars, int idx) {
			if (idx >= chars.length) {
				return this;
			}
			if (mid == null) {
				return null;
			} else if (chars[idx] == mid.now) {
				return mid.searchOne(chars, idx + 1);
			} else if (chars[idx] < mid.now) {
				if (lef == null) {
					return null;
				} else if (chars[idx] == lef.now) {
					return lef.searchOne(chars, idx + 1);
				} else if (chars[idx] < lef.now) {

				} else {
				}
			} else {
			}
		}
	}

	private final TstNode root;

	public TernarySearchTree2() {
		root = new TstNode();
		root.leaf = true;
	}

	public void insert(String s) {
		if (s.length() == 0) {
			return;
		}
		root.insert(s.toCharArray(), 0);
	}

	// public List<String> search(String s) {
	// int idx = 0;
	// TstNode p = root;
	// while (idx < s.length()) {
	// p = p.select(s.charAt(idx++), false);
	// if (p == null) {
	// return null;
	// }
	// }
	// List<String> suffixList = new ArrayList<String>();
	// StringBuilder sb = new StringBuilder();
	// p.findAll(suffixList, sb);
	// return suffixList;
	// }
	public boolean searchOne(String s) {
		TstNode node = root.searchOne(s.toCharArray(), 0);
		return node != null && node.leaf == true;
	}

	public void delete(String s) {

	}

	public static void main(String args[]) {
		TernarySearchTree2 t = new TernarySearchTree2();
		t.insert("is");
		t.insert("be");
		t.insert("in");
		t.insert("by");
		t.insert("bell");
		t.insert("best");
		// t.insert("bey");
		t.insert("as");
		System.out.println(t.search("b"));
	}
}
