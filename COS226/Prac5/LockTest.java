import java.util.concurrent.*;
import java.util.concurrent.atomic.AtomicInteger;

public class LockTest 
{
    static AtomicInteger sharedCounter = new AtomicInteger(0);
    static final int NUM_ITERATIONS = 100000;
    static final int FIB_ITERATIONS = 1000;
    static final int FIB_NUMBER = 15;

    public static long fibonacci(int n) 
    {
        if (n <= 1) return n;
        return fibonacci(n - 1) + fibonacci(n - 2);
    }

    // TAS Lock Test
    public static void tasTestIncrement(TASLock lock) 
    {
        for (int i = 0; i < NUM_ITERATIONS; i++) 
        {
            lock.lock();
            sharedCounter.incrementAndGet();
            lock.unlock();
        }
    }

    // TTAS Lock Test
    public static void ttasTestIncrement(TTASLock lock) 
    {
        for (int i = 0; i < NUM_ITERATIONS; i++) 
        {
            lock.lock();
            sharedCounter.incrementAndGet();
            lock.unlock();
        }
    }

    // Backoff Lock Test
    public static void backoffTestIncrement(BackoffLock lock) 
    {
        for (int i = 0; i < NUM_ITERATIONS; i++) 
        {
            lock.lock();
            sharedCounter.incrementAndGet();
            lock.unlock();
        }
    }

    // TAS Lock Test - Fibonacci
    public static void tasTestFibonacci(TASLock lock) 
    {
        for (int i = 0; i < FIB_ITERATIONS; i++) 
        {
            lock.lock();
            long fib = fibonacci(FIB_NUMBER);
            lock.unlock();
        }
    }

    // TTAS Lock Test - Fibonacci
    public static void ttasTestFibonacci(TTASLock lock) 
    {
        for (int i = 0; i < FIB_ITERATIONS; i++) 
        {
            lock.lock();
            long fib = fibonacci(FIB_NUMBER);
            lock.unlock();
        }
    }

    // Backoff Lock Test - Fibonacci
    public static void backoffTestFibonacci(BackoffLock lock) 
    {
        for (int i = 0; i < FIB_ITERATIONS; i++) 
        {
            lock.lock();
            long fib = fibonacci(FIB_NUMBER);
            lock.unlock();
        }
    }

    public static long runTest(Runnable lockTest, int numThreads) throws InterruptedException 
    {
        ExecutorService executor = Executors.newFixedThreadPool(numThreads);
        long startTime = System.currentTimeMillis();

        for (int i = 0; i < numThreads; i++) 
        {
            executor.submit(lockTest);
        }

        executor.shutdown();
        executor.awaitTermination(1, TimeUnit.HOURS);

        long endTime = System.currentTimeMillis();
        return endTime - startTime;
    }

    public static void main(String[] args) throws InterruptedException 
    {
        for (int numThreads = 1; numThreads <= 15; numThreads++) 
        {
            long tasTotalTimeInc = 0;
            long ttasTotalTimeInc = 0;
            long backoffTotalTimeInc = 0;
            long tasTotalTimeFib = 0;
            long ttasTotalTimeFib = 0;
            long backoffTotalTimeFib = 0;

            int sampleSize = 100;

            for (int i = 0; i < sampleSize; i++) 
            {
                TASLock tasLock = new TASLock();
                TTASLock ttasLock = new TTASLock();
                BackoffLock backoffLock = new BackoffLock();

                // Incrementing Tests
                tasTotalTimeInc += runTest(() -> tasTestIncrement(tasLock), numThreads);
                ttasTotalTimeInc += runTest(() -> ttasTestIncrement(ttasLock), numThreads);
                backoffTotalTimeInc += runTest(() -> backoffTestIncrement(backoffLock), numThreads);

                // Fibonacci Tests
                tasTotalTimeFib += runTest(() -> tasTestFibonacci(tasLock), numThreads);
                ttasTotalTimeFib += runTest(() -> ttasTestFibonacci(ttasLock), numThreads);
                backoffTotalTimeFib += runTest(() -> backoffTestFibonacci(backoffLock), numThreads);
            }

            // Calculate and print average times for Increment tests
            System.out.printf("Average time for TAS Increment lock with %d threads: %.2f ms%n", numThreads, tasTotalTimeInc / (double)sampleSize);
            System.out.printf("Average time for TTAS Increment lock with %d threads: %.2f ms%n", numThreads, ttasTotalTimeInc / (double)sampleSize);
            System.out.printf("Average time for Backoff Increment lock with %d threads: %.2f ms%n", numThreads, backoffTotalTimeInc / (double)sampleSize);

            // Calculate and print average times for Fibonacci tests
            System.out.printf("Average time for TAS Fibonacci lock with %d threads: %.2f ms%n", numThreads, tasTotalTimeFib / (double)sampleSize);
            System.out.printf("Average time for TTAS Fibonacci lock with %d threads: %.2f ms%n", numThreads, ttasTotalTimeFib / (double)sampleSize);
            System.out.printf("Average time for Backoff Fibonacci lock with %d threads: %.2f ms%n", numThreads, backoffTotalTimeFib / (double)sampleSize);
        }
    }
}
