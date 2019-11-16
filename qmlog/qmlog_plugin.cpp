/* qmlog_plugin.cpp
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

#include "qmlog_plugin.h"
#include "qmlogger.h"

#include <qqml.h>

void QmlogPlugin::registerTypes(const char *uri)
{
    // @uri io.veeso.qmlcomponents
    qmlRegisterType<QMLogger>(uri, 0, 1, "QMLogger");
}

