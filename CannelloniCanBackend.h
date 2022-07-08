#ifndef CANNELLONICANBACKEND_H_
#define CANNELLONICANBACKEND_H_

#include <QCanBusDevice>
#include <QUdpSocket>



//#include <sdkddkver.h>
//#define _WIN32_WINNT_WIN10_TH2 0x0A000001 // NTDDI_WIN10_TH2
//#define _WIN32_WINNT_WIN10_RS1 0x0A000002 // NTDDI_WIN10_RS1
//#define _WIN32_WINNT_WIN10_RS2 0x0A000003 // NTDDI_WIN10_RS2
//#define _WIN32_WINNT_WIN10_RS3 0x0A000004 // NTDDI_WIN10_RS3
//#define _WIN32_WINNT_WIN10_RS4 0x0A000005 // NTDDI_WIN10_RS4
//#define _WIN32_WINNT_WIN10_RS5 0x0A000006 // NTDDI_WIN10_RS5

class CannelloniCanBackend : public QCanBusDevice
{
    Q_OBJECT
public:
    CannelloniCanBackend(quint16 localPort, const QHostAddress& remoteAddr,
                         quint16 remotePort);

    bool writeFrame(const QCanBusFrame& frame) override;
    QString interpretErrorFrame(const QCanBusFrame& errorFrame) override;

protected:
    bool open() override;
    void close() override;
    void timerEvent(QTimerEvent*) override;

private:
    quint16 localPort_;
    QHostAddress remoteAddr_;
    quint16 remotePort_;
    QUdpSocket sock_;
    int timerId_;
    void handlePacket(const QByteArray& data);

private slots:
    void dataAvailable();
    // void outQueueTimer();
};

#endif /* CANNELLONICANBACKEND_H_ */
