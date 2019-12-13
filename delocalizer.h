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
    static bool delocalize(const QString & tsFilePath, const QString & projectPath = QString(), bool dryRun = false);

private:
    static bool replaceString(FileInfo *fileInfo, const QString & source, const QString & target, bool multiLine = false);
    static int findFileInfo(QList <FileInfo*> &list, QString fileName);
};



#endif // MAINWINDOW_H
