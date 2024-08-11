#include "QSerializer.hpp"

#include <QCoreApplication>
#include <QString>
#include <QStringList>
#include <QDebug>

struct UserData
{
    QString name;
    int value;

    QPACK_M(UserData, name, value);
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    {
        QString v0("1234");
        QVector<int> vec0{1,2,3};
        QMap<QString, int> map0{{"key0",11},{"key1",22}};
        UserData user0{"Lili", 12};
        auto data = QPACK(v0, 1, vec0, map0, user0);

        QString v1;
        int v2;
        QVector<int> vec1;
        QMap<QString, int> map1;
        UserData user1;
        QUnPack(data, v1, v2, vec1, map1, user1);
        qDebug() << v1 << v2 << vec1 << map1 << user1.name << user1.value;
    }

    return a.exec();
}
