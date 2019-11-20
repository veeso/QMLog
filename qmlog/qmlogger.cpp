/* qmlogger.cpp
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

#include "qmlogger.h"

#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QtDebug>

#define KEYWORD_DATETIME "DATETIME"
#define KEYWORD_COMPONENT "COMPONENT"
#define KEYWORD_LEVEL "LEVEL"
#define KEYWORD_MESSAGE "MESSAGE"

/**
 * @brief QMLogger::QMLogger constructor
 * @param parent
 */

QMLogger::QMLogger(QQuickItem *parent) : QQuickItem(parent) {
  this->m_toConsole = false;
  this->m_toFile = false;
  this->m_logFile = "";
  this->m_logLevel = LogLevel::INFO;
  this->m_logFormat = "";
  this->m_firstWrite = true;
}

QMLogger::~QMLogger() {

}

/**
 * @brief QMLogger::log log message to file
 * @param LogLevel level
 * @param QString component
 * @param QString msg
 */

void QMLogger::log(LogLevel level, QString component, QString msg) {
  //Check if configured log level is enabled for this log level
  if (level < m_logLevel) {
    return; //Don't log
  }
  if (m_toFile) {
    QFile logfilePtr(m_logFile);
    QIODevice::OpenModeFlag mode;
    if (m_truncate && m_firstWrite) {
      mode = QIODevice::Truncate;
      m_firstWrite = false;
    } else {
      mode = QIODevice::Append;
    }
    if (!logfilePtr.open(mode | QIODevice::WriteOnly | QIODevice::Text)) {
      logErrorSlot(LogError::WRITE_ERROR);
      return;
    }
    QString logContent;
    if (!formatLog(component, msg, level, logContent)) {
      logfilePtr.close();
      logErrorSlot(LogError::BAD_FORMAT);
      return;
    }
    logfilePtr.write(logContent.toUtf8());
    logfilePtr.write("\n");
    logfilePtr.close();
  }
  if (m_toConsole) {
    qDebug() << logContent;
  }
}

/**
 * @brief QMLogger::debug log message with debug level
 * @param QString component
 * @param QString msg
 */

void QMLogger::debug(QString component, QString msg) {
  log(LogLevel::DEBUG, component, msg);
}

/**
 * @brief QMLogger::info log message with info level
 * @param QString component
 * @param QString msg
 */

void QMLogger::info(QString component, QString msg) {
  log(LogLevel::INFO, component, msg);
}

/**
 * @brief QMLogger::warn log message with warn level
 * @param QString component
 * @param QString msg
 */

void QMLogger::warn(QString component, QString msg) {
  log(LogLevel::WARN, component, msg);
}

/**
 * @brief QMLogger::error log message with error level
 * @param QString component
 * @param QString msg
 */

void QMLogger::error(QString component, QString msg) {
  log(LogLevel::ERROR, component, msg);
}

/**
 * @brief QMLogger::critical log message with critical level
 * @param QString component
 * @param QString msg
 */

void QMLogger::critical(QString component, QString msg) {
  log(LogLevel::CRITICAL, component, msg);
}

/**
 * @brief QMLogger::formatLog format log message as indicated in logger configuration
 * @param component
 * @param message
 * @return QString the log string to write
 * NOTE: Check QMLog documentation to see which keywords are supported to format the log message
 */

bool QMLogger::formatLog(const QString& component, const QString& message, const LogLevel level, QString& log) {
  //QString timeStr = strftime()
  QDateTime tNow = QDateTime::currentDateTime();
  const std::string timeStr = tNow.toString(this->m_dateFmt).toUtf8().constData();

  log = this->m_logFormat;
  size_t startPos = 0;
  std::string logStr = log.toUtf8().constData();
  //Iterate over format to replace keywords with parts
  while ((startPos = logStr.find("${")) != std::string::npos) {
    size_t endPos = logStr.find("}");
    if (endPos < startPos || endPos == std::string::npos) {
      return false;
    }
    const size_t len = endPos - startPos;
    const std::string keyword = logStr.substr(startPos + 2, len - 2);
    if (keyword == KEYWORD_DATETIME) {
      replaceKeyword(logStr, timeStr, startPos, len);
    } else if (keyword == KEYWORD_LEVEL) {
      replaceKeyword(logStr, logLevelToStr(level).toUtf8().constData(), startPos, len);
    } else if (keyword == KEYWORD_COMPONENT) {
      replaceKeyword(logStr, component.toUtf8().constData(), startPos, len);
    } else if (keyword == KEYWORD_MESSAGE) {
      replaceKeyword(logStr, message.toUtf8().constData(), startPos, len);
    } else {
      replaceKeyword(logStr, std::string(""), startPos, len);
    }
  }

  //Convert back to QString
  log = QString::fromStdString(logStr);
  return true;
}

