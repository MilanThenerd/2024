import java.util.Set;

public class main 
{
  public static void highContentionTest(Set<Integer> set, int numThreads, int operationsPerThread) 
  {
      long totalTime = 0;
      int numTests = 1000;

      for (int test = 0; test < numTests; test++) 
      {
          long startTime = System.currentTimeMillis();

          Thread[] threads = new Thread[numThreads];
          for (int i = 0; i < numThreads; i++) 
          {
              final int threadId = i;
              threads[i] = new Thread(() -> {
                  for (int j = 0; j < operationsPerThread; j++) {
                      int value = threadId * operationsPerThread + j;
                      set.add(value);
                      set.remove(value);
                  }
              });
              threads[i].start();
          }

          for (Thread thread : threads) 
          {
              try 
              {
                  thread.join();
              } 
              catch (InterruptedException e) 
              {
                  Thread.currentThread().interrupt();
              }
          }

          long endTime = System.currentTimeMillis();
          totalTime += (endTime - startTime);
      }

      double averageTime = (double) totalTime / numTests;
      System.out.println("High Contention Test - Average Time taken: " + averageTime + " ms");
  }

  public static void readHeavyTest(Set<Integer> set, int numThreads, int operationsPerThread) 
  {
      long totalTime = 0;
      int numTests = 1000;

      for (int test = 0; test < numTests; test++) 
      {
          long startTime = System.currentTimeMillis();

          for (int i = 0; i < 1000; i++) {
              set.add(i);
          }

          Thread[] threads = new Thread[numThreads];
          for (int i = 0; i < numThreads; i++) 
          {
              final int threadId = i;
              threads[i] = new Thread(() -> {
                  for (int j = 0; j < operationsPerThread; j++) 
                  {
                      if (j % 10 == 0) 
                      {
                          set.add(threadId * operationsPerThread + j);
                      } 
                      else 
                      {
                          set.contains(j);
                      }
                  }
              });
              threads[i].start();
          }

          for (Thread thread : threads) 
          {
              try 
              {
                  thread.join();
              } 
              catch (InterruptedException e) 
              {
                  Thread.currentThread().interrupt();
              }
          }

          long endTime = System.currentTimeMillis();
          totalTime += (endTime - startTime);
      }

      double averageTime = (double) totalTime / numTests;
      System.out.println("Read-Heavy Test - Average Time taken: " + averageTime + " ms");
  }

  public static void mixedWorkloadTest(Set<Integer> set, int numThreads, int operationsPerThread) 
  {
      long totalTime = 0;
      int numTests = 1000;

      for (int test = 0; test < numTests; test++) 
      {
          long startTime = System.currentTimeMillis();

          Thread[] threads = new Thread[numThreads];
          for (int i = 0; i < numThreads; i++) 
          {
              final int threadId = i;
              threads[i] = new Thread(() -> {
                  for (int j = 0; j < operationsPerThread; j++) 
                  {
                      if (j % 2 == 0) 
                      {
                          set.add(threadId * operationsPerThread + j);  // Write operation (50% of the time)
                      } 
                      else 
                      {
                          set.contains(j);  // Read operation (50% of the time)
                      }
                  }
              });
              threads[i].start();
          }

          for (Thread thread : threads) 
          {
              try 
              {
                  thread.join();
              } 
              catch (InterruptedException e) 
              {
                  Thread.currentThread().interrupt();
              }
          }

          long endTime = System.currentTimeMillis();
          totalTime += (endTime - startTime);
      }

      double averageTime = (double) totalTime / numTests;
      System.out.println("Mixed Workload Test - Average Time taken: " + averageTime + " ms");
  }

  public static void main(String[] args) 
  {
    int numThreads = 1;
    int operationsPerThread = 10000;

    for(int i = 1 ; i <= 20 ; i++)
    {
      System.out.println("\nNumber of threads: "+i);
      // System.out.println("=== High Contention Test ===");
      Set<Integer> coarseGrainedSet = new CoarseGrainedSet();
      // highContentionTest(coarseGrainedSet, i, operationsPerThread);
  
      Set<Integer> fineGrainedSet = new FineGrainedSet();
      // highContentionTest(fineGrainedSet, i, operationsPerThread);
  
      Set<Integer> optimisticSet = new OptimisticSet();
      // highContentionTest(optimisticSet, i, operationsPerThread);
  
      // System.out.println("\n=== Read Heavy Test ===");
      // readHeavyTest(coarseGrainedSet, i, operationsPerThread);
      // readHeavyTest(fineGrainedSet, i, operationsPerThread);
      // readHeavyTest(optimisticSet, i, operationsPerThread);
  
      System.out.println("\n=== Mixed Workload Test ===");
      mixedWorkloadTest(coarseGrainedSet, i, operationsPerThread);
      mixedWorkloadTest(fineGrainedSet, i, operationsPerThread);
      mixedWorkloadTest(optimisticSet,i, operationsPerThread);
    }
  }
}
