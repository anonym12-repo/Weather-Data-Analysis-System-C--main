# 🌡️ Weather Data Analysis System (C++)
### Custom Template Data Structures, Statistical Analysis & CSV Pipeline for Multi-Year Meteorological Data

[![C++](https://img.shields.io/badge/C%2B%2B-Data%20Structures-00599C.svg)](https://isocpp.org/)
[![Doxygen](https://img.shields.io/badge/Docs-Doxygen-2C4AA8.svg)](https://www.doxygen.nl/)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](#license)

## 📌 Overview

A C++ system that ingests multiple years of raw weather-station CSV data (wind speed, ambient temperature, solar radiation), aggregates it by month/year using **hand-built generic data structures**, and produces statistical analysis (mean, standard deviation, Pearson correlation, mean absolute deviation) through an interactive menu. Rather than relying on off-the-shelf containers throughout, the project implements its own **template Binary Search Tree** and **dynamic array (Vector)** from scratch, alongside a thin, purpose-built wrapper around `std::map`, exercising real data-structure design decisions (memory management, deep-copy semantics, function-pointer-based traversal).

The codebase is backed by a **from-scratch unit + integration test suite**, static analysis via **Cppcheck**, and full **Doxygen-generated API documentation** — treating correctness and maintainability as first-class project deliverables, not afterthoughts.

## 🎯 Why This Project Stands Out to Recruiters

- **Implemented core data structures from first principles** — a template `Bst<T>` with recursive insert/search, three traversal orders (in/pre/post-order) driven by function pointers, deep-copy copy-constructor and assignment operator, and full recursive destruction. This is CS-fundamentals-level work: manual memory management, the Big Three (copy constructor, assignment operator, destructor), and template generic programming — skills that matter directly for systems, embedded, and performance-critical roles.
- **Deliberate architecture around encapsulation, not just usage** — rather than exposing `std::vector`/`std::map` directly, the project wraps them behind minimal, purpose-fit interfaces (`Vector<T>`, `Map<K,V>`), a defensive design pattern real codebases use to control coupling to standard library internals and simplify future substitution.
- **Real automated testing discipline** — a dedicated test suite (`BstTest`, `MapTest`, `DateRecMapTest`, `FileReaderTest`, `MonthYearKeyTest`, and cross-component `IntegrationTests`) each with 5–11 explicit test cases covering edge cases (empty containers, duplicate keys, boundary values, non-existent lookups) — not just happy-path checks.
- **Static analysis integrated into the workflow** — the project includes actual Cppcheck output (`cppcheck.txt`, `CppCheckResults.xml`) as part of its QA process, showing awareness of tooling beyond "it compiles and runs."
- **Honest, documented self-assessment** — the project's own evaluation notes candidly separate "fully working" from "partially working" functionality and explicitly document known limitations (unbalanced BST performance characteristics, a previously-misunderstood filtering requirement that was caught and fixed) rather than presenting an inflated picture — a hallmark of engineering maturity.
- **Professional documentation practice** — full Doxygen-style `@brief`/`@param`/`@pre`/`@post` documentation comments across every class and method, plus generated HTML API docs, mirrors how documentation is expected to be maintained in production C++ codebases.

## 🧠 Architecture

**Pipeline:** `CSV Data Files → RecordParse → WeatherRecord objects → WindlogAggregator (Map<MonthYearKey, MonthlyData>) → Stats/UnitConvert → Menu-driven Reports → CSV Export`

**Custom data structures:**
| Component | Purpose |
|---|---|
| `Bst<T>` | Template binary search tree — generic insert/search plus in-order, pre-order, and post-order traversal, each accepting a callback + optional filter predicate via function pointers |
| `Vector<T>` | Template dynamic array wrapper — encapsulated growth, subscript access, size/empty queries |
| `Map<K,V>` | Minimal key-value wrapper around `std::map` — insert, contains, get (const and non-const) |

**Domain model:**
- `Date`, `MyTime`, `WeatherRecord` — value types for a single timestamped observation (wind speed, temperature, solar radiation)
- `MonthYearKey` — composite (year, month) key type with well-defined ordering, used as the `Map` key for monthly aggregation
- `MonthlyData` — validated container of all readings for a given month/year, with input validation (`isValidMonth`, `isValidYear`)
- `DateRecMap` — maps individual `Date`s to their associated `WeatherRecord`s
- `WindlogAggregator` — orchestrates aggregation of raw records into the `Map<MonthYearKey, MonthlyData>` structure and exposes query methods (per-month wind speeds, temperatures, solar radiation, cross-year lookups)
- `Stats` — mean, sample standard deviation, Pearson correlation coefficient, and mean absolute deviation over `Vector<float>` datasets
- `UnitConvert` — m/s → km/h and W/m² → kWh/m² conversions, including vectorized/batch variants
- `RecordParse` / `FileReader` — CSV ingestion and multi-file source discovery
- `Menu` — the interactive front-end tying it all together

**Menu-driven analysis (4 core operations):**
1. Average wind speed + standard deviation for a specific month/year
2. Average temperature + standard deviation across every month of a specific year
3. Correlation coefficients for a specific calendar month across all years in the dataset
4. Full monthly weather data export to CSV

## 🛠️ Tech Stack

`C++` · Template metaprogramming (generic `Bst<T>`, `Vector<T>`) · Manual memory management (RAII, deep copy semantics, custom destructors) · Function pointers for callback-driven tree traversal · File I/O (CSV parsing) · Statistical computation (mean, std dev, Pearson correlation, MAD) · **Doxygen** documentation · **Cppcheck** static analysis · Custom unit + integration test framework

## 📁 Repository Structure

```
├── src/                      # Implementation files
│   ├── Date.cpp / MyTime.cpp / WeatherRecord.cpp
│   ├── RecordParse.cpp / FileReader.cpp
│   ├── MonthYearKey.cpp / MonthlyData.cpp / DateRecMap.cpp
│   ├── WindlogAggregator.cpp / Stats.cpp / UnitConvert.cpp
│   ├── DateUtils.cpp / Menu.cpp
├── include/                  # Header files (Doxygen-documented)
│   ├── Bst.h / Vector.h / Map.h        # Custom generic data structures
│   ├── Date.h / MyTime.h / WeatherRecord.h
│   ├── RecordParse.h / FileReader.h
│   ├── MonthYearKey.h / MonthlyData.h / DateRecMap.h
│   ├── WindlogAggregator.h / Stats.h / UnitConvert.h
│   ├── DateUtils.h / Menu.h
├── main.cpp                  # Program entry point
├── test plan a2/
│   ├── unit test classes/    # BstTest, MapTest, DateRecMapTest, FileReaderTest,
│   │                         #   MonthYearKeyTest, IntegrationTests
│   ├── test data/            # Sample CSVs used by the test suite
│   └── ict283_testing_a2.pdf # Formal test plan document
├── docs/                     # Doxygen-generated API documentation
├── documentation.pdf         # Full technical documentation
└── README.md
```

## 🚀 Building & Running

Built as a Code::Blocks project (Ant-style `.cbp`). To build manually with g++:
```bash
g++ -std=c++11 -Iinclude main.cpp src/*.cpp -o weather_analysis
./weather_analysis
```
On launch, the program reads all data source files listed in `data/data_source.txt`, aggregates every record by month/year, and presents the interactive analysis menu.

## 🔮 Future Work

- Rebalance the BST (e.g. AVL or red-black tree) to guarantee O(log n) performance on already-sorted date sequences, addressing the documented worst-case O(n) limitation
- Convert the recursive BST operations to iterative equivalents to remove the theoretical stack-overflow risk on very large datasets
- Strengthen malformed-CSV handling with structured error reporting rather than relying on downstream validation alone
- Expand automated test coverage to the statistical (`Stats`) and unit-conversion (`UnitConvert`) modules

## 📄 License

This project is available under the MIT License.

---

*This project was completed as an academic assignment (ICT283) focused on custom data structure design, template programming, and software testing methodology in C++.*
