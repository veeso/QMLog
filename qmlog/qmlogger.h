/* qmlogger.h
*
* 	Copyright (C) 2019 Christian Visintin - christian.visintin1997@gmail.com
*
* 	This file is part of "QMLog"
*
*   QMLog is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   QMLog is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with QMLog.  If not, see <http://www.gnu.org/licenses/>.
*
*/

#ifndef QMLOGGER_H
#define QMLOGGER_H

#include <QQuickItem>
#include <QObject>
#include <QString>

enum class LogLevel {
  DEBUG,
  INFO,
  WARN,
  ERROR,
  CRITICAL
};

enum class LogError {
  WRITE_ERROR,
  BAD_FORMAT
};

class QMLogger : public QQuickItem {
  Q_OBJECT
  Q_DISABLE_COPY(QMLogger)

  //Properties
  Q_PROPERTY(QString logLevel READ logLevelToStr WRITE setLogLevel)
  Q_PROPERTY(QString logFile READ getLogFile WRITE setLogFile)
  Q_PROPERTY(QString logFormat READ getLogFormat WRITE setLogFormat)
  Q_PROPERTY(QString dateFormat READ getDateFormat WRITE setDateFormat)
  Q_PROPERTY(bool console READ getConsole WRITE toConsole)
  Q_PROPERTY(bool truncateFile READ getTruncate WRITE setTruncateFile)

signals:
  void logError(QString error);

public:
  explicit QMLogger(QQuickItem *parent = nullptr);
  ~QMLogger() override;
  //Logging Methods
  void log(LogLevel level, QString component, QString msg);
  Q_INVOKABLE void debug(QString component, QString msg);
  Q_INVOKABLE void info(QString component, QString msg);
  Q_INVOKABLE void warn(QString component, QString msg);
  Q_INVOKABLE void error(QString component, QString msg);
  Q_INVOKABLE void critical(QString component, QString msg);
  //Q_PROPERTY READ Methods
  QString logLevelToStr();
  QString logLevelToStr(const LogLevel level);
  QString getLogFile();
  QString getLogFormat();
  QString getDateFormat();
  bool getConsole();
  bool getTruncate();
  //Q_PROPERTY WRITE Methods
  void setLogLevel(QString levelStr);
  void setLogFile(QString logFile);
  void toConsole(bool toConsole);
  void setLogFormat(QString format);
  void setDateFormat(QString dateFmt);
  void setTruncateFile(bool truncate);

  //Signals
  void logErrorSlot(LogError error);

private:
  QString getErrorDesc(LogError error);
  bool formatLog(const QString& component, const QString& message, const LogLevel level, QString& log);
  void replaceKeyword(std::string& logMessage, const std::string& replaceWith, const size_t startPos, const size_t endPos);

  LogLevel m_logLevel;
  QString m_logFile;
  QString m_logFormat;
  QString m_dateFmt;
  bool m_toConsole;
  bool m_toFile;
  bool m_truncate;
  bool m_firstWrite;

};

#endif // QMLOGGER_Hlo
