

public class Main {
    public static void main(String[] args) throws Exception 
    {
      BoundedTimestamp ts1 = new BoundedTimestamp(new int[]{0,1});
      BoundedTimestamp ts2 = new BoundedTimestamp(new int[]{1,0});
      BoundedTimestamp ts3 = new BoundedTimestamp(new int[]{2,2,1});
      BoundedTimestamp ts4 = new BoundedTimestamp(new int[]{2,0,2});
      BoundedTimestamp ts5 = new BoundedTimestamp(new int[]{1,0,0});
      
      System.out.println("Comparing ts1 with ts2: " + ts1.compare(ts2));
      System.out.println("Comparing ts2 with ts1: " + ts2.compare(ts1));
      System.out.println("Comparing ts3 with ts4: " + ts3.compare(ts4));
      System.out.println("Comparing ts3 with ts5: " + ts3.compare(ts5));
      System.out.println("Comparing ts3 with ts3: " + ts3.compare(ts3));

      BoundedTimestamp[] timestamps = { new BoundedTimestamp(new int[]{2,0}), new BoundedTimestamp(new int[]{1,1}), new BoundedTimestamp(new int[]{2,1}) };
      
      BoundedTimestamp nextTimestamp = BoundedTimestamp.getNext(timestamps, 0);
      System.out.println("" + timestamps[0] + timestamps[1] + timestamps[2]);
      System.out.println("Next smallest legal timestamp for thread 0: " + nextTimestamp);

      BoundedTimestamp[] timestamps2 = { new BoundedTimestamp(new int[]{0,0}), new BoundedTimestamp(new int[]{0,0}), new BoundedTimestamp(new int[]{0,0}) };
      
      BoundedTimestamp nextTimestamp2 = BoundedTimestamp.getNext(timestamps2, 1);
      System.out.println("" + timestamps2[0] + timestamps2[1] + timestamps2[2]);
      System.out.println("Next smallest legal timestamp for thread 1: " + nextTimestamp2);

      BoundedTimestamp[] timestamps3 = { new BoundedTimestamp(new int[]{0,0}), new BoundedTimestamp(new int[]{0,1}), new BoundedTimestamp(new int[]{0,0}) };
      
      BoundedTimestamp nextTimestamp3 = BoundedTimestamp.getNext(timestamps3, 1);
      System.out.println("" + timestamps3[0] + timestamps3[1] + timestamps3[2]);
      System.out.println("Next smallest legal timestamp for thread 1: " + nextTimestamp3);
    }

    // public static void testWithLock() throws InterruptedException {
    //     int threads = 4;
    //     Marker[] markers = new Marker[threads];
    //     Queue<Paper> allPapers = new LinkedList<>();
    //     System.out.println("###");
    //     for (int j = 0; j < 100; j++) {

    //         BackeryLock lock = new BackeryLock(threads);
    //         for (int i = 0; i < 50; i++) {
    //             allPapers.add(new Paper());
    //         }
    //         for (int i = 0; i < markers.length; i++) {
    //             markers[i] = new Marker(lock, allPapers);
    //         }
    //         for (int i = 0; i < markers.length; i++) {
    //             markers[i].start();
    //         }
    //         for (int i = 0; i < markers.length; i++) {
    //             markers[i].join();
    //         }
    //         System.out.println("Output " + j);
    //     }
    //}
  
}
