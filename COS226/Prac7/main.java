import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.ThreadLocalRandom;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicInteger;

public class main {
    public static void main(String[] args) {
        int numOperations = 100000;

        System.out.println("Performance Test Started");

        for (int x = 1; x <= 20; x++) {
            int n = 400;
            int numThreads = x;
            System.out.println("Number of Threads: " + x);

            System.out.println("== Balanced (Push/Pop) Test ==");
            runTest(numThreads, numOperations, n, "Balanced");

            System.out.println("== 80% Push, 20% Pop Test ==");
            runTest(numThreads, numOperations, n, "SkewedPush");

            System.out.println("== 20% Push, 80% Pop Test ==");
            runTest(numThreads, numOperations, n, "SkewedPop");

        }
        System.out.println("Performance Test Completed");
    }

    private static void runTest(int numThreads, int numOperations, int n, String testType) {
        long totalTime;

        totalTime = executeTest(BlockingStack::new, numThreads, numOperations, n, testType);
        System.out.println("BlockingStack - Time taken: " + totalTime / n + " ms");

        totalTime = executeTest(LockFreeStack::new, numThreads, numOperations, n, testType);
        System.out.println("LockFreeStack - Time taken: " + totalTime / n + " ms");

        totalTime = executeTest(EliminationBackoffStack::new, numThreads, numOperations, n, testType);
        System.out.println("EliminationBackoffStack - Time taken: " + totalTime / n + " ms");
    }

    private static <T> long executeTest(StackSupplier<T> stackSupplier, int numThreads, int numOperations, int n, String testType) {
        long totalTime = 0;
        for (int i = 0; i < n; i++) {
            T stack = stackSupplier.get();
            long startTime = System.nanoTime();
            measurePerformance(stack, numThreads, numOperations, testType);
            long endTime = System.nanoTime();
            long duration = (endTime - startTime) / 1_000_000;
            totalTime += duration;
        }
        return totalTime;
    }

    private static void measurePerformance(Object stack, int numThreads, int numOperations, String testType) {
        ExecutorService executor = Executors.newFixedThreadPool(numThreads);

        for (int i = 0; i < numThreads; i++) {
            executor.execute(() -> {
                for (int j = 0; j < numOperations / numThreads; j++) {
                    if ("SkewedPush".equals(testType) && ThreadLocalRandom.current().nextInt(10) < 8) {
                        performOperation(stack, true);
                    } else if ("SkewedPop".equals(testType) && ThreadLocalRandom.current().nextInt(10) < 2) {
                        performOperation(stack, true);
                    } else {
                        performOperation(stack, ThreadLocalRandom.current().nextBoolean());
                    }
                }
            });
        }

        executor.shutdown();
        try {
            executor.awaitTermination(1, TimeUnit.MINUTES);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    private static void performOperation(Object stack, boolean isPush) {
        if (stack instanceof BlockingStack) {
            BlockingStack<Integer> s = (BlockingStack<Integer>) stack;
            if (isPush) {
                s.push(ThreadLocalRandom.current().nextInt());
            } else {
                s.pop();
            }
        } else if (stack instanceof LockFreeStack) {
            LockFreeStack<Integer> s = (LockFreeStack<Integer>) stack;
            if (isPush) {
                s.push(ThreadLocalRandom.current().nextInt());
            } else {
                s.pop();
            }
        } else if (stack instanceof EliminationBackoffStack) {
            EliminationBackoffStack<Integer> s = (EliminationBackoffStack<Integer>) stack;
            if (isPush) {
                s.push(ThreadLocalRandom.current().nextInt());
            } else {
                s.pop();
            }
        }
    }

    @FunctionalInterface
    private interface StackSupplier<T> {
        T get();
    }
}
