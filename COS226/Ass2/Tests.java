import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Objects;

public class Tests 
{
  @Test
  @Order(1)
  public void testA() 
  {
      System.out.println("Running Test A");
      assert 1 + 1 == 2;
  }

  @Test
  @Order(3)
  public void testB() 
  {
      System.out.println("Running Test B");
      assert 2 * 2 == 5 : "Test B failed: 2 * 2 is not 5";
  }

  @Test(skip = true)
  @Order(2)
  public void testC() 
  {
      System.out.println("Running Test C");
  }

  @Test
  @Order(4)
  public void testD() 
  {
      System.out.println("Running Test D");
      assert "hello".equals("hello");
  }

  @Test
  @Order(5)
  public void testE() 
  {
      System.out.println("Running Test E");
      assert Math.pow(2, 3) == 8;
  }

   @Test
   @Order(6)
   public void testF() 
   {
      System.out.println("Running Test F");
      int[] numbers = {5, 2, 9, 1, 5, 6};
      Arrays.sort(numbers);
      int[] expected = {1, 2, 5, 5, 6, 9};
      assert Arrays.equals(numbers, expected) : "Test F failed: Array was not sorted correctly";
    }

    @Test
    @Order(7)
    public void testG() 
    {
        System.out.println("Running Test G");
        try 
        {
            int result = 10 / 0;
            assert false : "Test G failed: Exception was not thrown";
        } 
        catch (ArithmeticException e) 
        {
            assert true;
        }
    }

        @Test
    @Order(8)
    public void testH() 
    {
        System.out.println("Running Test H");
        // Test a more complex calculation
        double result = Math.sqrt(16) * Math.pow(2, 4) - 5 + Math.sin(Math.PI / 2);
        double expected = 16.0;
        assert Math.abs(result - expected) < 0.0001 : "Test H failed: Complex calculation result incorrect";
    }

    @Test
    @Order(9)
    public void testI() 
    {
        System.out.println("Running Test I");
        // Validate a collection operation
        List<String> names = new ArrayList<>();
        names.add("Alice");
        names.add("Bob");
        names.add("Charlie");
        assert names.size() == 3 : "Test I failed: Incorrect number of elements in the list";
        assert names.contains("Alice") : "Test I failed: List does not contain 'Alice'";
    }

    @Test
    @Order(10)
    public void testJ() 
    {
        System.out.println("Running Test J");
        Person person1 = new Person("John", 30);
        Person person2 = new Person("John", 30);
        assert person1.equals(person2) : "Test J failed: Person objects are not equal";
    }

    static class Person 
    {
        private String name;
        private int age;

        public Person(String name, int age) 
        {
            this.name = name;
            this.age = age;
        }

        @Override
        public boolean equals(Object obj) 
        {
            if (this == obj) return true;
            if (obj == null || getClass() != obj.getClass()) return false;
            Person person = (Person) obj;
            return age == person.age && name.equals(person.name);
        }

        @Override
        public int hashCode() 
        {
            return Objects.hash(name, age);
        }
    }


    @Test
    @Order(11)
    public void testLongComputation1() 
    {
        System.out.println("Running Long Computation Test 1");
        // Simulate a heavy computation (e.g., calculating a large prime number)
        long prime = findNthPrime(100000);
        assert prime > 0 : "Test LongComputation1 failed: Unable to calculate prime.";
    }

    @Test
    @Order(12)
    public void testLongComputation2() 
    {
        System.out.println("Running Long Computation Test 2");
        // Another heavy computation (e.g., calculating Fibonacci series)
        long fib = fibonacci(45);
        assert fib == 1134903170L : "Test LongComputation2 failed: Incorrect Fibonacci calculation.";
    }

    @Test
    @Order(14)
    public void testLongComputation3() 
    {
        System.out.println("Running Long Computation Test 3");
        // Perform another time-consuming task (matrix multiplication)
        int[][] result = matrixMultiplication(500, 500);
        assert result != null : "Test LongComputation3 failed: Matrix multiplication error.";
    }

