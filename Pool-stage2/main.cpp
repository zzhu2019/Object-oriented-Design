#include "mainwindow.h"
#include "simplecreator.h"
#include <QApplication>

#include <QFile>
#include <QString>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

//#define CONFIG_PATH "../Pool/config.json"
#define CONFIG_PATH "/Users/zhuzihan/Desktop/INFO3220\ Object\ Oriented\ Design/project/Pool/config_stage2.json"

int main(int argc, char *argv[])
{
	QFile conf_file(CONFIG_PATH);
    conf_file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString content = conf_file.readAll();
    conf_file.close();

    QJsonObject config = QJsonDocument::fromJson(content.toUtf8()).object();//config the file content

	QApplication a(argc, argv);
    MainWindow w(SimpleCreator().makeScene(config));//to create the window and render
    w.show();
	return a.exec();
}
