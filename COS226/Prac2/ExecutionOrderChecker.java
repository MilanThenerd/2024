import java.util.*;

public class ExecutionOrderChecker {
    public static List<List<MethodCall>> findPossibleOrders(List<MethodCall> operations) 
    {
        List<List<MethodCall>> result = new ArrayList<>();
        generatePerms(new ArrayList<>(), new HashMap<>(), operations, result);
        return result;
    }

    private static void generatePerms(List<MethodCall> current, Map<String, Integer> lastOperationIndex, List<MethodCall> remaining, List<List<MethodCall>> result) 
    {
        if (remaining.isEmpty()) 
        {
            result.add(new ArrayList<>(current));
            return;
        }

        for (int i = 0; i < remaining.size(); i++) 
        {
            MethodCall operation = remaining.get(i);
            if (lastOperationIndex.containsKey(operation.threadId)) 
            {
                if (lastOperationIndex.get(operation.threadId) >= operation.orderInThread) 
                {
                    continue;
                }
            }

            List<MethodCall> newCurrent = new ArrayList<>(current);
            Map<String, Integer> newLastOperationIndex = new HashMap<>(lastOperationIndex);
            List<MethodCall> newRemaining = new ArrayList<>(remaining);

            newCurrent.add(operation);
            newLastOperationIndex.put(operation.threadId, operation.orderInThread);
            newRemaining.remove(i);

            if (isValid(newCurrent)) 
            {
                generatePerms(newCurrent, newLastOperationIndex, newRemaining, result);
            }
        }
    }

    private static boolean isValid(List<MethodCall> sequence) 
    {
        Queue<String> queue = new LinkedList<>();

        for (MethodCall operation : sequence) 
        {
            if (operation.action.startsWith("enq")) 
            {
                queue.offer(operation.action);
            } 
            else if (operation.action.startsWith("deq")) 
            {
                if (queue.isEmpty() || !queue.poll().equals("enq(" + operation.action.substring(4))) 
                {
                    return false;
                }
            }
        }
        return true;
    }
}
