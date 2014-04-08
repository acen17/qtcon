/****************************************************************************
**
** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtBluetooth module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtCore/QGlobalStatic>
#include <QtCore/QLoggingCategory>
#include "bluez5_helper_p.h"
#include "objectmanager_p.h"

QT_BEGIN_NAMESPACE

Q_DECLARE_LOGGING_CATEGORY(QT_BT_BLUEZ)

typedef enum Bluez5TestResultType
{
    Unknown,
    Bluez4,
    Bluez5
} Bluez5TestResult;

Q_GLOBAL_STATIC_WITH_ARGS(Bluez5TestResult, bluezVersion, (Bluez5TestResult::Unknown));

bool isBluez5()
{
    if (*bluezVersion() == Bluez5TestResultType::Unknown) {
        OrgFreedesktopDBusObjectManagerInterface manager(QStringLiteral("org.bluez"),
                                                         QStringLiteral("/"),
                                                         QDBusConnection::systemBus());

        qDBusRegisterMetaType<InterfaceList>();
        qDBusRegisterMetaType<ManagedObjectList>();

        QDBusPendingReply<ManagedObjectList> reply = manager.GetManagedObjects();
        reply.waitForFinished();
        if (reply.isError()) {
            *bluezVersion() = Bluez5TestResultType::Bluez4;
            qCDebug(QT_BT_BLUEZ) << "Bluez 4 detected.";
        } else {
            *bluezVersion() = Bluez5TestResultType::Bluez5;
            qCDebug(QT_BT_BLUEZ) << "Bluez 5 detected.";
        }
    }

    return (*bluezVersion() == Bluez5TestResultType::Bluez5);
}

QT_END_NAMESPACE
