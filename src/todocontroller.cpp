#include "todocontroller.h"

#include <QClipboard>
#include <QDate>
#include <QFile>
#include <QGuiApplication>
#include <QUrl>

static QString localPath(const QString& fileUrlOrPath) {
  const QUrl u(fileUrlOrPath);
  if (u.isValid() && u.scheme() == QLatin1String("file")) return u.toLocalFile();
  return fileUrlOrPath;
}

TodoController::TodoController(QObject* parent) : QObject(parent) {
  store_.load();
}

QString TodoController::countsLabel() const { return store_.countsLabel(); }

QString TodoController::dateTitle() const {
  const auto now = QDate::currentDate();
  static const char* wk[] = {"星期日", "星期一", "星期二", "星期三", "星期四", "星期五", "星期六"};
  const int dow = now.dayOfWeek();
  const int wi = (dow == 7) ? 0 : dow;
  return QStringLiteral("%1月%2日 %3").arg(now.month()).arg(now.day()).arg(QString::fromUtf8(wk[wi]));
}

FilterKind TodoController::filterKind() const {
  if (filter_ == QLatin1String("active")) return FilterKind::Active;
  if (filter_ == QLatin1String("done")) return FilterKind::Done;
  return FilterKind::All;
}

QVariantList TodoController::items() const {
  QVariantList list;
  const auto idx = store_.filteredIndices(filterKind());
  for (int row = 0; row < static_cast<int>(idx.size()); ++row) {
    const auto& it = store_.items()[idx[row]];
    QVariantMap m;
    m.insert(QStringLiteral("row"), row);
    m.insert(QStringLiteral("text"), it.text);
    m.insert(QStringLiteral("done"), it.done);
    list.append(m);
  }
  return list;
}

void TodoController::setFilter(const QString& f) {
  if (filter_ == f) return;
  filter_ = f;
  emit filterChanged();
  emit listChanged();
}

void TodoController::addItem(const QString& text) {
  store_.add(text);
  emit listChanged();
}

int TodoController::storeIndexForRow(int row) const {
  const auto idx = store_.filteredIndices(filterKind());
  if (row < 0 || row >= static_cast<int>(idx.size())) return -1;
  return idx[row];
}

void TodoController::toggleRow(int row) {
  const int si = storeIndexForRow(row);
  if (si < 0) return;
  const auto& it = store_.items()[si];
  store_.setDone(si, !it.done);
  emit listChanged();
}

void TodoController::removeRow(int row) {
  const int si = storeIndexForRow(row);
  if (si < 0) return;
  store_.removeAt(si);
  emit listChanged();
}

void TodoController::exportToPath(const QString& fileUrlOrPath) {
  const QString path = localPath(fileUrlOrPath);
  if (path.isEmpty()) return;
  QFile f(path);
  if (!f.open(QIODevice::WriteOnly)) {
    emit message(QStringLiteral("无法写入文件"));
    return;
  }
  f.write(store_.exportMarkdown().toUtf8());
  emit message(QStringLiteral("已导出"));
}

void TodoController::importFromPath(const QString& fileUrlOrPath) {
  const QString path = localPath(fileUrlOrPath);
  if (path.isEmpty()) return;
  if (path.endsWith(QStringLiteral(".json"), Qt::CaseInsensitive)) {
    store_.replaceFromJsonFile(path);
  } else {
    QFile f(path);
    if (!f.open(QIODevice::ReadOnly)) {
      emit message(QStringLiteral("无法读取文件"));
      return;
    }
    store_.importMarkdown(QString::fromUtf8(f.readAll()));
    store_.save();
  }
  emit listChanged();
  emit message(QStringLiteral("已导入"));
}

void TodoController::pasteFromClipboard() {
  const auto* clip = QGuiApplication::clipboard();
  if (!clip) return;
  store_.importMarkdown(clip->text());
  store_.save();
  emit listChanged();
  emit message(QStringLiteral("已从剪贴板导入"));
}
