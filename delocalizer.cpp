#include "delocalizer.h"
#include "TS.h"

#include <QDebug>
#include <QFileInfo>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QTextDocument>


int Delocalizer::findFileInfo(QList<FileInfo *> &list, QString fileName)
{
    for (int i = 0; i<list.size(); i++) {
        if (list.at(i)->fileName == fileName)
            return i;
    }
    return -1;
}

bool Delocalizer::delocalize(const QString tsFilePath, QString outProjectPath)
{
    TS ts;
    bool ok = false;
    QFileInfo fi(tsFilePath);
    ts = ts.parseFile(tsFilePath, &ok);

    // if no outProjectPath use the folder where the TS file is.
    if (outProjectPath.isEmpty())
        outProjectPath = fi.path();

    QList <FileInfo*> outFiles;
    FileInfo *currentFileInfo = NULL;
    QString lastMessageFirstFileName = "";
    for (int i = 0; i<ts.contextList().count(); i++) {
        Context c = ts.contextList().at(i);
        foreach (Message msg, c.messageList()) {
            int locCounter = 0;
            foreach (Location l, msg.locationList()) {
                QString fileName = "";
                if (!l.filename().isEmpty()) {
                    // fileName not empty
                    int infoIndex = findFileInfo(outFiles, l.filename());
                    if (infoIndex == -1) {
                        currentFileInfo = new FileInfo;
                        currentFileInfo->fileName = l.filename();
                        currentFileInfo->lineNumber = -1;
                        outFiles.append(currentFileInfo);

                        QFile inFile;
                        inFile.setFileName(fi.path() + QDir::separator() + l.filename());

                        if (!inFile.open(QFile::ReadOnly)) {
                            qWarning() << "Unable to open " << inFile.fileName() << " for read";
                            return false;
                        }

                        QTextStream textStream(&inFile);
                        while (true) {
                            QString line = textStream.readLine();
                            if (line.isNull()) {
                                break;
                            } else {
                                currentFileInfo->inFileLines.append(line);
                                currentFileInfo->outFileLines.append(line);
                            }
                        }
                        inFile.close();
                        if (locCounter == 0)
                            lastMessageFirstFileName = l.filename();
                    } else {
                        currentFileInfo = outFiles[infoIndex];
                    }

                    if (locCounter == 0) {
                        lastMessageFirstFileName = l.filename();
                    }
                } else if (l.filename().isEmpty() && locCounter == 0) {
                    int infoIndex = findFileInfo(outFiles, lastMessageFirstFileName);
                    if (infoIndex == -1) {
                        qWarning() << "lastMessageFirstFileName invalid";
                        return false;
                    }
                    currentFileInfo = outFiles[infoIndex];
                }

                currentFileInfo->lineNumber += l.line(); // line is going to be 0 if not present at the attributes

                if (!msg.translation().value().isEmpty() && !msg.source().value().isEmpty()) {
                    // translated message replace back
                    if (currentFileInfo->lineNumber < currentFileInfo->inFileLines.count()) {
                        if (msg.source().value().contains('\n')) {
                            QStringList sources = msg.source().value().split('\n');
                            QStringList targets = msg.translation().value().split('\n');
                            for (int i = 0; i<sources.size(); i++) {
                                QString targetLine = "";
                                if (i < targets.size()) {
                                    targetLine = targets.at(i);
                                } else {
                                    qWarning() << "the translation and the source has different line count!";
                                }
                                if (!replaceString(currentFileInfo, sources.at(i), targetLine, true))
                                    return false;
                            }
                        } else {
                            if (!replaceString(currentFileInfo, msg.source().value(), msg.translation().value()))
                                return false;
                        }
                    } else {
                        qWarning() << "lineIndex" << currentFileInfo->lineNumber << "is out of range! Run lupdate on the project!";
                        return false;
                    }
                }
                locCounter++;
            }
        }
    }

    foreach (FileInfo *info, outFiles) {
        QFile outFile(outProjectPath + QDir::separator() + info->fileName);
        qWarning() << "writing" << outFile.fileName();
        if (!outFile.open(QFile::WriteOnly))  {
            qWarning() << "Unable to open " << outFile.fileName() << " for write";
            return false;
        }

        QTextStream out(&outFile);
        for ( QStringList::Iterator it = info->outFileLines.begin(); it != info->outFileLines.end(); ++it )
            out << *it << "\n";

        outFile.close();
        qWarning() << "DONE";
    }

    return true;
}

void Delocalizer::help()
{
    qWarning() << "\tde_lupdate\n"
                  "\twritten by Miklos Marton <martonmiklosqdev [at] gmail {dot} com>\n"
                  "\n"
                  "\tAn utility to change push back the localized strings\n"
                  "\tfrom a TS file to a source and ui codebase\n"
                  "\n"
                  "\tUsage:\n"
                  "\tArguments:"
                  "\t-ts : path to the ts file"
                  "\t-proj : path to the project containing the codebase (optional)\n"
                  "\t        the ts file folder is going to be used if left exist\n"
                  "\t-h: ; displays this help";
}

bool Delocalizer::replaceString(FileInfo *fileInfo, const QString &source, const QString &target, bool multiLine)
{
    /*
     * TODO the current implementation does not check the presence of the macros
     * in the target line.
        Q_DECLARE_TR_FUNCTIONS
        QT_TR_NOOP
        QT_TRID_NOOP
        QT_TRANSLATE_NOOP
        QT_TRANSLATE_NOOP3
        QT_TR_NOOP_UTF8
        QT_TRANSLATE_NOOP_UTF8
        QT_TRANSLATE_NOOP3_UTF8
        findMessage
        qtTrId
        tr
        trUtf8
        translate
        qsTr
        qsTrId
        qsTranslate
     * Ugly hack but works most cases.
     */
    int lineNumber = fileInfo->lineNumber;
    int maxRowCount = 10;

    QString sourceModified = source;
    QString targetModified = target;
    if (fileInfo->fileName.right(3).toLower() == ".ui") {
        maxRowCount = 1; // ui files are generated no extra LF shall be present
        if (multiLine) {
            sourceModified = source.toHtmlEscaped();
            targetModified = target.toHtmlEscaped();
        } else {
            sourceModified = ">" + source.toHtmlEscaped() + "<";
            targetModified = ">" + target.toHtmlEscaped() + "<";
        }
    } else {
        if (!multiLine) {
            sourceModified = "\"" + source + "\"";
            targetModified = "\"" + target + "\"";
        }
    }

    while (maxRowCount) {
        QString inLine = fileInfo->inFileLines.at(lineNumber);
        if (inLine.contains(sourceModified)) {
            fileInfo->outFileLines[lineNumber] = inLine.replace(sourceModified, targetModified);
            qWarning() << "\nSRC: ";
            qWarning() << fileInfo->inFileLines[lineNumber].trimmed();
            qWarning() << fileInfo->outFileLines[lineNumber].trimmed();
            return true;
        }
        lineNumber++;
        maxRowCount--;
    }
    qWarning() << "unable to find the " << sourceModified << "string in the " << fileInfo->fileName <<
                  " file between lines " << fileInfo->lineNumber << " and " << lineNumber;
    return false;
}
