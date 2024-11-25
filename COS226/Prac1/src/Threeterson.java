
import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Threeterson implements Lock {
    private final ReentrantLock printLock;
    private final Output output;
    private final int[] level;
    private final int[] victim;
    private final int numThreads = 3;
    private volatile boolean lockHeld = false;

    public Threeterson(Output output) {
      this.printLock = new ReentrantLock();
      this.output = output;
      this.victim = new int[numThreads];
      this.level = new int[numThreads];
  }

   

    @Override
    public void lock() {
      int index = Integer.parseInt(Thread.currentThread().getName().split("-")[1]) % 3;
      for(int i = 1 ; i < numThreads ; i++)
      {
        level[index] = i;
        victim[i] = index;
        log(Thread.currentThread().getName() + " at L" + i);
        log(Thread.currentThread().getName() + " is the victim of L" + i);
        boolean waiting;
        do {
          waiting = false;
          for (int k = 0; k < numThreads; k++) {
              if (k != index && level[k] >= i && victim[i] == index) {
                  waiting = true;
                  break;
              }
          }
          if (waiting) {
              Thread.yield();
          }
        } while (waiting);
      }
      log(Thread.currentThread().getName() + " has the lock");
      printLock.lock();
    }
    
    @Override
    public void unlock() {
      int index = Integer.parseInt(Thread.currentThread().getName().split("-")[1]) % numThreads;
      level[index] = 0;
      printLock.unlock();
      log(Thread.currentThread().getName() + " unlocked the lock");
    }

    private void log(String message) {
      printLock.lock();
      try {
          output.println(message);
      } finally {
          printLock.unlock();
      }
    }
    @Override
    public void lockInterruptibly() throws InterruptedException {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public boolean tryLock() {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public boolean tryLock(long time, TimeUnit unit) throws InterruptedException {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public Condition newCondition() {
        throw new UnsupportedOperationException("Not supported yet.");
    }

}
