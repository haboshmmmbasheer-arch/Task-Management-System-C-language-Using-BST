# Task Management System using BST (C)

A menu-driven Task Management System implemented in C using a **Binary Search Tree (BST)**.
Tasks are loaded from `tasks.txt` and stored in a BST, with support for insertion, deletion, searching, performing tasks, and restructuring the BST based on different keys.

## What I implemented (main.c)

### Data Structure
- **BST (Binary Search Tree)** node contains:
  - Task ID
  - Task Name
  - Task Date
  - Task Duration (hours)
  - left / right pointers

### Program Menus (Features)
1. **Load Tasks File**
   - Reads tasks from `tasks.txt`
   - Inserts tasks into the BST (default insertion by **ID**)

2. **Add a New Task**
   - Adds a task to the BST
   - Checks if the ID already exists to prevent duplicates

3. **Delete a Task**
   - Deletes a task from the BST using Task ID
   - Uses standard BST delete (replace with minimum from right subtree when needed)

4. **Search for a Task**
   - Searches by **Task Name**
   - Rebuilds the BST ordered by Name, then performs BST search by name

5. **Perform a Task**
   - Finds a task by ID in the unperformed BST
   - Inserts it into another BST called **performed**

6. **View Unperformed Tasks**
   - Prints tasks in-order (sorted output)
   - Uses a rebuilt/copy tree to display tasks ordered by name

7. **View Performed Tasks**
   - Prints performed tasks (in-order)

8. **Restructure the Tasks BST**
   - Rebuilds (copies) the BST based on chosen key:
     - 1) ID
     - 2) Name
     - 3) Date
     - 4) Duration

9. **View the tasks BST info**
   - Displays:
     - Tree height
     - Tree size
     - Number of leaves
     - Number of internal nodes

10. **Exit**

## Input File Format (tasks.txt)
Each line must follow:
`ID#TaskName#TaskDate#Duration`

Example:
10#meeting#22/3/2025#1.5
11#attend lecture#25/3/2025#3

## How to Compile & Run
Compile:
```bash
gcc main.c -o bst_tasks
./bst_tasks
