import java.util.concurrent.atomic.AtomicReference;
import java.util.concurrent.ThreadLocalRandom;
import java.util.concurrent.TimeUnit;

public class EliminationBackoffStack<T> {
    private static class Node<T> {
        T value;
        Node<T> next;

        Node(T value) {
            this.value = value;
        }
    }

    private AtomicReference<Node<T>> head = new AtomicReference<>();
    private EliminationArray<T> eliminationArray = new EliminationArray<>(10);

    public void push(T item) {
        Node<T> newNode = new Node<>(item);
        while (true) {
            Node<T> currentHead = head.get();
            newNode.next = currentHead;
            if (head.compareAndSet(currentHead, newNode)) {
                return;
            } else {
                try {
                    T otherItem = eliminationArray.visit(item, 5, TimeUnit.MILLISECONDS);
                    if (otherItem == null) {
                        return;
                    }
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                }
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
            } else {
                try {
                    T otherItem = eliminationArray.visit(null, 5, TimeUnit.MILLISECONDS);
                    if (otherItem != null) {
                        return otherItem;
                    }
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                }
            }
        }
    }

    private static class EliminationArray<T> {
        private AtomicReference<T>[] slots;

        @SuppressWarnings("unchecked")
        public EliminationArray(int capacity) {
            slots = (AtomicReference<T>[]) new AtomicReference[capacity];
            for (int i = 0; i < capacity; i++) {
                slots[i] = new AtomicReference<>(null);
            }
        }

        public T visit(T value, long timeout, TimeUnit unit) throws InterruptedException {
            int slot = ThreadLocalRandom.current().nextInt(slots.length);
            AtomicReference<T> selectedSlot = slots[slot];

            if (value == null) {
                return selectedSlot.getAndSet(null);
            } else {
                if (selectedSlot.compareAndSet(null, value)) {
                    unit.sleep(timeout);
                    if (selectedSlot.compareAndSet(value, null)) {
                        return null;
                    } else {
                        return selectedSlot.getAndSet(null);
                    }
                }
            }
            return null;
        }
    }
}
