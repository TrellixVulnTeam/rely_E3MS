
public class BSTToSortedDoublyList {
	  // @include
	  // Transform a BST into a circular sorted doubly linked list in-place,
	  // return the head of the list.
	  public static BinaryTree<Integer> bstToDoublyLinkedList(
	      BinaryTree<Integer> T) {
		  
		  if(T==null){
			  return T;
		  }
		  
		  BinaryTree<Integer> leftList = bstToDoublyLinkedList(T.getLeft());
		  if(leftList==null){
			  leftList = T;
			  T.setLeft(T);
		  }else{
			  T.setLeft(leftList.getLeft());
			  leftList.getLeft().setRight(T);
		  }
		  
		  BinaryTree<Integer> rightList = bstToDoublyLinkedList(T.getRight());
		  if(rightList==null){
			  rightList = T;
			  T.setRight(T);
		  }else{
			  T.setRight(rightList);
		  }
		  
		  leftList.setLeft(rightList.getLeft());
		  rightList.getLeft().setRight(leftList);
		  if(rightList!=T)
			  rightList.setLeft(T);
		  
		  return leftList;
	  }
	  // @exclude

	  public static void main(String[] args) {
	    // 3
	    // 2 5
	    // 1 4 6
	    BinaryTree<Integer> root = new BinaryTree<>(3);
	    root.setLeft(new BinaryTree<>(2));
	    root.getLeft().setLeft(new BinaryTree<>(1));
	    root.setRight(new BinaryTree<>(5));
	    root.getRight().setLeft(new BinaryTree<>(4));
	    root.getRight().setRight(new BinaryTree<>(6));
	    BinaryTree<Integer> L = bstToDoublyLinkedList(root);
	    BinaryTree<Integer> curr = L;
	    int pre = Integer.MIN_VALUE;
	    do {
	      assert (pre <= curr.getData());
	      System.out.println(curr.getData());
	      pre = curr.getData();
	      curr = curr.getRight();
	    } while (curr != L);
	  }
}
