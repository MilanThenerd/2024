import java.util.*;

public class Main {

    public static void main(String[] args) {
        List<MethodCall> operations = Arrays.asList(
                new MethodCall("A", 1, "enq(x)"),
                new MethodCall("A", 1, "enq(x)"),
                new MethodCall("A", 2, "enq(y)"),
                new MethodCall("B", 1, "deq(x)"),
                new MethodCall("B", 2, "deq(y)")
        );

        List<List<MethodCall>> possibleOrders = ExecutionOrderChecker.findPossibleOrders(operations);

        
        for (List<MethodCall> order : possibleOrders) {
            System.out.println(order);
        }
        /*
         * Should print:
         * [(A,1,enq(x)), (B,1,deq(x)), (A,2,enq(y)), (B,2,deq(y))]
         * [(A,1,enq(x)), (A,2,enq(y)), (B,1,deq(x)), (B,2,deq(y))]
         */

        //  System.out.println("test");
        //  List<MethodCall> operations1 = Arrays.asList(
        //           new MethodCall("A", 1, "enq(x)"),
        //           new MethodCall("A", 1, "enq(x)"),
        //           new MethodCall("A", 2, "deq(x)"),
        //           new MethodCall("A", 3, "enq(z)"),
        //           new MethodCall("A", 4, "enq(y)"),
        //           new MethodCall("B", 1, "enq(x)"),
        //           new MethodCall("B", 1, "enq(x)"),
        //           new MethodCall("B", 2, "deq(x)"),
        //           new MethodCall("B", 3, "deq(z))"),
        //           new MethodCall("B", 4, "deq(y)")
        //   );

        //   List<List<MethodCall>> possibleOrders1 = ExecutionOrderChecker.findPossibleOrders(operations1);

          
        //   for (List<MethodCall> order : possibleOrders1) {
        //       System.out.println(order);
        //   }
    }
}
