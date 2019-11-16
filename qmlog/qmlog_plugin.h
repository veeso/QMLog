/* qmlog_plugin.h
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

#ifndef QMLOG_PLUGIN_H
#define QMLOG_PLUGIN_H

#include <QQmlExtensionPlugin>

class QmlogPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    void registerTypes(const char *uri) override;
};

#endif // QMLOG_PLUGIN_H
