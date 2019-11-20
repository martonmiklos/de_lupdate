// This file is generated by kxml_compiler from TS.xsd.
// All changes you do to this file will be lost.
#ifndef TS_H
#define TS_H

#include <QString>
#include <QDomElement>
#include <QList>

class Translation
{
  public:
    Translation();
    Translation( const QString &v );
    void setValue( const QString &v );
    QString value() const;
    bool valueHadBeenSet() const;
    void setElementIsOptional( const bool &v );
    bool elementIsOptional() const;
    /**
      Parse XML object from DOM element.
     */
    static Translation parseElement( const QDomElement &element, bool *ok );

  private:
    QString mValue;
    bool mValueHadBeenSet;
    bool mElementIsOptional;
};

class Source
{
  public:
    Source();
    Source( const QString &v );
    void setValue( const QString &v );
    QString value() const;
    bool valueHadBeenSet() const;
    void setElementIsOptional( const bool &v );
    bool elementIsOptional() const;
    /**
      Parse XML object from DOM element.
     */
    static Source parseElement( const QDomElement &element, bool *ok );

  private:
    QString mValue;
    bool mValueHadBeenSet;
    bool mElementIsOptional;
};

class Location
{
  public:
    typedef QList<Location> List;

  public:
    Location();
    void setFilename( const QString &v );
    QString filename() const;
    void setLine( const qint32 &v );
    qint32 line() const;
    bool valueHadBeenSet() const;
    void setElementIsOptional( const bool &v );
    bool elementIsOptional() const;
    /**
      Parse XML object from DOM element.
     */
    static Location parseElement( const QDomElement &element, bool *ok );

  private:
    QString mFilename;
    qint32 mLine;
    bool mValueHadBeenSet;
    bool mElementIsOptional;
};

class Message
{
  public:
    typedef QList<Message> List;

  public:
    Message();
    void addLocation( const Location &v );
    void setLocationList( const Location::List &v );
    Location::List locationList() const;
    void setSource( const Source &v );
    Source source() const;
    void setTranslation( const Translation &v );
    Translation translation() const;
    bool valueHadBeenSet() const;
    void setElementIsOptional( const bool &v );
    bool elementIsOptional() const;
    /**
      Parse XML object from DOM element.
     */
    static Message parseElement( const QDomElement &element, bool *ok );

  private:
    Location::List mLocationList;
    Source mSource;
    Translation mTranslation;
    bool mValueHadBeenSet;
    bool mElementIsOptional;
};

class Name
{
  public:
    Name();
    Name( const QString &v );
    void setValue( const QString &v );
    QString value() const;
    bool valueHadBeenSet() const;
    void setElementIsOptional( const bool &v );
    bool elementIsOptional() const;
    /**
      Parse XML object from DOM element.
     */
    static Name parseElement( const QDomElement &element, bool *ok );

  private:
    QString mValue;
    bool mValueHadBeenSet;
    bool mElementIsOptional;
};

class Context
{
  public:
    typedef QList<Context> List;

  public:
    Context();
    void setName( const Name &v );
    Name name() const;
    void addMessage( const Message &v );
    void setMessageList( const Message::List &v );
    Message::List messageList() const;
    bool valueHadBeenSet() const;
    void setElementIsOptional( const bool &v );
    bool elementIsOptional() const;
    /**
      Parse XML object from DOM element.
     */
    static Context parseElement( const QDomElement &element, bool *ok );

  private:
    Name mName;
    Message::List mMessageList;
    bool mValueHadBeenSet;
    bool mElementIsOptional;
};

class TS
{
  public:
    TS();
    void setVersion( const double &v );
    double version() const;
    void setLanguage( const QString &v );
    QString language() const;
    void addContext( const Context &v );
    void setContextList( const Context::List &v );
    Context::List contextList() const;
    bool valueHadBeenSet() const;
    void setElementIsOptional( const bool &v );
    bool elementIsOptional() const;
    /**
      Parse XML object from DOM element.
     */
    static TS parseElement( const QDomElement &element, bool *ok );
    static TS parseFile( const QString &filename, bool *ok );
    static TS parseString( const QString &xml, bool *ok );

  private:
    double mVersion;
    QString mLanguage;
    Context::List mContextList;
    bool mValueHadBeenSet;
    bool mElementIsOptional;
};

#endif