# IKT103 — C++ Object-Oriented Programming

Coursework for **IKT103 — Advanced Programming** at the University of Agder. Five small **modern C++17** programs progressing from basic classes to file I/O, JSON serialization, SQLite persistence, and finally a REST HTTP client.

Built with **CMake** so each assignment compiles standalone on any platform.

## Repository structure

| Folder | Topic | Key techniques |
|--------|-------|----------------|
| [`assignment_1_1/`](assignment_1_1/) | Classes and objects | `Student` class with a static auto-incrementing ID counter; `vector<Student>` collection. |
| [`assignment_2_1/`](assignment_2_1/) | File I/O + data analysis | Reads `customer`, `product`, `order` records from text files; aggregations like `moneySpentPerCustomer` and `amountOrderedPerProduct`. |
| [`assignment_2_2/`](assignment_2_2/) | JSON serialization | Uses **RapidJSON** to load/save students; STL `list<Student*>` with operations like *find youngest*. |
| [`assignment_3_1/`](assignment_3_1/) | SQLite persistence | Full CRUD console app for a `students` table using **SQLiteCpp** — create, read by id, update, delete, list all. |
| [`assignment_4_1/`](assignment_4_1/) | REST HTTP client | Uses **C++ REST SDK (cpprest / Casablanca)** to talk to a JSON REST API on `http://localhost:5000`. |

## Tech stack

- **C++17**
- **CMake ≥ 3.21**
- External libraries (bundled in the repo for reproducibility):
  - [RapidJSON](https://rapidjson.org/) — JSON in `assignment_2_2`
  - [SQLiteCpp](https://github.com/SRombauts/SQLiteCpp) + SQLite — database in `assignment_3_1`
  - [C++ REST SDK](https://github.com/microsoft/cpprestsdk) — HTTP client in `assignment_4_1`

## Building and running

Each assignment is a standalone CMake project. To build any of them:

```bash
cd assignment_3_1
cmake -S . -B build
cmake --build build
./build/assignment_3_1     # Linux/macOS
./build/assignment_3_1.exe # Windows
```

Or open the folder's `CMakeLists.txt` in **CLion** / **Visual Studio** / **VS Code** with the CMake Tools extension and use the IDE's run button.

### Assignment 4 — REST client

The HTTP client expects a JSON REST server on `http://localhost:5000` exposing a `/students` endpoint. Spin one up in any language (Node.js Express, Python Flask, .NET, etc.) returning JSON like:

```json
[
  { "id": 1, "name": "Alice", "email": "alice@example.com", "year": 2001 }
]
```

## Notes

- Build outputs (`cmake-build-*/`, `build/`, binaries) are excluded via `.gitignore`.
- The local SQLite database `school.sqlite` is recreated automatically on first run.
- External libraries are checked in so the projects compile out of the box; in a real-world setting you'd pull them via `FetchContent`, `vcpkg`, or `Conan`.
