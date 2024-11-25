import java.util.concurrent.atomic.AtomicBoolean;

public class TASLock 
{
    private AtomicBoolean locked = new AtomicBoolean(false);

    public void lock() 
    {
        while (locked.getAndSet(true)) 
        {
            //Spin
        }
    }

    public void unlock() 
    {
        locked.set(false);
    }
}
