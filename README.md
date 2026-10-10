# DB SQL Browser

Small relational database with its own engine written in C++ and two front ends: a command-line interface and a Java desktop GUI.

## How it works

- **Database engine.** Written in C++ with an object-oriented, modular design and a custom query handler that parses and executes the queries.
- **Command-line interface.** Runs queries directly against the engine.
- **Java GUI.** A desktop interface that passes queries to the native C++ engine through JNI and shows the results.

## Tech stack

C++, Java, JNI
