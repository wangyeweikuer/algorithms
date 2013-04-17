import java.util.ArrayList;
import java.util.List;

/**
 * TODO 请注释：
 * 
 * @author wangye04 笨笨
 * @email wangye04@baidu.com
 * @datetime Nov 19, 2012 4:47:44 PM
 */
public class TernarySearchTree {

	private class TstNode {

		TstNode[] children = new TstNode[3];
		boolean leaf = false;
		char now;
		TstNode parent;

		public TstNode(char c, TstNode parent) {
			now = c;
			this.parent = parent;
		}

		public void insert(char[] chars, int idx) {
			if (chars[idx] == now) {
				if (idx == chars.length - 1) {
					leaf = true;
					return;
				} else if (children[1] == null) {
					children[1] = new TstNode(chars[idx + 1], this);
				}
				children[1].insert(chars, idx + 1);
			} else if (chars[idx] < now) {
				if (children[0] == null) {
					children[0] = new TstNode(chars[idx], this);
				}
				children[0].insert(chars, idx);
			} else {
				if (children[2] == null) {
					children[2] = new TstNode(chars[idx], this);
				}
				children[2].insert(chars, idx);
			}
		}

		public TstNode contains(char[] chars, int idx) {
			if (chars[idx] == now) {
				if (idx == chars.length - 1) {
					return this;
				} else if (children[1] == null) {
					return null;
				}
				return children[1].contains(chars, idx + 1);
			} else if (chars[idx] < now) {
				if (children[0] == null) {
					return null;
				}
				return children[0].contains(chars, idx);
			} else {
				if (children[2] == null) {
					return null;
				}
				return children[2].contains(chars, idx);
			}
		}

		public void traverse(StringBuilder sb, List<String> reslist) {
			if (children[0] != null) {
				children[0].traverse(sb, reslist);
			}
			sb.append(now);
			if (leaf) {
				reslist.add(sb.toString());
			}
			if (children[1] != null) {
				children[1].traverse(sb, reslist);
			}
			sb.deleteCharAt(sb.length() - 1);
			if (children[2] != null) {
				children[2].traverse(sb, reslist);
			}
		}

		public void deleteBottomUp() {
			if (!canBeRemoved() || parent == null) {
				return;
			}
			for (int i = 0; i < parent.children.length; i++) {
				if (parent.children[i] == this) {
					parent.children[i] = null;
					TstNode p = parent;
					parent = null;
					p.deleteBottomUp();
					break;
				}
			}
		}

		public boolean canBeRemoved() {
			return !leaf && children[0] == null && children[1] == null && children[2] == null;
		}

	}

	private TstNode root;

	public void insert(String s) {
		if (s.length() == 0) {
			return;
		}
		if (root == null) {
			root = new TstNode(s.toCharArray()[0], null);
		}
		root.insert(s.toCharArray(), 0);
	}

	public boolean contains(String s) {
		if (root == null) {
			return false;
		}
		if (s.length() == 0) {
			return true;
		}
		TstNode node = root.contains(s.toCharArray(), 0);
		return node != null && node.leaf;
	}

	public List<String> search(String s) {
		if (root == null) {
			return null;
		}
		TstNode node = root.contains(s.toCharArray(), 0);
		if (node == null) {
			return new ArrayList<String>();
		}
		List<String> reslist = new ArrayList<String>();
		if (node.leaf) {
			reslist.add(s);
		}
		if (node.children[1] != null) {
			node.children[1].traverse(new StringBuilder(s), reslist);
		}
		return reslist;
	}

	public void delete(String s) {
		if (root == null) {
			return;
		}
		TstNode node = root.contains(s.toCharArray(), 0);
		if (node == null) {
			return;
		}
		if (node.leaf) {
			node.leaf = false;
		}
		node.deleteBottomUp();
		if (root.canBeRemoved()) {
			root = null;
		}
	}

	public static void main(String args[]) {
		TernarySearchTree t = new TernarySearchTree();
		t.insert("is");
		t.insert("be");
		t.insert("in");
		t.insert("by");
		t.insert("bell");
		t.insert("best");
		t.insert("as");
		t.insert("a");

		System.out.println(t.contains("a"));
		System.out.println(t.contains("as"));
		System.out.println(t.contains("bel"));
		System.out.println(t.contains("p"));
		System.out.println(t.contains("st"));

		System.out.println(t.search("i"));
		t.delete("is");
		System.out.println(t.search("i"));
		t.delete("in");
		System.out.println(t.search("i"));

		System.out.println(t.search("b"));
		t.delete("b");
		System.out.println(t.search("b"));
		t.delete("bell");
		System.out.println(t.search("b"));
		t.delete("best");
		System.out.println(t.search("b"));
		t.delete("be");
		System.out.println(t.search("b"));
		t.delete("by");
		System.out.println(t.search("b"));

		System.out.println(t.search("a"));
		t.delete("as");
		System.out.println(t.search("a"));
		t.delete("a");
		System.out.println(t.search("a"));
		System.out.println(t.root);
	}
}
