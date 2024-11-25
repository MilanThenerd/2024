public class Main 
{
  public static void main(String[] args) {
    long start, end;

    // Sequential Dice Roll
    start = System.nanoTime();
    SequentialDiceRoll.main(null);
    end = System.nanoTime();
    System.out.println("Sequential Execution Time: " + (end - start) / 1_000_000.0 + " ms");

    // Concurrent Dice Roll
    start = System.nanoTime();
    ConcurrentDiceRoll.main(null);
    end = System.nanoTime();
    System.out.println("Concurrent Execution Time: " + (end - start) / 1_000_000.0 + " ms");
  }
}
