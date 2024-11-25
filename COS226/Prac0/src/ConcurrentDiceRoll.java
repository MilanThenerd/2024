import java.util.concurrent.CountDownLatch;

public class ConcurrentDiceRoll {
    private static int roll1;
    private static int roll2;

    public static void main(String[] args) {
        CountDownLatch latch = new CountDownLatch(2);

        Thread thread1 = new Thread(() -> {
            Die die1 = new Die();
            roll1 = die1.roll();
            latch.countDown();
        });

        Thread thread2 = new Thread(() -> {
            Die die2 = new Die();
            roll2 = die2.roll();
            latch.countDown();
        });

        thread1.start();
        thread2.start();

        try {
            latch.await();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        int sum = roll1 + roll2;

        System.out.println("Concurrent Roll:");
        System.out.println("Die 1: " + roll1);
        System.out.println("Die 2: " + roll2);
        System.out.println("Sum: " + sum);
    }
}
