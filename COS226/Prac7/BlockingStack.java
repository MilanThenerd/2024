import java.util.Stack;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class BlockingStack<T> {
    private Stack<T> stack;
    private Lock lock;

    public BlockingStack() {
        this.stack = new Stack<>();
        this.lock = new ReentrantLock();
    }

    public void push(T item) {
        lock.lock();
        try {
            stack.push(item);
        } finally {
            lock.unlock();
        }
    }

    public T pop() {
        lock.lock();
        try {
            if (!stack.isEmpty()) {
                T item = stack.pop();
                return item;
            } else {
                return null;
            }
        } finally {
            lock.unlock();
        }
    }
}
