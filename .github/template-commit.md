# Commit Template

Commit messages should be self-explanatory with enough detail for developers, maintainers, testers, and every other member of the development team to understand what exactly has changed with each commit.

## Commit Types

Use the following symbols to indicate the type of commit:

- **`[+]`**: New feature
- **`[-]`**: Removal
- **`[#]`**: Bug fix
- **`[~]`**: Refactoring, general changes, or others that don't fit into the first two

Example:

```
[+] Auth: Add JWT-based authentication
[-] LegacyCode: Remove deprecated API endpoint
[#] Payment: Fix rounding issue in total amount
[~] UI: Refactor dashboard components
```

## Commit Message Structure

Each commit message consists of the following parts:

1. **Summary (required):**

   - The summary has two parts:
     - The name of the module
     - A brief description of the change

2. **Description (optional, but encouraged):**
   - Details about how the algorithm works
   - Any new dependencies introduced
   - Explanation of how the change solves the problem or provides a solution
   - Additional notes
   - Relevant links (issues, other PRs, etc.)
   - Co-authors, if applicable

## Writing the Commit

There are 3 basic rules for writing a proper commit:
1- Imperative mood
2- Avoiding the period
3- Capitalize the messages

1. **Imperative Mood:**
   Use the **imperative mood** in the summary line. To remove any confusion, a properly written summary line for a commit message should complete the following sentence:

**`This commit will...`**

Note: You do **not** need to use **_imperative mood_** in the additional notes, remarks etc.

For examples:

- This commit will **_Change the search algorithm_**
- This commit will **_Remove deprecated methods_**
- This commit will **_Merge pull request #123 from foo/bar_**
- This commit will ~~Fixed bug~~
- This commit will ~~Changing input logic~~
- This commit will ~~Adding new sweet API methods~~

---

2. **Do not end with a period:**
   Trailing punctuation is unnecessary in commit messages.

Example:

- Open the pod bay doors

Instead of:

- ~~Open the pod bay doors.~~

---

3. **Capitalize the Commit Messages:**
   This is as simple as it sounds. Begin all commit message lines with a capital letter.

For example:

- Accelerate to 88 miles per hour

Instead of:

- ~~accelerate to 88 miles per hour~~

## Template Commit

Below is the recommended template for writing commit messages:

```plaintext
[TYPE] Module Name: Summarize the change in less than 50 characters

# What changed?
- Explain the new algorithm or functionality.
- Mention new dependencies, if any.

# Why was this change made?
- Explain the reason behind the change.
- Each bullet point should be under 72 characters.

# **Remarks (if needed):**
- Include any extra notes, relevant links, or co-authors.

Issue: #GITHUB_ISSUE_ID
```

## Example Commit

Here is the example commit:

```plaintext
[~] UART: Optimize UART transmission reliability

- Implement a retry mechanism for failed UART transmissions
- Adjust buffer size to reduce data loss
- Improve error handling by adding status checks

- Prevent occasional data loss due to transmission failures
- Enhance reliability in noisy environments
- Reduce CPU overhead by optimizing buffer usage

**Additional Remarks:**
- Tested on STM32F407 with a baud rate of 115200
- Future improvement: Implement DMA-based UART handling

Issue: #456
```

**NOT**: Check [this](https://cbea.ms/git-commit/) article to read more about writing good commit messages.
Another well-written git commit can be found [here](https://github.com/bitcoin/bitcoin/commit/eb0b56b19017ab5c16c745e6da39c53126924ed6).
