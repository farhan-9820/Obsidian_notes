---
excalidraw-plugin: parsed
tags:
  - excalidraw
---


# 4 
## a. 
### Repeated Searches: Efficiency Gains with Binary Search

When you need to perform multiple search operations on the same dataset, the efficiency of binary search becomes evident. Here’s a detailed breakdown:

#### Scenario

Imagine you have a dataset of size O(n) and you need to perform mm search queries on this dataset. Let’s compare the total time complexity for both linear search and binary search in this scenario.

#### Linear Search

- **Time Complexity per Search**: O(n)
    
- **Total Time Complexity for** m **Searches**: O(m⋅n)
    

#### Binary Search

1. **Initial Sorting**: The dataset needs to be sorted first, which takes O(nlog⁡n)
    
2. **Time Complexity per Search**: O(log⁡n)
    
3. **Total Time Complexity for** mm **Searches**: O(nlog⁡n)+O(m⋅log⁡n)
    

#### Comparison

- **Linear Search**: O(m⋅n)
    
- **Binary Search**: O(nlog⁡n)+O(m⋅log⁡n)
    

#### Example

Let’s consider an example with n=1,000,000n = 1,000,000 (1 million) and m=1,000m = 1,000 (1 thousand) search queries.

- **Linear Search**:
    
    - Each search takes O(n)=O(1,000,000)O(n) = O(1,000,000).
        
    - Total time for 1,000 searches: O(1,000⋅1,000,000)=O(1,000,000,000)O(1,000 \cdot 1,000,000) = O(1,000,000,000).
        
- **Binary Search**:
    
    - Initial sorting takes O(nlog⁡n)=O(1,000,000⋅log⁡1,000,000)≈O(1,000,000⋅20)=O(20,000,000)O(n \log n) = O(1,000,000 \cdot \log 1,000,000) \approx O(1,000,000 \cdot 20) = O(20,000,000).
        
    - Each search takes O(log⁡n)=O(20)O(\log n) = O(20).
        
    - Total time for 1,000 searches: O(20,000,000)+O(1,000⋅20)=O(20,000,000)+O(20,000)=O(20,020,000)O(20,000,000) + O(1,000 \cdot 20) = O(20,000,000) + O(20,000) = O(20,020,000).
        

#### Analysis

- **Linear Search**: O(1,000,000,000)O(1,000,000,000)
    
- **Binary Search**: O(20,020,000)O(20,020,000)
    

In this example, binary search is significantly more efficient than linear search when performing multiple queries. The initial sorting step is outweighed by the efficiency gains in the subsequent search operations.




## b. 
Using a randomized pivot in Quick Sort helps mitigate the worst-case time complexity, making it less likely to encounter the worst-case scenario. Here’s how it affects the time and space complexity:

### Time Complexity

- **Average Case**: The average-case time complexity remains O(nlog⁡n). Randomized pivot selection ensures that the partitions are more balanced on average.
    
- **Worst Case**: The worst-case time complexity is still O(n2)O(n^2), but the probability of encountering this scenario is significantly reduced due to the randomization of the pivot.
    

### Space Complexity

- **In-Place Sorting**: Quick Sort is an in-place sorting algorithm, so the primary memory usage comes from the stack space due to recursion.
    
- **Average Case**: The average-case space complexity is O(log⁡n) because the recursion depth is balanced.
    
- **Worst Case**: The worst-case space complexity is O(n)O(n) due to the depth of the recursion stack. However, with randomized pivot selection, the likelihood of hitting this worst-case scenario is much lower.
    

### Summary

- **Time Complexity**:
    
    - Average Case: O(nlog⁡n)
        
    - Worst Case: O(n2)O(n^2) (less likely with randomized pivot)
        
- **Space Complexity**:
    
    - Average Case: O(log⁡n)
        
    - Worst Case: O(n) (less likely with randomized pivot)




## c.  
To construct an array where Quick Sort fails to work in O(Nlog⁡N) time, we need to create a scenario where the pivot selection leads to highly unbalanced partitions. This typically happens when the pivot is always the smallest or largest element in the array. Here’s an example:

### Worst-Case Scenario for Quick Sort

If we always choose the first element as the pivot, an already sorted array (either in ascending or descending order) will cause Quick Sort to perform poorly. Here’s an example of such an array:

```
# Example of an array that causes Quick Sort to perform poorly
worst_case_array = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

```

### Explanation

- **Pivot Selection**: If the pivot is always the first element, the array is divided into two subarrays: one empty subarray and one subarray with n−1 elements.
    
- **Unbalanced Partitions**: This leads to highly unbalanced partitions, causing the recursion depth to be O(n).
    
- **Time Complexity**: The time complexity in this case becomes O(n^2) because each partitioning step only reduces the problem size by one element.






# question 1 about algorithms 

	1. lets say i have a array which is increasing and then decreasing, how do I implement binary search to find the maximum and minimum here?

		`def find_peak(arr):
		    left, right = 0, len(arr) - 1
		    while left < right:
		        mid = left + (right - left) // 2
		        if arr[mid] > arr[mid + 1]:
		            right = mid
		        else:
		            left = mid + 1
		    return arr[left]

2. how to calculate the midpoints for ternary search? 
# questions 

![[Pasted image 20241119031138.png]]
```
function maxConsecutiveZeros(arr, start, end):
    # Base case
    if start == end:
        return 1 if arr[start] == '0' else 0
    
    mid = (start + end) // 2
    
    # Get max from left and right halves
    left_max = maxConsecutiveZeros(arr, start, mid)
    right_max = maxConsecutiveZeros(arr, mid + 1, end)
    
    # Find crossing zeros
    # Count zeros going left from mid
    left_count = 0
    temp_count = 0
    for i from mid down to start:
        if arr[i] == '0':
            temp_count += 1
        else:
            break
    left_count = temp_count
    
    # Count zeros going right from mid+1
    right_count = 0
    temp_count = 0
    for i from mid+1 to end:
        if arr[i] == '0':
            temp_count += 1
        else:
            break
    right_count = temp_count
    
    # Combine crossing zeros if they're consecutive
    crossing_count = left_count + right_count
    
    # Return maximum of all three cases
    return max(left_max, right_max, crossing_count)
```

![[Pasted image 20241119021952.png]]

![[Pasted image 20241119022121.png]]

![[Pasted image 20241119022201.png]]

![[Pasted image 20241119022414.png]]

![[Pasted image 20241119022426.png]]


![[Pasted image 20241119022558.png]]

==⚠  Switch to EXCALIDRAW VIEW in the MORE OPTIONS menu of this document. ⚠== You can decompress Drawing data with the command palette: 'Decompress current Excalidraw file'. For more info check in plugin settings under 'Saving'


## Drawing
```compressed-json
N4IgLgngDgpiBcIYA8DGBDANgSwCYCd0B3EAGhADcZ8BnbAewDsEAmcm+gV31TkQAswYKDXgB6MQHNsYfpwBGAOlT0AtmIBeNCtlQbs6RmPry6uA4wC0KDDgLFLUTJ2lH8MTDHQ0YNMWHRJMRZFAA5FAGYyJE9VGEYwGgQAbQBdcnQoKABlALA+UFkYOIQQXHR8AGtoyXw8bOwNPkZOTExyHRgiACF0VErarkZcAGF6THp8UoBiADN5hZAAXyWgA
```
%%