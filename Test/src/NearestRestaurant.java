import java.util.*;

public class NearestRestaurant {

	// @include
	public static List<BinaryTree<Integer>> rangeQueryOnBST(
			BinaryTree<Integer> n, Integer L, Integer U) {
		List<BinaryTree<Integer>> ret = new ArrayList<BinaryTree<Integer>>();
		BinaryTree<Integer> first = findFirstLarger(n,L);
		if(first!=null && first.getData()<=U){
			ret.add(first);
			BinaryTree<Integer> succ = findSuccessor(n, first);
			while(succ!=null && succ.getData()<=U){
				ret.add(succ);
				succ = findSuccessor(n, succ);
			}
		}
		return ret;
	}

	private static BinaryTree<Integer> findFirstLarger(
			BinaryTree<Integer> root, Integer L) {
		BinaryTree<Integer> first = null;
		BinaryTree<Integer> cur = root;
		while(cur!=null){
			if(L < cur.getData()){
				first = cur;
				cur = cur.getLeft();
			}else if(L == cur.getData()){
				first = cur;
				break;
			}else{
				cur = cur.getRight();
			}
		}
		return first;
	}

	private static BinaryTree<Integer> findSuccessor(BinaryTree<Integer> root,
			BinaryTree<Integer> node) {
		BinaryTree<Integer> succ = null;
		if(node.getRight()!=null){
			succ = node.getRight();
			while(succ.getLeft()!=null)
				succ = succ.getLeft();
			return succ;
		}
		
		while(root !=null){
			if(node.getData() < root.getData()){
				succ = root;
				root = root.getLeft();
				
			}else if(node.getData() == root.getData()){
				break;
			}else{
				root = root.getRight();
				
			}
			
		}
		return succ;
	}

	// @exclude

	public static void main(String[] args) {
		// 3
		// 2 5
		// 1 4 6
		BinaryTree<Integer> root = new BinaryTree<>(3, null, null);
		root.setLeft(new BinaryTree<>(2, null, null));
		root.getLeft().setParent(root);
		root.getLeft().setLeft(new BinaryTree<>(1, null, null));
		root.getLeft().getLeft().setParent(root.getLeft());
		root.setRight(new BinaryTree<>(5, null, null));
		root.getRight().setParent(root);
		root.getRight().setLeft(new BinaryTree<>(4, null, null));
		root.getRight().getLeft().setParent(root.getRight());
		root.getRight().setRight(new BinaryTree<>(6, null, null));
		root.getRight().getRight().setParent(root.getRight());
		List<BinaryTree<Integer>> res = rangeQueryOnBST(root, 2, 5);
		assert (res.size() == 4);
		for (BinaryTree<Integer> l : res) {
			assert (l.getData() >= 2 && l.getData() <= 5);
		}
		res = rangeQueryOnBST(root, -1, 0);
		assert (res.isEmpty());
		res = rangeQueryOnBST(root, 10, 25);
		assert (res.isEmpty());
		res = rangeQueryOnBST(root, -10, 30);
		assert (res.size() == 6);
		for (BinaryTree<Integer> l : res) {
			assert (l.getData() >= 1 && l.getData() <= 6);
		}
	}
}
