# DB SQL Browser

Small in-memory relational database with its own engine written in C++ and a JavaFX desktop interface. The GUI calls the native engine through JNI.

## Supported commands

- `CREATE TABLE name (col1, col2, ...)` and `DROP TABLE name`
- `INSERT INTO name (cols) VALUES ("v1", "v2"), ...`
- `SELECT cols FROM name WHERE col = "value"`, with `*` for all columns
- `UPDATE name SET ... WHERE ...` and `DELETE FROM name WHERE ...`
- `SHOW TABLES`
- `SAVE SQL`, which exports the whole database into a SQLite file

`WHERE` accepts conditions with `=`, `<` and `>`, and a row must satisfy all of them.

## How it works

- **Engine.** `Baza` holds the tables and `Tabela` holds the column names and the rows. Commands are recognized and split into parts with regular expressions, then executed over the rows in memory.
- **Persistence.** The database is written to a text file after every command and loaded from it on start.
- **SQLite export.** `SAVE SQL` uses the SQLite C library to create a `.db` file with the same tables and rows. SQLite is used only for this export, not for running queries.
- **JNI bridge.** The Java class `JNI` declares native methods implemented in `JNI.cpp`. A command goes in as a string and the result comes back as a string.
- **GUI.** A JavaFX window with a command field, the query result and the list of current tables.

## Repository layout

| Folder | Contents |
| --- | --- |
| `javaa_native/` | C++ engine (`Baza`, `Tabela`), the JNI bridge and the SQLite sources |
| `application/` | JavaFX interface |

## Tech stack

C++, Java, JavaFX, JNI, SQLite (export only)
