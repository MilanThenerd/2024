import java.util.concurrent.atomic.AtomicReference;

public class LockFreeStack<T> {
    private static class Node<T> {
        T value;
        Node<T> next;
        
        Node(T value) {
            this.value = value;
        }
    }

    private AtomicReference<Node<T>> head = new AtomicReference<>();

    public void push(T item) {
        Node<T> newNode = new Node<>(item);
        while (true) {
            Node<T> currentHead = head.get();
            newNode.next = currentHead;
            if (head.compareAndSet(currentHead, newNode)) {
                break;
            }
        }
    }

    public T pop() {
        while (true) {
            Node<T> currentHead = head.get();
            if (currentHead == null) {
                return null;
            }
            Node<T> newHead = currentHead.next;
            if (head.compareAndSet(currentHead, newHead)) {
                return currentHead.value;
            }
        }
    }
}
