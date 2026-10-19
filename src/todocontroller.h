#pragma once

#include "todostore.h"

#include <QObject>
#include <QVariantList>

class TodoController : public QObject {
  Q_OBJECT
  Q_PROPERTY(QString countsLabel READ countsLabel NOTIFY listChanged)
  Q_PROPERTY(QString dateTitle READ dateTitle CONSTANT)
  Q_PROPERTY(QVariantList items READ items NOTIFY listChanged)
  Q_PROPERTY(QString filter READ filter WRITE setFilter NOTIFY filterChanged)

 public:
  explicit TodoController(QObject* parent = nullptr);

  QString countsLabel() const;
  QString dateTitle() const;
  QVariantList items() const;
  QString filter() const { return filter_; }
  void setFilter(const QString& f);

  Q_INVOKABLE void addItem(const QString& text);
  Q_INVOKABLE void toggleRow(int row);
  Q_INVOKABLE void removeRow(int row);
  Q_INVOKABLE void exportToPath(const QString& fileUrlOrPath);
  Q_INVOKABLE void importFromPath(const QString& fileUrlOrPath);
  Q_INVOKABLE void pasteFromClipboard();

 signals:
  void listChanged();
  void filterChanged();
  void message(const QString& text);

 private:
  FilterKind filterKind() const;
  int storeIndexForRow(int row) const;

  TodoStore store_;
  QString filter_ = QStringLiteral("all");
};
