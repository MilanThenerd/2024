import java.util.Random;

public class BoundedTimestamp {
    public final int[] timestamp;

    public BoundedTimestamp(int[] timestampArray) {
        //create a new timestamp with the same values as the input array
        this.timestamp = timestampArray;
    }

    public BoundedTimestamp(int n) {
        this.timestamp = new int[n];
        //explicitly set new timestamp to 0,0,0...
        for (int i = 0; i < n; i++) {
            timestamp[i] = 0;
        }
    }

    // Returns 1 if this comes before the other (i.e this is earlier), -1 if this comes after the other (i.e this is later), 0 if they are equal
    public int compare(BoundedTimestamp other) 
    {
      for (int i = 0; i < this.timestamp.length; i++) 
      {
        int thisDigit = this.timestamp[i];
        int otherDigit = other.timestamp[i];
        if (thisDigit == otherDigit) 
        {
          continue;
        }
        if((thisDigit == 0 && otherDigit == 1) ||
           (thisDigit == 1 && otherDigit == 2) ||
           (thisDigit == 2 && otherDigit == 0)){
            return 1;
        }
        else
        {
          return -1;
        }
    }
    return 0;
    }

    

    public static BoundedTimestamp getNext(BoundedTimestamp[] label, int indexAskingForLabel) 
    {
      int n = label[0].timestamp.length;
      int[] current = label[indexAskingForLabel].timestamp.clone();
      
      int i = n - 1;
      while (i >= 0) 
      {
          current[i] = (current[i] + 1) % 3;
          if (current[i] != 0) 
          {
              break;
          }
          i--;
      }
      BoundedTimestamp newTimestamp = new BoundedTimestamp(current);
      while (true) 
      {
          boolean valid = true;
          if(newTimestamp == new BoundedTimestamp(label[indexAskingForLabel].timestamp.clone()))
          {
            valid = false;
          }
          for (int j = 0; j < label.length; j++)
           {
              if (j != indexAskingForLabel) 
              {
                Random rand = new Random();
                int number = rand.nextInt() % 2;
                  BoundedTimestamp other = label[j];
                  if (newTimestamp.compare(other) == 1 || newTimestamp.compare(other) == 0) 
                  {
                      valid = false;
                      break;
                  }
              }
          }
          
          if (valid) 
          {
              break;
          }
          i = n - 1;
          while (i >= 0) 
          {
              current[i] = (current[i] + 1) % 3;
              if (current[i] != 0) 
              {
                  break;
              }
              i--;
          }
          
          newTimestamp = new BoundedTimestamp(current);
      }
      
      return newTimestamp;
  }

    //you may add varibles and methods as needed

    @Override
    public String toString() {
        return java.util.Arrays.toString(timestamp);
    }

}
