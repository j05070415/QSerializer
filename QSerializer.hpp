#ifndef QSERIALIZER_H
#define QSERIALIZER_H

#include <QDataStream>
#include <QByteArray>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

#define STREAM_O <<
#define STREAM_I >>
#define P_PACK_EXPAND(...) __VA_ARGS__
#define P_PACK_COUNT(LEVEL, _10,_9,_8,_7,_6,_5,_4,_3,_2,_1,N,...) LEVEL##N
#define P_PACK_N(LEVEL,ACTION, ...) P_PACK_EXPAND(P_PACK_COUNT(LEVEL, __VA_ARGS__,_10,_9,_8,_7,_6,_5,_4,_3,_2,_1))P_PACK_EXPAND((ACTION, __VA_ARGS__))

/************************一般序列化和反序列化*********************/
#ifdef _WIN32
#define P_PACK(ACTION, ...) P_PACK_N(PSTREAM, ACTION, __VA_ARGS__)
#define PSTREAM_1(ACTION,  A)      ACTION A
#define PSTREAM_2(ACTION,  A, ...) ACTION A P_PACK_EXPAND(PSTREAM_1(ACTION, __VA_ARGS__))
#define PSTREAM_3(ACTION,  A, ...) ACTION A P_PACK_EXPAND(PSTREAM_2(ACTION, __VA_ARGS__))
#define PSTREAM_4(ACTION,  A, ...) ACTION A P_PACK_EXPAND(PSTREAM_3(ACTION, __VA_ARGS__))
#define PSTREAM_5(ACTION,  A, ...) ACTION A P_PACK_EXPAND(PSTREAM_4(ACTION, __VA_ARGS__))
#define PSTREAM_6(ACTION,  A, ...) ACTION A P_PACK_EXPAND(PSTREAM_5(ACTION, __VA_ARGS__))
#define PSTREAM_7(ACTION,  A, ...) ACTION A P_PACK_EXPAND(PSTREAM_6(ACTION, __VA_ARGS__))
#define PSTREAM_8(ACTION,  A, ...) ACTION A P_PACK_EXPAND(PSTREAM_7(ACTION, __VA_ARGS__))
#define PSTREAM_9(ACTION,  A, ...) ACTION A P_PACK_EXPAND(PSTREAM_8(ACTION, __VA_ARGS__))
#define PSTREAM_10(ACTION, A, ...) ACTION A P_PACK_EXPAND(PSTREAM_9(ACTION, __VA_ARGS__))
#elif defined(__linux__)
#define P_PACK(ACTION, ...) P_PACK_EXPAND(P_PACK_N(PSTREAM, ACTION, __VA_ARGS__))
#define PSTREAM_1(ACTION,  A)      ACTION A
#define PSTREAM_2(ACTION,  A, ...) ACTION A PSTREAM_1(ACTION, __VA_ARGS__)
#define PSTREAM_3(ACTION,  A, ...) ACTION A PSTREAM_2(ACTION, __VA_ARGS__)
#define PSTREAM_4(ACTION,  A, ...) ACTION A PSTREAM_3(ACTION, __VA_ARGS__)
#define PSTREAM_5(ACTION,  A, ...) ACTION A PSTREAM_4(ACTION, __VA_ARGS__)
#define PSTREAM_6(ACTION,  A, ...) ACTION A PSTREAM_5(ACTION, __VA_ARGS__)
#define PSTREAM_7(ACTION,  A, ...) ACTION A PSTREAM_6(ACTION, __VA_ARGS__)
#define PSTREAM_8(ACTION,  A, ...) ACTION A PSTREAM_7(ACTION, __VA_ARGS__)
#define PSTREAM_9(ACTION,  A, ...) ACTION A PSTREAM_8(ACTION, __VA_ARGS__)
#define PSTREAM_10(ACTION, A, ...) ACTION A PSTREAM_9(ACTION, __VA_ARGS__)
#endif

#define QPACK1(...) \
    [&] { \
        QByteArray buff; \
        QDataStream ds(&buff, QIODevice::WriteOnly); \
        ds P_PACK_EXPAND(P_PACK(STREAM_O, __VA_ARGS__)); \
        return buff; \
    }();

#define QPACK(data, ...) \
    [&] { \
        QDataStream ds(&data, QIODevice::WriteOnly); \
        ds P_PACK_EXPAND(P_PACK(STREAM_O, __VA_ARGS__)); \
    }();

//data是被序列化的数据，类型为QByteArray
#define QUNPACK(data, ...) \
    { \
        QDataStream ds(data); \
        ds P_PACK_EXPAND(P_PACK(STREAM_I, __VA_ARGS__)); \
    };

