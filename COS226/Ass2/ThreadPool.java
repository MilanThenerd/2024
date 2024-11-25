import java.util.Queue;
import java.util.concurrent.ConcurrentLinkedQueue;
import java.util.List;
import java.util.ArrayList;

public class ThreadPool 
{
    private final Queue<Runnable> taskQueue;
    private final List<WorkerThread> threads;
    private boolean isStopped = false;

    public ThreadPool(int noOfThreads) 
    {
        taskQueue = new ConcurrentLinkedQueue<>();
        threads = new ArrayList<>(noOfThreads);

        for (int i = 0; i < noOfThreads; i++) 
        {
            threads.add(new WorkerThread(taskQueue));
        }

        for (WorkerThread thread : threads) 
        {
            thread.start();
        }
    }

    public synchronized void submit(Runnable task) 
    {
        if (isStopped) throw new IllegalStateException("ThreadPool is stopped");
        taskQueue.add(task);
        notifyAll();
    }

    public void stop() 
    {
        isStopped = true;
        for (WorkerThread thread : threads) 
        {
            thread.stopThread();
        }
    }
}

class WorkerThread extends Thread 
{
    private final Queue<Runnable> taskQueue;

    public WorkerThread(Queue<Runnable> queue) 
    {
        taskQueue = queue;
    }

    @Override
    public void run() 
    {
        while (!isInterrupted()) 
        {
            Runnable task = taskQueue.poll();
            if (task != null) 
            {
                try 
                {
                    task.run();
                } 
                catch (Exception e) 
                {
                    // Handle task exceptions
                }
            }
        }
    }

    public void stopThread() 
    {
        interrupt();
    }
}
