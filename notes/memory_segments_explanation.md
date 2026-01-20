# Memory Segments - Complete Explanation

## Overview
Memory segments are fundamental to how C programs organize memory. Understanding them is crucial for reverse engineering, debugging, and performance optimization.

## Complete Memory Segment Breakdown

### 1. **Code Segment (Text Segment)**
- **Purpose**: Stores executable instructions
- **Characteristics**: Read-only, fixed size, shared (multiple processes)
- **What's inside**: Your compiled functions, machine code
- **Address range**: Lowest addresses (0x400000+)
- **Example**: All your functions like `main()`, `log_info()`, `minsp_malloc()`

### 2. **Data Segment**
- **Purpose**: Initialized global and static variables
- **Characteristics**: Read-write, fixed size, program lifetime
- **What's inside**: Variables with initial values, string literals
- **Address range**: Low to medium addresses
- **Example**: 
  ```c
  int initialized_global = 100;
  static char message[] = "data segment";
  ```

### 3. **BSS Segment**
- **Purpose**: Uninitialized global and static variables
- **Characteristics**: Read-write, fixed size, zero-initialized at startup
- **What's inside**: Variables declared without initial values
- **Address range**: Follows data segment
- **Example**:
  ```c
  int uninitialized_global;
  static long uninitialized_static;
  ```

### 4. **Heap Segment**
- **Purpose**: Dynamic memory allocation
- **Characteristics**: Grows upward, managed by malloc/free, variable size
- **What's inside**: `malloc()` allocations, dynamic data structures
- **Address range**: Medium addresses
- **Example**:
  ```c
  int *ptr = malloc(sizeof(int) * 100);
  ```

### 5. **Stack Segment**
- **Purpose**: Local variables, function calls, automatic storage
- **Characteristics**: Grows downward, LIFO, function-call boundaries
- **What's inside**: Local variables, return addresses, parameters
- **Address range**: High addresses (0x7fffffff+)
- **Example**:
  ```c
  void function() {
      int local_var = 5;  // Stack allocation
  }
  ```

## Memory Layout Visualization

```
High addresses: 0x7fffffffffff
┌─────────────────────────────────┐
│         Stack Segment           │  ← Grows downward
│    (local variables, etc.)      │
├─────────────────────────────────┤
│                                 │
│                                 │
│         Heap Segment            │  ← Grows upward
│      (malloc allocations)       │
│                                 │
├─────────────────────────────────┤
│         BSS Segment             │  ← Uninitialized globals
└─────────────────────────────────┘
Low addresses: 0x400000
┌─────────────────────────────────┐
│       Data Segment             │  ← Initialized globals
├─────────────────────────────────┤
│       Code Segment             │  ← Executable instructions
└─────────────────────────────────┘
```

## Practical Example from Our Demos

From `complete_memory_demo.c` output:
```
Code (main):       0x4004f8    ← Code segment
Data (global):     0x403030    ← Data segment  
Data (static):     0x403040    ← Data segment
BSS (uninit):      0x403060    ← BSS segment
Heap allocation:  0x575d320   ← Heap segment
Stack variable:   0x7ffdc659bcf4 ← Stack segment
```

## Why This Matters for Reverse Engineering

### **For Reverse Engineers:**
- **Code Segment**: Find executable code, disassemble functions
- **Data Segment**: Locate constants, strings, configuration
- **BSS Segment**: Find zero-initialized variables, buffers
- **Heap Segment**: Track dynamic allocations, find memory leaks
- **Stack Segment**: Analyze function calls, find stack overflows

### **For Your Memory Inspector Project:**
```c
// These live in the data segment:
static void* (*real_malloc)(size_t) = malloc;
static void (*real_free)(void *) = free;

// These track allocations across heap/stack:
void* minsp_malloc(size_t size, const char *file, int line);
void minsp_free(void *ptr, const char *file, int line);
```

## Key Takeaways

1. **Fixed vs Dynamic**: Code/Data/BSS are fixed; Heap/Stack are dynamic
2. **Lifetime Matters**: Segments determine when variables exist
3. **Address Patterns**: Each segment has predictable address ranges
4. **Security Implications**: Different segments have different permissions
5. **Debugging Value**: Understanding segments helps locate problems

## Tools for Exploring Segments

- **`size` command**: Shows segment sizes in executables
- **`objdump`**: Disassembles code segment
- **`gdb`**: Inspects memory at runtime
- **`/proc/[pid]/maps`**: Shows process memory layout (Linux)

## Segment Size Example

From our demo output:
```
   text    data     bss     dec     hex    filename
   1961     608      24    2593     a21    complete_memory_demo
```
- text (code): 1961 bytes
- data: 608 bytes  
- bss: 24 bytes

---

*Generated: 2026-01-20*
*Project: C Memory Inspector - Reverse Engineering Learning*