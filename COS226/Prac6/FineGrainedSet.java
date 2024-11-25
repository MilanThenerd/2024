import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;

public class FineGrainedSet implements Set<Integer> {
    private final Set<Integer> set;
    private final Map<Integer, Object> lockMap;

    public FineGrainedSet() {
        this.set = new HashSet<>();
        this.lockMap = new HashMap<>();
    }

    private Object getLock(int item) {
        return lockMap.computeIfAbsent(item, k -> new Object());
    }

    @Override
    public boolean add(Integer item) {
        synchronized (getLock(item)) {
            return set.add(item);
        }
    }

    @Override
    public boolean contains(Object item) {
        synchronized (getLock((Integer) item)) {
            return set.contains(item);
        }
    }

    @Override
    public boolean remove(Object item) {
        synchronized (getLock((Integer) item)) {
            return set.remove(item);
        }
    }

    @Override
    public void clear() {
        synchronized (this) {
            set.clear();
            lockMap.clear();
        }
    }

    @Override
    public int size() {
        synchronized (this) {
            return set.size();
        }
    }

    @Override
    public boolean isEmpty() {
        synchronized (this) {
            return set.isEmpty();
        }
    }

    @Override
    public Iterator<Integer> iterator() {
        synchronized (this) {
            return set.iterator();
        }
    }

    @Override
    public Object[] toArray() {
        synchronized (this) {
            return set.toArray();
        }
    }

    @Override
    public <T> T[] toArray(T[] a) {
        synchronized (this) {
            return set.toArray(a);
        }
    }

    @Override
    public boolean containsAll(java.util.Collection<?> c) {
        synchronized (this) {
            return set.containsAll(c);
        }
    }

    @Override
    public boolean addAll(java.util.Collection<? extends Integer> c) {
        synchronized (this) {
            return set.addAll(c);
        }
    }

    @Override
    public boolean retainAll(java.util.Collection<?> c) {
        synchronized (this) {
            return set.retainAll(c);
        }
    }

    @Override
    public boolean removeAll(java.util.Collection<?> c) {
        synchronized (this) {
            return set.removeAll(c);
        }
    }
}
