Since you're prepping for Python-specific array interviews, it's important to remember that while we talk about "arrays," we’re almost always dealing with **Lists** (which are dynamic arrays) or **NumPy arrays** for more technical data work.

Here are some essential interview questions ranging from conceptual to practical, along with the "why" behind the answers.

---

## 1. Conceptual Fundamentals

### Q: What is the difference between a Python List and an Array (from the `array` module)?

**A:** * **Lists:** Can store elements of different data types (heterogeneous). They are part of Python’s core and are very flexible.

- **Arrays:** Must store elements of the same data type (homogeneous). They are more memory-efficient for storing large amounts of basic data like integers or floats.
    

### Q: How are Python Lists stored in memory?

**A:** Python lists are **dynamic arrays**. They store **references** to objects rather than the objects themselves. When a list grows beyond its allocated capacity, Python allocates a larger chunk of memory (usually doubling it) and copies the references over. This makes `append()` an $O(1)$ operation on average (amortized).

---

## 2. Coding & Logic Questions

### Q: How do you reverse a list in Python? (Name three ways)

**A:**

1. **Slicing:** `my_list[::-1]` (Creates a new list).
    
2. **The `reverse()` method:** `my_list.reverse()` (Reverses in-place).
    
3. **The `reversed()` function:** `list(reversed(my_list))` (Returns an iterator).
    

### Q: Find the "Missing Number" in an array of 1 to $n$.

**A:** This is a classic logic test. The most efficient way uses the sum formula:

```python

def find_missing(arr, n):
    total_sum = n * (n + 1) // 2
    return total_sum - sum(arr)
```

- **Complexity:** $O(n)$ time and $O(1)$ space.
    

### Q: How do you remove duplicates from a list while maintaining the original order?

**A:** A common trick is using a `set` to track seen items, as converting a list to a `set` and back to a `list` (e.g., `list(set(arr))`) does **not** guarantee order.

Python

```python

def remove_duplicates(arr):
    seen = set()
    return [x for x in arr if not (x in seen or seen.add(x))]
```

---

## 3. Advanced Slicing & Manipulation

### Q: What does `arr[: : 2]` do?

**A:** It returns every second element of the list (stepping by 2), starting from index 0.

### Q: Given an array, rotate it to the right by $k$ steps.

**A:** You can use slicing for a very "Pythonic" one-liner:

Python

```python

def rotate(nums, k):
    k %= len(nums)
    nums[:] = nums[-k:] + nums[:-k]
```

---

## 4. Performance & Complexity

### Q: What is the time complexity of `pop(0)` vs. `pop()`?

**A:**

- **`pop()`**: $O(1)$. Removing the last element doesn't require shifting any other elements.
    
- **`pop(0)`**: $O(n)$. Every other element in the list must be shifted one position to the left to fill the gap.
    

### Q: Why would you use a `collections.deque` instead of a List?

**A:** If you need to add or remove elements from the **beginning** of the sequence frequently. A `deque` (double-ended queue) provides $O(1)$ performance for `popleft()` and `appendleft()`, whereas a list takes $O(n)$ for those operations.

---

---

**Quick Tip for the Interview:** If they ask about "huge datasets" or "matrix math," always mention **NumPy**. Interviewers love it when you know which tool fits the scale of the problem.
