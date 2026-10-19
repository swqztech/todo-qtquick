# 墨迹清单 · Qt Quick

C++ 后端 + **Qt Quick (QML)** 界面的本地待办，数据与 `todo-qt` 同逻辑，存储在 `%APPDATA%/todo-qtquick/todos.json`。

## 构建

```powershell
$env:CMAKE_PREFIX_PATH="d:\codes\soft\.qt\6.8.2\msvc2022_64"
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

**不要直接双击 `build\Release` 里的 exe**（缺少 Qt DLL）。请打包后运行：

```powershell
bash packaging/build.sh
```

绿色版：`dist\墨迹清单-qtquick-0.1.0-win64-绿色版\todo-qtquick.exe`
