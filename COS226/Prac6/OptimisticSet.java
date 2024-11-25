import java.util.HashSet;
import java.util.Iterator;
import java.util.Set;
import java.util.concurrent.locks.ReentrantLock;

public class OptimisticSet implements Set<Integer> {
    private final Set<Integer> set;
    private final ReentrantLock lock;

    public OptimisticSet() {
        this.set = new HashSet<>();
        this.lock = new ReentrantLock();
    }

    @Override
    public boolean add(Integer item) {
        while (true) {
            if (set.contains(item)) {
                return false;
            }
            lock.lock();
            try {
                if (!set.contains(item)) {
                    return set.add(item);
                }
            } finally {
                lock.unlock();
            }
        }
    }

    @Override
    public boolean contains(Object item) {
        return set.contains(item);
    }

    @Override
    public boolean remove(Object item) {
        while (true) {
            if (!set.contains(item)) {
                return false; 
            }
            lock.lock();
            try {
                if (set.contains(item)) {
                    return set.remove(item);
                }
            } finally {
                lock.unlock();
            }
        }
    }

    @Override
    public void clear() {
        lock.lock();
        try {
            set.clear();
        } finally {
            lock.unlock();
        }
    }

    @Override
    public int size() {
        return set.size();
    }

    @Override
    public boolean isEmpty() {
        return set.isEmpty();
    }

    @Override
    public Iterator<Integer> iterator() {
        lock.lock();
        try {
            return new HashSet<>(set).iterator();
        } finally {
            lock.unlock();
        }
    }

    @Override
    public Object[] toArray() {
        lock.lock();
        try {
            return set.toArray();
        } finally {
            lock.unlock();
        }
    }

    @Override
    public <T> T[] toArray(T[] a) {
        lock.lock();
        try {
            return set.toArray(a);
        } finally {
            lock.unlock();
        }
    }

    @Override
    public boolean containsAll(java.util.Collection<?> c) {
        return set.containsAll(c);
    }

    @Override
    public boolean addAll(java.util.Collection<? extends Integer> c) {
        boolean modified = false;
        for (Integer item : c) {
            if (add(item)) {
                modified = true;
            }
        }
        return modified;
    }

    @Override
    public boolean retainAll(java.util.Collection<?> c) {
        lock.lock();
        try {
            return set.retainAll(c);
        } finally {
            lock.unlock();
        }
    }

    @Override
    public boolean removeAll(java.util.Collection<?> c) 
    {
        boolean modified = false;
        for (Object item : c) {
            if (remove(item)) {
                modified = true;
            }
        }
        return modified;
    }
}
