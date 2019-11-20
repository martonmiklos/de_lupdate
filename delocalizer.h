#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QString>
#include <QStringList>

class FileInfo
{
public:
    QString fileName;
    qint32 lineNumber;
    QStringList inFileLines;
    QStringList outFileLines;
};

class Delocalizer
{

public:
    explicit Delocalizer() {}

    bool delocalize(const QString tsFilePath, QString outProjectPath = "");
    void help();
private:
    QStringList inFileLines;
    QStringList outFileLines;

    bool replaceString(FileInfo *fileInfo, const QString & source, const QString & target, bool multiLine = false);
    int findFileInfo(QList <FileInfo*> &list, QString fileName);
};



#endif // MAINWINDOW_H
