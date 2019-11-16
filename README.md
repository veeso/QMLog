# QMLog

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0) [![HitCount](http://hits.dwyl.io/ChristianVisintin/QMLog.svg)](http://hits.dwyl.io/ChristianVisintin/QMLog) [![Stars](https://img.shields.io/github/stars/ChristianVisintin/QMLog.svg)](https://github.com/ChristianVisintin/QMLog) [![Issues](https://img.shields.io/github/issues/ChristianVisintin/QMLog.svg)](https://github.com/ChristianVisintin/QMLog/issues) [![Build](https://api.travis-ci.org/ChristianVisintin/QMLog.svg?branch=master)](https://travis-ci.org/ChristianVisintin/QMLog)

Developed by *Christian Visintin*

Current Version 0.1.0 (16/11/2019)

---

- [QMLog](#qmlog)
  - [Introduction](#introduction)
  - [Build instructions](#build-instructions)
    - [With QtCreator](#with-qtcreator)
    - [With Qmake](#with-qmake)
  - [Implementation](#implementation)
  - [Changelog](#changelog)
  - [License](#license)

---

## Introduction

QMLog is a simple QML logging module. Its main features are:

- 5 log levels
- Custom log format
- Custom date format
- Extremely easy to use
- Possibility both to log to file and to console

## Build instructions

### With QtCreator

Using qtcreator just open qmlog project and build it, eventually install the QMLog module in your Qt directory.

### With Qmake

To build QMLog follow these steps:

1. ```cd qmlog```
2. ```mkdir build/```
3. ```qmake ..```
4. ```make```
5. ```make install```

## Implementation

Once you've installed QMLog, follow these steps to implement QMLogger in your application

1. Import QTLogger in your main file (or anywhere you want)

```qml
import QMLogger 0.1
```

2. Create a QMLogger in your Item

```qml
QMLogger {
  id: logger;
  logFile: "/tmp/qmlogger.log";
  console: true;
  logLevel: "INFO";
  dateFormat: "yyyy-MM-dd hh:mm:ss";
  logFormat: "${DATETIME} [${LEVEL}] ${COMPONENT}: ${MESSAGE}";
  truncateFile: false;
  onLogError: {
    console.log("Could not log message: ", error);
  }
}
```

- **logFile**: specify the log file location
- **console**: indicates whether to log messages to console too
- **logLevel**: indicates the log level ("DEBUG"/"INFO"/"WARN"/"ERROR"/"CRITICAL")
- **dateFormat**: Indicates the date format. The date format follows the following one <https://doc.qt.io/qt-5/qdatetime.html#toString>
- **logFormat**: The log message format. The format is made up of keywords (${}) which are replaced during the write operation. The available keywords are:
  - DATETIME: the date time string, serialized as specified in dateFormat
  - LEVEL: the log level string associated to this message
  - COMPONENT: the component which issued the log write
  - MESSAGE: the log message
- **truncateFile**: indicates whether the log file should be truncated at application start
- **onLogError**: an handler in case of log error signal is raised by the QMLogger.

3. Log content

Once you've configured your logger, from any logger's sibling item (or one of its children) you can log a message calling a log function:

```qml
logger.debug("Component foo", "This is a debug message");
logger.info("Component bar", "This is an info message");
logger.warn("Component foo", "This is a warn message");
logger.error("Component bar", "this is an error message");
logger.critical("Component foo", "This is a critical error message");
```

## Changelog

## License

Licensed under the GNU GPLv3 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at

<http://www.gnu.org/licenses/gpl-3.0.txt>

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License.

You can read the entire license [HERE](./LICENSE.txt)
