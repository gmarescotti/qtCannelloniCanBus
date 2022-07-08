#include "CannelloniCanBackend.h"

#include <QCanBusFactory>
#include <QObject>
#include <QStringList>
#include <QHostInfo>
#include <limits>

class QtCannelloniCanBusPlugin : public QObject, public QCanBusFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QCanBusFactory" FILE "plugin.json")
    Q_INTERFACES(QCanBusFactory)

public:
    QCanBusDevice* createDevice(const QString& interfaceName,
                                QString* errorMessage) const override
    {
        auto tokens = interfaceName.split(QChar(','));
        if (tokens.size() != 3)
        {
            *errorMessage = "Invalid interface name format";
            return nullptr;
        }
        bool ok;
        const auto quint16max = std::numeric_limits<quint16>::max();
        auto localPort = tokens[0].toUInt(&ok);
        if (!ok || localPort > quint16max)
        {
            *errorMessage = "Invalid local port format";
            return nullptr;
        }
        QHostAddress remoteAddr(tokens[1]);
        if (remoteAddr.isNull()) // is null could be a DNS (instead of a IPv6)
        {
            QHostInfo info = QHostInfo::fromName(tokens[1]);
            if (info.addresses().isEmpty()) {
                *errorMessage = "Invalid remote address format " + tokens[1];
                return nullptr;
            }
            for (const QHostAddress &address: info.addresses()) {
                if (address.protocol() == QAbstractSocket::IPv4Protocol) {
                    remoteAddr = address;
                    break;
                }
            }
            if (remoteAddr.isNull()) {
                *errorMessage = "Invalid remote address format " + tokens[1];
                return nullptr;
            }
        }
        auto remotePort = tokens[2].toUInt(&ok);
        if (!ok || remotePort > quint16max)
        {
            *errorMessage = "Invalid remote port format";
            return nullptr;
        }
        return new CannelloniCanBackend(localPort, remoteAddr, remotePort);
    }
};

#include "QtCannelloniCanBusPlugin.moc"
