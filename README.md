# 墨迹清单 · Qt Quick

C++ 后端 + **Qt Quick (QML)** 界面的本地待办，数据与 `todo-qt` 同逻辑，存储在 `%APPDATA%/todo-qtquick/todos.json`。

## 构建

```powershell
$env:CMAKE_PREFIX_PATH="d:\codes\soft\.qt\6.8.2\msvc2022_64"
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

运行：`build\Release\todo-qtquick.exe`
