# System-Design Patterns Library

A curated collection of **system design patterns** with example implementations in **Java** and **C++**, meant to serve as a reference and learning resource for scalable and maintainable software architecture.

---

## 📁 Repository Structure

System-Design/
├── C++/ ← C++ implementations of design/system patterns
│ ├── Singleton/
│ ├── Factory/
│ ├── ...
│
└── Java/ ← Java implementations of design/system patterns
├── Singleton/
├── Factory/
├── ...


> ✨ Each folder contains self-contained examples along with source files to help you understand the pattern from scratch.

---

## 🔧 Included Design Patterns

| Category     | Patterns (Examples)                                   |
|-------------|--------------------------------------------------------|
| Creational   | Singleton, Factory, Abstract Factory, Builder          |
| Structural   | Adapter, Decorator, Facade, Proxy                      |
| Behavioral   | Observer, Strategy, Command, Chain of Responsibility   |

*(Update the above list according to the patterns currently included in your code.)*

---

## 🚀 Getting Started

### ✅ Requirements

- C++17 compatible compiler (e.g., `g++`, `clang++`)
- Java 8+ (JDK)
- **Optional**: CMake, Maven, or Gradle (depending on how you want to build)

---

### ▶ Run Java Examples

```bash
cd Java
# compile an example (replace with actual package path)
javac Singleton/SingletonExample.java
# run the class
java Singleton.SingletonExample

cd C++
# compile and run a pattern folder manually
g++ -std=c++17 Singleton/Singleton.cpp -o singleton
./singleton