    @Test
    @Order(15)
    public void testLongComputation4() 
    {
        System.out.println("Running Long Computation Test 4");
        long prime = findNthPrime(200000);
        assert prime > 0 : "Test LongComputation4 failed: Unable to calculate prime.";
    }

    @Test
    @Order(16)
    public void testLongComputation5() 
    {
        System.out.println("Running Long Computation Test 5");
        int[][] result = matrixMultiplication(1000, 1000);
        assert result != null : "Test LongComputation5 failed: Matrix multiplication error.";
    }

    @Test
    @Order(16)
    public void testLongComputation6() 
    {
        System.out.println("Running Long Computation Test 6");
        long fib = fibonacci(60);
        assert fib == 1548008755920L : "Test LongComputation6 failed: Incorrect Fibonacci calculation.";
    }

    @Test
    @Order(17)
    public void testLongComputation7() 
    {
        System.out.println("Running Long Computation Test 7");
        long fib = fibonacci(69);
        assert fib == 117669030460994L : "Test LongComputation7 failed: Incorrect Fibonacci calculation.";
    }

    // Utility function to find the nth prime number (time-consuming task)
    private long findNthPrime(int n) 
    {
        int count = 0;
        long num = 1;
        while (count < n) 
        {
            num++;
            if (isPrime(num)) 
            {
                count++;
            }
        }
        return num;
    }

    private boolean isPrime(long num) 
    {
        if (num < 2) return false;
        for (long i = 2; i <= Math.sqrt(num); i++) 
        {
            if (num % i == 0) return false;
        }
        return true;
    }

    // Utility function to calculate Fibonacci (another heavy task)
    private long fibonacci(int n) 
    {
        if (n <= 1) return n;
        long a = 0, b = 1, c = 0;
        for (int i = 2; i <= n; i++) 
        {
            c = a + b;
            a = b;
            b = c;
        }
        return c;
    }

    // Simulate matrix multiplication (time-consuming computation)
    private int[][] matrixMultiplication(int size, int size2) 
    {
        int[][] matrixA = new int[size][size2];
        int[][] matrixB = new int[size2][size];
        int[][] result = new int[size][size];

        // Initialize matrices with some values
        for (int i = 0; i < size; i++) 
        {
            for (int j = 0; j < size2; j++) 
            {
                matrixA[i][j] = i + j;
                matrixB[j][i] = i - j;
            }
        }

        // Perform multiplication
        for (int i = 0; i < size; i++) 
        {
            for (int j = 0; j < size; j++) 
            {
                for (int k = 0; k < size2; k++) 
                {
                    result[i][j] += matrixA[i][k] * matrixB[k][j];
                }
            }
        }
        return result;
    }
    @Test
    @Order(18)
    public void testStringManipulation() 
    {
        System.out.println("Running Test String Manipulation");
        String str = "  Hello World!  ";
        String trimmed = str.trim().toLowerCase().replace(" ", "_");
        assert "hello_world!".equals(trimmed) : "Test String Manipulation failed: String was not manipulated correctly.";
    }

    @Test
    @Order(19)
    public void testLargeListSorting() 
    {
        System.out.println("Running Test Large List Sorting");
        List<Integer> numbers = new ArrayList<>();
        for (int i = 1000; i >= 1; i--) 
        {
            numbers.add(i);
        }
        numbers.sort(Integer::compareTo);
        assert numbers.get(0) == 1 && numbers.get(numbers.size() - 1) == 1000 : "Test Large List Sorting failed: List was not sorted correctly.";
    }

    @Test
    @Order(20)
    public void testExceptionHandling() 
    {
        System.out.println("Running Test Exception Handling");
        try 
        {
            String value = null;
            value.length();
            assert false : "Test Exception Handling failed: NullPointerException was not thrown.";
        } 
        catch (NullPointerException e) 
        {
            assert true;
        }
    }
}
