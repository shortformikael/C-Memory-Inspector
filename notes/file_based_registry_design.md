# File-Based Memory Inspector Registry Design

## Current State Analysis
- Program correctly intercepts malloc/free calls via macro redirection
- Records heap allocations with file/line info
- Currently prints basic information but doesn't persist state
- Has MemoryEntry structure ready but wants file-based approach

## User's Design Direction
**Goal**: File-based registry system for true memory tracking

### Design Philosophy
- **Persistent tracking** - survives program execution for later analysis
- **Linear format** - easy to parse and analyze  
- **Complete lifecycle** - tracks both malloc AND free operations
- **Location awareness** - file/line info for debugging
- **No memory overhead** during execution (critical for low-memory constraints)
- **Post-mortem analysis** - can analyze patterns after program finishes

### Registry Format
```
Whenever something is allocated to the heap or free'd, keep track of it as an entry
In the file, each line represents an entry.
Each entry should contain what and where was stored.
Then when the program is over, read the registry and see if everything was free'd or if something was left hanging
```

## Design Considerations to Address

### File Format Questions
- [ ] What separator to use between fields? (comma, pipe, tab?)
- [ ] How to handle file concurrency if multiple processes use inspector?
- [ ] What's the strategy for registry file location?

### Analysis Questions  
- [ ] How to match malloc entries with their corresponding free entries?
- [ ] What leak detection patterns to implement?
- [ ] Will you track allocation sizes for statistics?

### Edge Cases to Consider
- [ ] What happens if the file write fails?
- [ ] How to handle NULL pointer frees?
- [ ] What about `realloc()` calls?

## Implementation Plan

### Phase 1: File Writing
- Create/open registry file
- Write entries in standardized format
- Handle file I/O errors gracefully

### Phase 2: Entry Matching
- Design allocation ID system
- Track malloc->free relationships
- Detect unmatched allocations (leaks)

### Phase 3: Analysis Engine
- Read registry file
- Match allocations with frees
- Generate leak reports and statistics

### Phase 4: Advanced Features
- realloc() tracking
- Memory usage patterns
- Performance analysis

## Technical Notes
- Mirrors how professional tools like Valgrind and AddressSanitizer work
- Building simplified version of tools reverse engineers use
- Perfect for low-memory constraint: persistent, minimal runtime overhead

---

*Design captured: 2026-01-20*
*Next steps: Implementation of file-based registry system*