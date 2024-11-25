public class SequentialDiceRoll {
  public static void main(String[] args) {
      Die die1 = new Die();
      Die die2 = new Die();

      int roll1 = die1.roll();
      int roll2 = die2.roll();

      int sum = roll1 + roll2;

      System.out.println("Sequential Roll:");
      System.out.println("Die 1: " + roll1);
      System.out.println("Die 2: " + roll2);
      System.out.println("Sum: " + sum);
  }
}
