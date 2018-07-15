#ifndef PARTICIPANT_H
#define PARTICIPANT_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QDebug>
#include <QVariant>
#include <QSqlError>
#include <QMessageBox>

namespace Core {
    class Participant
    {
    public:
        Participant();

        QString getCode() const;
        void setCode(const QString &value);

        QString getAgent() const;
        void setAgent(const QString &value);

        bool getSuppr() const;
        void setSuppr(bool value);

        bool save();
        bool update();
        bool remove();
        bool restore();
        bool Delete();
        bool Existe();
        void Clone(Participant *T);
        bool Equal(Participant*T);

    private:
        QString code;
        QString agent;
        bool Suppr;

        QSqlQuery *query;
    };
}

#endif // PARTICIPANT_H
