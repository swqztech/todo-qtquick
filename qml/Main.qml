import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs

ApplicationWindow {
    id: root
    width: 560
    height: 640
    visible: true
    title: "墨迹清单 · Qt Quick"
    color: "#E8EEF6"

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 10

        Label {
            text: "墨迹清单"
            font.pixelSize: 18
            font.bold: true
            Layout.fillWidth: true
            horizontalAlignment: Text.AlignHCenter
            padding: 10
            background: Rectangle { color: "#F5F8FC"; radius: 6 }
        }

        Label {
            text: Todo.dateTitle
            font.pixelSize: 22
            font.bold: true
            color: "#4878C8"
            Layout.fillWidth: true
        }

        Label {
            text: Todo.countsLabel
            color: "#5A6A7A"
            Layout.fillWidth: true
        }

        RowLayout {
            Layout.fillWidth: true
            TextField {
                id: input
                Layout.fillWidth: true
                placeholderText: "下一件要做的事…"
                onAccepted: addBtn.clicked()
            }
            Button {
                id: addBtn
                text: "加入"
                highlighted: true
                onClicked: {
                    if (input.text.trim().length > 0) {
                        Todo.addItem(input.text)
                        input.clear()
                    }
                }
            }
        }

        RowLayout {
            spacing: 6
            Repeater {
                model: [
                    { k: "all", t: "全部" },
                    { k: "active", t: "未完成" },
                    { k: "done", t: "已完成" }
                ]
                delegate: Button {
                    text: modelData.t
                    checkable: true
                    checked: Todo.filter === modelData.k
                    onClicked: Todo.filter = modelData.k
                }
            }
            Item { Layout.fillWidth: true }
            Button { text: "导出"; onClicked: exportDialog.open() }
            Button { text: "导入"; onClicked: importDialog.open() }
            Button { text: "粘贴"; onClicked: Todo.pasteFromClipboard() }
        }

        ListView {
            id: list
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            spacing: 6
            model: Todo.items

            delegate: Rectangle {
                width: list.width
                height: 44
                radius: 6
                color: modelData.done ? "#EEF2F8" : "#FFFFFF"
                border.color: "#D2DAE6"

                RowLayout {
                    anchors.fill: parent
                    anchors.margins: 8
                    CheckBox {
                        checked: modelData.done
                        onToggled: Todo.toggleRow(modelData.row)
                    }
                    Label {
                        text: modelData.text
                        Layout.fillWidth: true
                        wrapMode: Text.Wrap
                        color: modelData.done ? "#8A96A6" : "#1E2834"
                        font.strikeout: modelData.done
                    }
                    Button {
                        text: "删除"
                        flat: true
                        onClicked: Todo.removeRow(modelData.row)
                    }
                }
            }
        }
    }

    FileDialog {
        id: exportDialog
        title: "导出 Markdown"
        fileMode: FileDialog.SaveFile
        nameFilters: ["Markdown (*.md)", "所有文件 (*)"]
        defaultFileName: "todos.md"
        onAccepted: Todo.exportToPath(selectedFile)
    }

    FileDialog {
        id: importDialog
        title: "导入"
        fileMode: FileDialog.OpenFile
        nameFilters: ["JSON (*.json)", "Markdown (*.md)", "所有文件 (*)"]
        onAccepted: Todo.importFromPath(selectedFile)
    }
}
