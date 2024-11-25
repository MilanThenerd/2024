import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.Arrays;
import java.util.Comparator;
import java.util.List;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.stream.Collectors;

public class TestRunner 
{
    private final ThreadPool threadPool;
    private final AtomicInteger totalTests = new AtomicInteger(0);
    private final AtomicInteger testsPassed = new AtomicInteger(0);
    private final AtomicInteger testsFailed = new AtomicInteger(0);
    private final AtomicInteger testsSkipped = new AtomicInteger(0);

    public TestRunner(int noOfThreads) 
    {
        threadPool = new ThreadPool(noOfThreads);
    }

    public void runTests(Class<?> testClass) 
    {

        Method[] methods = testClass.getDeclaredMethods();
        List<Method> testMethods = Arrays.stream(methods)
                .filter(m -> m.isAnnotationPresent(Test.class))
                .sorted(Comparator.comparingInt(m -> m.getAnnotation(Order.class).value()))
                .collect(Collectors.toList());

        totalTests.set(testMethods.size());
        CountDownLatch latch = new CountDownLatch(totalTests.get());

        for (Method method : testMethods) 
        {
            threadPool.submit(() -> {
                try 
                {
                    executeTest(method);
                } 
                finally 
                {
                    latch.countDown();
                }
            });
        }
        try 
        {
            latch.await();
        } 
        catch (InterruptedException e) 
        {
            Thread.currentThread().interrupt();
        }

        threadPool.stop();


        System.out.println("Total Tests: " + totalTests);
        System.out.println("Passed: " + testsPassed);
        System.out.println("Failed: " + testsFailed);
        System.out.println("Skipped: " + testsSkipped);
    }

    private void executeTest(Method method) 
    {
        Test testAnnotation = method.getAnnotation(Test.class);
        if (testAnnotation.skip()) 
        {
            testsSkipped.incrementAndGet();
            return;
        }
        try 
        {
            Object instance = method.getDeclaringClass().getDeclaredConstructor().newInstance();
            method.invoke(instance);
            testsPassed.incrementAndGet();
        } 
        catch (InvocationTargetException e) 
        {
            Throwable cause = e.getCause();
            if (cause instanceof AssertionError) 
            {
                testsFailed.incrementAndGet();
            } 
            else 
            {
                e.printStackTrace();
                testsFailed.incrementAndGet();
            }
        } 
        catch (Exception e) 
        {
            e.printStackTrace();
            testsFailed.incrementAndGet();
        }
    }
}
