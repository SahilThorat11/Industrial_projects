
---

# 📚 Generalised Data Structure Library in C++

---

A **generic, template-based Data Structure Library** implemented in **C++**, providing reusable implementations of fundamental data structures such as **Linked Lists, Stack, and Queue**.
Designed for **learning, academic projects, and DSA practice**.

---

## 🚀 Features

✔ Generic Programming using **C++ Templates**
✔ Supports multiple data types (`int`, `char`, `float`, etc.)
✔ Clean, modular, and well-documented code
✔ Covers **Linear & Circular** data structures
✔ Beginner-friendly and interview-ready

---

## 📦 Data Structures Implemented

| Category    | Data Structure  | Class Name  |
| ----------- | --------------- | ----------- |
| Linked List | Singly Linear   | `SinglyLLL` |
| Linked List | Doubly Linear   | `DoublyLLL` |
| Linked List | Singly Circular | `SinglyCLL` |
| Linked List | Doubly Circular | `DoublyCLL` |
| Stack       | LIFO            | `Stack`     |
| Queue       | FIFO            | `Queue`     |

---

## 🛠️ Operations Supported

### 🔗 Linked Lists

* `InsertFirst()`
* `InsertLast()`
* `InsertAtPos()`
* `DeleteFirst()`
* `DeleteLast()`
* `DeleteAtPos()`
* `Display()`
* `Count()`

### 📚 Stack

* `Push()`
* `Pop()`
* `Peep()`
* `Display()`
* `Count()`

### 🚶 Queue

* `Enqueue()`
* `Dequeue()`
* `Display()`
* `Count()`

---

## 🧰 Technologies & Concepts

* **Language:** C++
* **Core Concepts:**

  * Templates (Generic Programming)
  * Object-Oriented Programming (OOP)
  * Pointers & Dynamic Memory Allocation
  * Linked Lists
  * Stack & Queue
  * Circular Data Structures

---

## 📂 Project Structure

```
📁 Generalised-Data-Structure-Library
│
├── GDSL.cpp        // Full implementation + test cases
├── README.md       // Project documentation
```

---

## ⚙️ Build & Run

### 🔨 Compile

```bash
g++ main.cpp -o ds_library
```

### ▶️ Execute

```bash
./ds_library
```

---

## 🧪 Sample Usage

```cpp
SinglyLLL<int> obj;

obj.InsertFirst(11);
obj.InsertLast(51);
obj.InsertAtPos(21, 2);

obj.Display();
cout << "Count: " << obj.Count() << "\n";
```

---

## 📤 Sample Output

```
| 11 | -> | 21 | -> | 51 | -> NULL
Count: 3
```

---

## 👨‍💻 Author

**Sahil Rajaram Thorat**
📅 January 2026
🎓 Data Structures using C++
📌 Academic / Learning Project

---

## 🔮 Future Enhancements

* Add **destructors** to free memory
* Improve **error handling**
* Split code into **.h / .cpp** files
* Add **unit tests**
* Performance optimization
* STL comparison examples

---

## 📜 License

This project is licensed for **educational use**.
Feel free to use, modify, and share with proper attribution.

---

### ⭐ If you find this useful, give the repository a star!

---

