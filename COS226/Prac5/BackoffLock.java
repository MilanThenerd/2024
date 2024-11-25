import java.util.concurrent.atomic.AtomicBoolean;

public class BackoffLock 
{
    private AtomicBoolean locked = new AtomicBoolean(false);
    private final int MAX_BACKOFF = 1024;

    public void lock() 
    {
        int backoff = 1;
        while (true) 
        {
            while (locked.get()) 
            {
                // Rethink life choices D:
            }
            if (!locked.getAndSet(true)) 
            {
                break;
            }
            try 
            {
                Thread.sleep(backoff);
                backoff = Math.min(backoff * 2, MAX_BACKOFF);
            } 
            catch (InterruptedException e) 
            {
                e.printStackTrace();
            }
        }
    }

    public void unlock() 
    {
        locked.set(false);
    }
}