/************************类或结构体序列化*********************/
#ifdef _WIN32
#define P_PACK_M(ACTION, ...) P_PACK_N(PSTREAM_M, ACTION, __VA_ARGS__)
#define PSTREAM_M_1(ACTION,  A)      ACTION d.##A
#define PSTREAM_M_2(ACTION,  A, ...) ACTION d.##A P_PACK_EXPAND(PSTREAM_M_1(ACTION, __VA_ARGS__))
#define PSTREAM_M_3(ACTION,  A, ...) ACTION d.##A P_PACK_EXPAND(PSTREAM_M_2(ACTION, __VA_ARGS__))
#define PSTREAM_M_4(ACTION,  A, ...) ACTION d.##A P_PACK_EXPAND(PSTREAM_M_3(ACTION, __VA_ARGS__))
#define PSTREAM_M_5(ACTION,  A, ...) ACTION d.##A P_PACK_EXPAND(PSTREAM_M_4(ACTION, __VA_ARGS__))
#define PSTREAM_M_6(ACTION,  A, ...) ACTION d.##A P_PACK_EXPAND(PSTREAM_M_5(ACTION, __VA_ARGS__))
#define PSTREAM_M_7(ACTION,  A, ...) ACTION d.##A P_PACK_EXPAND(PSTREAM_M_6(ACTION, __VA_ARGS__))
#define PSTREAM_M_8(ACTION,  A, ...) ACTION d.##A P_PACK_EXPAND(PSTREAM_M_7(ACTION, __VA_ARGS__))
#define PSTREAM_M_9(ACTION,  A, ...) ACTION d.##A P_PACK_EXPAND(PSTREAM_M_8(ACTION, __VA_ARGS__))
#define PSTREAM_M_10(ACTION, A, ...) ACTION d.##A P_PACK_EXPAND(PSTREAM_M_9(ACTION, __VA_ARGS__))
#elif defined(__linux__)
#define P_PACK_M(ACTION, ...) P_PACK_EXPAND(P_PACK_N(PSTREAM_M, ACTION, __VA_ARGS__))
#define PSTREAM_M_1(ACTION,  A)      ACTION d.##A
#define PSTREAM_M_2(ACTION,  A, ...) ACTION d.##A PSTREAM_M_1(ACTION, __VA_ARGS__)
#define PSTREAM_M_3(ACTION,  A, ...) ACTION d.##A PSTREAM_M_2(ACTION, __VA_ARGS__)
#define PSTREAM_M_4(ACTION,  A, ...) ACTION d.##A PSTREAM_M_3(ACTION, __VA_ARGS__)
#define PSTREAM_M_5(ACTION,  A, ...) ACTION d.##A PSTREAM_M_4(ACTION, __VA_ARGS__)
#define PSTREAM_M_6(ACTION,  A, ...) ACTION d.##A PSTREAM_M_5(ACTION, __VA_ARGS__)
#define PSTREAM_M_7(ACTION,  A, ...) ACTION d.##A PSTREAM_M_6(ACTION, __VA_ARGS__)
#define PSTREAM_M_8(ACTION,  A, ...) ACTION d.##A PSTREAM_M_7(ACTION, __VA_ARGS__)
#define PSTREAM_M_9(ACTION,  A, ...) ACTION d.##A PSTREAM_M_8(ACTION, __VA_ARGS__)
#define PSTREAM_M_10(ACTION, A, ...) ACTION d.##A PSTREAM_M_9(ACTION, __VA_ARGS__)
#endif

#define QPACK_M(T, ...)\
friend QDataStream& operator<< (QDataStream& stream, const T& d)\
{\
    stream P_PACK_EXPAND(P_PACK_M(STREAM_O, __VA_ARGS__));\
    return stream;\
}\
\
friend QDataStream& operator>> (QDataStream& stream, T& d)\
{\
    stream P_PACK_EXPAND(P_PACK_M(STREAM_I, __VA_ARGS__));\
    return stream;\
}

#if defined (QJSON_SERIALIZE)
QDataStream& operator>>(QDataStream &in, QJsonObject& obj)
{
    QByteArray data;
    in >> data;
    auto value = QJsonDocument::fromJson(data).object();
    obj = std::move(value);
    return in;
}

QDataStream& operator<<(QDataStream &in, const QJsonObject& obj)
{
    auto data = QJsonDocument(obj).toJson();
    in << data;
    return in;
}

QDataStream& operator>>(QDataStream &in, QJsonArray& obj)
{
    QByteArray data;
    in >> data;
    auto value = QJsonDocument::fromJson(data).array();
    obj = std::move(value);
    return in;
}

QDataStream& operator<<(QDataStream &in, const QJsonArray& obj)
{
    auto data = QJsonDocument(obj).toJson();
    in << data;
    return in;
}
#endif

#endif //QSERIALIZER_H
