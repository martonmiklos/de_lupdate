#include "delocalizer.h"

#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("MM");
    QCoreApplication::setApplicationName("de_lupdate");
    QCoreApplication::setApplicationVersion("1.0");

    QApplication a(argc, argv);

    QCommandLineParser cmdLine;
    cmdLine.setApplicationDescription("");
    cmdLine.addHelpOption();
    cmdLine.addVersionOption();

    QCommandLineOption tsPath(
                "ts",
                QCoreApplication::translate("main",
                                            "Path to the TS file from what the translated "
                                            "strings are going to be written back to the sources"),
                "ts");
    cmdLine.addOption(tsPath);

    QCommandLineOption proFile(
                "pro",
                QCoreApplication::translate("main", "Path to the project folder where the source "
                                                    "and ui files lives (by default it is the ts file folder)"));
    cmdLine.addOption(proFile);

    QCommandLineOption dryRun(
                "dry",
                QCoreApplication::translate("main", "Do not modify any files"));
    cmdLine.addOption(dryRun);
    if (!cmdLine.parse(QCoreApplication::arguments())) {
        qDebug() << cmdLine.errorText();
        return -1;
    }

    Delocalizer::delocalize(cmdLine.value("ts"), cmdLine.value("pro"), cmdLine.isSet("dryRun"));
    return 0;
}
