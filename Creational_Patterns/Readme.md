# Creational Design Patterns

Creational design patterns deal with object creation mechanisms, optimizing and abstracting the instantiation process in ways that suit varying situations. They help you manage complexity by decoupling your code from concrete class instantiation, supporting flexibility, scalability, and clarity in your software architecture.

---

## What Are Creational Patterns?

Creational patterns abstract the process of object creation, making your code more robust to change and easier to extend.  
They allow you to:
- Control **when**, **how**, and **which** objects are created
- Encapsulate the instantiation logic, so client code is not tightly coupled to specific classes
- Support families of related objects or enforce certain constraints (e.g., only one instance exists)

---

## Benefits

- **Encapsulation:** Object creation logic is centralized and hidden from client code.
- **Flexibility:** New types or creation strategies can be introduced without changing client code.
- **Testability:** Object creation can be controlled or mocked for testing purposes.
- **Scalability:** Patterns support easy extension to families of related objects.

---

## Common Creational Patterns

This section covers the following patterns, each with its own folder, explanation, analogy, UML/class structure, and code example:

- **Singleton:** Ensures a class has only one instance and provides a global point of access.
- **Factory Method:** Lets a class defer instantiation to subclasses, allowing new object types without changing existing code.
- **Abstract Factory:** Provides an interface for creating families of related objects without specifying their concrete classes.
- **Builder:** Separates the construction of a complex object from its representation, enabling step-by-step creation and different configurations.
- **Prototype:** Creates new objects by cloning an existing object, avoiding costly creation or enforcing runtime flexibility.

---

## When to Use Creational Patterns

- When object creation logic becomes complex, repetitive, or tightly coupled to the client code
- When you need to enforce constraints on instantiation (e.g., only one instance, pooling, etc.)
- When you want to enable future extensibility (supporting new families/types with minimal changes)
- When construction involves multiple steps or possible configurations



---




> “Creational patterns make creation logic explicit, isolated, and adaptable—leading to flexible, robust, and maintainable code.”

---
