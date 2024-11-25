import java.util.HashSet;
import java.util.Iterator;
import java.util.Set;

public class CoarseGrainedSet implements Set<Integer> {
    private final Set<Integer> set;
    private final Object lock;

    public CoarseGrainedSet() {
        this.set = new HashSet<>();
        this.lock = new Object();
    }

    @Override
    public boolean add(Integer item) {
        synchronized (lock) {
            return set.add(item);
        }
    }

    @Override
    public boolean contains(Object item) {
        synchronized (lock) {
            return set.contains(item);
        }
    }

    @Override
    public boolean remove(Object item) {
        synchronized (lock) {
            return set.remove(item);
        }
    }

    @Override
    public void clear() {
        synchronized (lock) {
            set.clear();
        }
    }

    @Override
    public int size() {
        synchronized (lock) {
            return set.size();
        }
    }

    @Override
    public boolean isEmpty() {
        synchronized (lock) {
            return set.isEmpty();
        }
    }

    @Override
    public Iterator<Integer> iterator() {
        synchronized (lock) {
            return set.iterator(); 
        }
    }

    @Override
    public Object[] toArray() {
        synchronized (lock) {
            return set.toArray();
        }
    }

    @Override
    public <T> T[] toArray(T[] a) {
        synchronized (lock) {
            return set.toArray(a);
        }
    }

    @Override
    public boolean containsAll(java.util.Collection<?> c) {
        synchronized (lock) {
            return set.containsAll(c);
        }
    }

    @Override
    public boolean addAll(java.util.Collection<? extends Integer> c) {
        synchronized (lock) {
            return set.addAll(c);
        }
    }

    @Override
    public boolean retainAll(java.util.Collection<?> c) {
        synchronized (lock) {
            return set.retainAll(c);
        }
    }

    @Override
    public boolean removeAll(java.util.Collection<?> c) {
        synchronized (lock) {
            return set.removeAll(c);
        }
    }
}
