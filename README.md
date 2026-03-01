# DTV Application Manager

A robust C++17 object-oriented manager designed for Digital TV (DTV) application lifecycles. This system handles application lists received via JSON, utilizing polymorphism to manage different TV standards (TV 2.X and TV 3.0) with high memory safety.

## 🚀 Features

* **Dynamic Management**: Full support for Create, Update, and Delete (CRUD) operations on applications.
* **JSON Integration**: Powered by `nlohmann/json` for seamless parsing of external metadata.
* **Polymorphic Architecture**: Specialized behavior for `AppTV2X` and `AppTV30` using a `BaseApp` interface.
* **Memory Safety**: Built with `std::shared_ptr` to ensure automatic resource management and avoid memory leaks.
* **Containerized Environment**: Multi-stage Docker build for consistent compilation and lightweight execution.

---

## 🏗️ Architecture & Design

The project follows a clean separation of concerns, facilitating maintenance and scalability.



* **`Application` (Core)**: Defines the data structures (`AppInfo`), Enums, and specific implementations for TV standards.
* **`ApplicationManager` (Engine)**: Encapsulates the business logic, manages the app collection, and handles JSON parsing.
* **`Logging`**: Integrated with `spdlog` for high-performance, formatted console output.

---

## 🐳 Running with Docker (Highly Recommended)

The project is fully containerized. This ensures that all dependencies (`spdlog`, `GTest`, `nlohmann-json`) are correctly configured without polluting your host machine.

### 1. Build the Image
From the root directory, run:
```bash
docker build -t dtv-app-manager .
```

### 2. Execution Options
From the root directory, Run Middleware (Standard):
```bash
docker build -t dtv-app-manager .
```
From the root directory, Run Unit Tests Individually:
```bash
docker run --rm --entrypoint ./app_manager_test dtv-app-manager
```

🛠️ Local Development (Manual Build)
If you prefer to build locally (e.g., via WSL or Linux), ensure you have the following requirements:

Compiler: GCC/Clang with C++17 support.

Build System: CMake 3.10 or higher.

Dependencies: nlohmann-json3-dev, libspdlog-dev, libgtest-dev.

Steps:
```bash
cmake -S . -B build
cmake --build build
```

# To run tests locally:
```bash
./build/app_manager_test
```
# To run the app locally:
```bash
./build/dtv_middleware
```
📋 JSON Data Protocol
The ApplicationManager expects a JSON array containing application metadata. The system is resilient to missing keys, providing clear error logging:
[
    {
        "id": 101,
        "name": "Test App",
        "path": "/usr/bin/dtv_app",
        "controlCode": 1,
        "engineType": 9,
        "appType": 1
    }
]

📈 Quality Standards

This project implements the following developer goals for 2026:

[x] Dockerization: Full multi-stage environment.

[x] Standardization: Portable and reproducible build process.

[x] Robustness: Unit testing and exception handling for JSON parsing.