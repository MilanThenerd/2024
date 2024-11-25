import java.util.concurrent.atomic.AtomicBoolean;

public class TTASLock 
{
    private AtomicBoolean locked = new AtomicBoolean(false);

    public void lock() 
    {
        while (true) 
        {
            while (locked.get()) 
            {
                //Fidget Spinner
            }
            if (!locked.getAndSet(true)) 
            {
                break;
            }
        }
    }

    public void unlock() 
    {
        locked.set(false);
    }
}
