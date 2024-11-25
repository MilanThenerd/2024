import java.util.LinkedList;
import java.util.Queue;

public class Main {
    public static void main(String[] args) {
        Output output = new Output();
        Queue<Paper> allPapers = new LinkedList<>();
        Threeterson lock = new Threeterson(output);

        for (int i = 0; i < 10; i++) {
            allPapers.add(new Paper());
        }

        int numMarkers = 3;
        Marker[] markers = new Marker[numMarkers];
        for (int i = 0; i < numMarkers; i++) {
            markers[i] = new Marker(lock, output, allPapers);
            markers[i].start();
        }

        for (Marker marker : markers) {
            try {
                marker.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        System.out.println(output.toString());
    }
}