/**
 * @brief QMLogger::replaceKeyword
 * @param logMessage
 * @param replaceWith
 * @param startPos
 * @param endPos
 */

void QMLogger::replaceKeyword(std::string& logMessage, const std::string& replaceWith, const size_t startPos, const size_t endPos) {
  logMessage.replace(startPos, endPos + 1, replaceWith);
}

/**
 * @brief QMLogger::getErrorDesc
 * @param error
 * @return QString error description
 */

QString QMLogger::getErrorDesc(LogError error) {
  switch (error) {
  case LogError::WRITE_ERROR:
    return "Could not write to file " + this->m_logFile;
  case LogError::BAD_FORMAT:
    return "Bad log format syntax";
  }
}

/**
 * @brief QMLogger::logErrorSlot
 * @param error
 */

void QMLogger::logErrorSlot(LogError error) {
  emit logError(getErrorDesc(error));
}

/**
 * @brief QMLogger::setLogFile
 * @param logFile
 */

void QMLogger::setLogFile(QString logFile) {
  this->m_logFile = logFile;
  this->m_toFile = true;
}

/**
 * @brief QMLogger::setLogLevel
 * @param levelStr
 */

void QMLogger::setLogLevel(QString levelStr) {
  levelStr = levelStr.toUpper();
  if (levelStr == "DEBUG") {
    this->m_logLevel = LogLevel::DEBUG;
  } else if (levelStr == "INFO") {
    this->m_logLevel = LogLevel::INFO;
  } else if (levelStr == "WARN") {
    this->m_logLevel = LogLevel::WARN;
  } else if (levelStr == "ERROR") {
    this->m_logLevel = LogLevel::ERROR;
  } else if (levelStr == "CRITICAL") {
    this->m_logLevel = LogLevel::CRITICAL;
  } else {
    this->m_logLevel = LogLevel::INFO;
  }
}

/**
 * @brief QMLogger::setLogFormat
 * @param format
 */

void QMLogger::setLogFormat(QString format) {
  this->m_logFormat = format;
}

/**
 * @brief QMLogger::setDateFormat
 * @param dateFmt
 */

void QMLogger::setDateFormat(QString dateFmt) {
  this->m_dateFmt = dateFmt;
}

/**
 * @brief QMLogger::setTruncateFile
 * @param truncate
 */

void QMLogger::setTruncateFile(bool truncate) {
  this->m_truncate = truncate;
}

/**
 * @brief QMLogger::toConsole
 * @param toConsole
 */

void QMLogger::toConsole(bool toConsole) {
  this->m_toConsole = toConsole;
}

//Getters
QString QMLogger::getLogFile() {
  return m_logFile;
}

QString QMLogger::getLogFormat() {
  return m_logFormat;
}

QString QMLogger::getDateFormat() {
  return m_dateFmt;
}

QString QMLogger::logLevelToStr() {
  return logLevelToStr(m_logLevel);
}

QString QMLogger::logLevelToStr(const LogLevel level) {
  switch (level) {
  case LogLevel::DEBUG:
    return "DEBUG";
  case LogLevel::INFO:
    return "INFO";
  case LogLevel::WARN:
    return "WARN";
  case LogLevel::ERROR:
    return "ERROR";
  case LogLevel::CRITICAL:
    return "CRITICAL";
  }
}

bool QMLogger::getConsole() {
  return m_toConsole;
}

bool QMLogger::getTruncate() {
  return m_truncate;
}
