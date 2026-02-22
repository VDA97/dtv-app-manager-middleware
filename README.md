# DTV Application Manager

A robust C++17 object-oriented manager designed for Digital TV (DTV) application lifecycles. This system handles application lists received via JSON, utilizing polymorphism to manage different TV standards (TV 2.X and TV 3.0) with high memory safety.

## 🚀 Features

* **Dynamic Management**: Full support for Create, Update, and Delete (CRUD) operations on applications.
* **JSON Integration**: Powered by `nlohmann/json` for seamless parsing of external API strings.
* **Polymorphic Architecture**: Uses a `BaseApp` interface to handle specialized behavior for `AppTV2X` and `AppTV30`.
* **Memory Safety**: Built with `std::shared_ptr` and `std::vector` to ensure automatic memory management and reference integrity.
* **Efficient Lookups**: Optimized search by ID to prevent duplicate entries and facilitate quick updates.

---

## 🏗️ Architecture & Design

The project follows the standard C++ separation of concerns, ensuring a clean build process and high maintainability.

* **`Application` (Core)**: Defines data structures (`AppInfo`), Enums, and specific TV implementations.
* **`ApplicationManager` (Engine)**: Manages the collection of apps and encapsulates the business logic for list processing.



---

## 🛠️ Requirements

* **Compiler**: GCC/Clang with C++17 support.
* **Build System**: CMake 3.10 or higher.
* **Dependency**: [nlohmann/json](https://github.com/nlohmann/json)
    * *Ubuntu/WSL installation*: `sudo apt install nlohmann-json3-dev`

## 📥 Build & Run

1.  **Clone and Navigate**:
    ```bash
    git clone <your-repo-url>
    cd dtv-app-manager
    ```

2.  **Configure and Compile**:
    ```bash
    cmake -S . -B build
    cmake --build build
    ```

3.  **Execute Tests**:
    ```bash
    ./build/app_manager_test
    ```

---

## 📋 JSON Data Protocol

The `ApplicationManager` expects a JSON array containing application metadata:

```json
[
    {
        "id": 101,
        "name": "Global Play",
        "path": "/usr/bin/dtv_app",
        "controlCode": 1,
        "engineType": 9,
        "appType": 1
    }
]