/****************************************************************************
**
** Copyright (C) 2020 Manfred Kern. All rights reserved.
** Contact: manfred.kern@gmail.com
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are met:
**
** 1. Redistributions of source code must retain the above copyright notice,
**    this list of conditions and the following disclaimer.
**
** 2. Redistributions in binary form must reproduce the above copyright
**    notice, this list of conditions and the following disclaimer in the
**    documentation and/or other materials provided with the distribution.
**
** 3. All advertising materials mentioning features or use of this software
**    must display the following acknowledgement:
**    This product includes software developed by the the organization.
**
** 4. Neither the name of the copyright holder nor the names of its
**    contributors may be used to endorse or promote products derived from
**    this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
****************************************************************************/
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QQmlContext>
#include <QQmlComponent>
#include <QQuickItem>
#include <QDebug>

#include "controller.h"

#include "garminlistmodel.h"
#include "garmintreemodel.h"

int main(int argc, char* argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    // define App ...
    app.setApplicationName("AnalyzeGPX");
    app.setApplicationVersion("0.0.5");
    app.setOrganizationName("private");
    app.setOrganizationDomain("org");

    // qmlRegisterUncreatableType not needed, only for the sake of completeness
    qmlRegisterUncreatableType<GarminListModel>("GarminListModel",
                                                1, 0,
                                                "GarminListModel",
                                                "This is a model, which should not be instantiated");
    qmlRegisterUncreatableType<GarminTreeModel>("GarminTreeModel",
                                                1, 0,
                                                "GarminTreeModel",
                                                "This is a model, which should not be instantiated");


    // MVC: Connect controller and model
    Controller controller;
    GarminListModel* garminListModel = &(controller.garminListModel());
    GarminTreeModel* garminTreeModel = &(controller.garminTreeModel());

    QQmlApplicationEngine engine;
//    const QUrl url(QStringLiteral("qrc:/Ui/main.qml"));
    const QUrl url(QStringLiteral("qrc:/Ui/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
    &app, [url](QObject * obj, const QUrl & objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    // MVC: Connect to the view
    // Sets (Binds) the ListModel for tracks, routes and waypoints
    QQmlContext* ctxt = engine.rootContext();

    ctxt->setContextProperty(QStringLiteral("garminListModel"), garminListModel);
    ctxt->setContextProperty(QStringLiteral("garminTreeModel"), garminTreeModel);
    ctxt->setContextProperty("controller", &controller);

    engine.load(url);

    return app.exec();
}
