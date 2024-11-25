import java.util.*;

public class Register {
    List<RegisterOperation> operations = new ArrayList<>();

    void write(int value, int startTime, int endTime) {
        operations.add(new RegisterOperation(RegisterOperation.Type.WRITE, value, startTime, endTime));
    }

    void read(int startTime, int endTime) {
        operations.add(new RegisterOperation(RegisterOperation.Type.READ, null, startTime, endTime));
    }

    List<List<Integer>> getValidReadValues() 
    {
      List<RegisterOperation> reads = new ArrayList<>();
      List<RegisterOperation> writes = new ArrayList<>();

      for(RegisterOperation op : operations)
      {
        if(op.type == RegisterOperation.Type.READ)
        {
          reads.add(op);
        }
        else
        {
          writes.add(op);
        }
      }

      List<List<Integer>> result = new ArrayList<>();
      generateReadCombinations(result, new ArrayList<>() , reads , writes , 0);
      return result;
    }

    private void generateReadCombinations(List<List<Integer>> result , List<Integer> current , List<RegisterOperation> reads , List<RegisterOperation> writes , int readIndex)
    {
      if(readIndex == reads.size())
      {
        result.add(new ArrayList<>(current));
        return;
      }

      RegisterOperation currentRead = reads.get(readIndex);
      Set<Integer> possibleValues = new HashSet<>();
      Integer latestWriteValue = null;
      for (RegisterOperation write : writes)
      {
        if(write.endTime < currentRead.startTime)
        {
          latestWriteValue = write.value;
        }
      }
      possibleValues.add(latestWriteValue);
      for(RegisterOperation write : writes)
      {
        if ((currentRead.startTime < write.endTime && currentRead.endTime > write.startTime)) 
        {
          possibleValues.add(write.value);
        }
      }
      if(possibleValues.isEmpty())
      {
        possibleValues.add(null);
      }
      for (Integer value : possibleValues) 
      {
        current.add(value);
        generateReadCombinations(result, current, reads, writes, readIndex + 1);
        current.remove(current.size() - 1);
      }



    }
}