/*
 * Copyright (c) 2013 Mark Liversedge (liversedge@gmail.com)
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRWFApiY; without even the implied warranty of MERCHWFApiABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc., 51
 * Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef gc_WFApi_h
#define gc_WFApi_h

// GC 
#include "GoldenCheetah.h"
#include "Settings.h"
#include "RealtimeData.h"
#include "DeviceConfiguration.h"
#include "RealtimeData.h"

// QT
#include <QPointer>
#include <QObject>

// global singleton
class WFApi;
extern WFApi *_gc_wfapi;

// declare the provate implementation for objc
#ifdef __OBJC__
@class WFBridge;
#else
// irritating dependencies
#endif

class WFApi : public QObject // QOBject for signals
{
   Q_OBJECT

public:
    WFApi(); // single instance
    ~WFApi();

    static WFApi *getInstance() { if (_gc_wfapi) return _gc_wfapi;
                                  else return (_gc_wfapi = new WFApi); } // singleton

    // what version?
    QString apiVersion();

    // status of BTLE
    bool hasBTLESupport();
    bool isBTLEEnabled();
    bool enableBTLE(bool enable, bool bondingmode);
    bool isCommunicationHWReady();

    // current state
    typedef enum {
        WFAPI_HWCONN_STATE_NOT_CONNECTED                = 0,
        WFAPI_HWCONN_STATE_CONNECTED                    = 0x01,
        WFAPI_HWCONN_STATE_ACTIVE                       = 0x02,
        WFAPI_HWCONN_STATE_RESET                        = 0x04,
        WFAPI_HWCONN_STATE_BT40_ENABLED                 = 0x08,
        WFAPI_HWCONN_STATE_BT_BONDING_MODE              = 0x10 };
    int currentState();

    // connection state
    typedef enum {
    WF_SENSOR_CONNECTION_STATUS_IDLE = 0,
    WF_SENSOR_CONNECTION_STATUS_CONNECTING = 1,
    WF_SENSOR_CONNECTION_STATUS_CONNECTED = 2,
    WF_SENSOR_CONNECTION_STATUS_INTERRUPTED = 3,
    WF_SENSOR_CONNECTION_STATUS_DISCONNECTING = 4 };
    int connectionStatus();
    bool isConnected();

    // scan
    bool discoverDevicesOfType(int eSensorType, int eNetworkType, int timeout);
    int deviceCount();
    QString deviceUUID(int); // return the UUID for device n

    // connect and disconnect
    bool connectDevice(QString uuid); // connect the device n
    bool disconnectDevice();   // disconnect

    // has data?
    bool hasData();
    void getRealtimeData(RealtimeData *p);

    // set slope or ergo mode
    void setSlopeMode();
    void setErgoMode();

    // set resistance slope or load
    void setSlope(double slope);
    void setLoad(int watts);

    // NOTE: There is an application wide NSAutoreleasePool maintained
    //       in cocoa initialiser, but it is only to support activity on
    //       the main thread.
    //       The application code (e.g. Kickr.cpp) needs to get and free a
    //       pool for each thread, this is why we have a getPool/freePool
    //       method in WFApi, but never allocate a pool ourselves.
    void *getPool();
    void freePool(void*);

signals:
    void currentStateChanged(int); // hardware conncector state changed
    void connectionStateChanged(int status);
    int discoveredDevices(int,bool);
    void connectionHasData();

public slots:

    // connecting...
    void stateChanged();
    void connectionState(int status);
    void connectionTimeout();

    void connectedSensor(void*);
    void didDiscoverDevices(int count, bool finished);
    void disconnectedSensor(void*);
    void hasFirmwareUpdateAvalableForConnection();
    void connectorHasData();

signals:

public slots:

public:

    // the native api bridge -- private implementation in
    // WFApi.mm -- bridge between the QT/C++ world and the
    // WF/Objc world
#ifdef __OBJC__
    WFBridge *wf; // when included in objc sources
#else /* __OBJC__ */
    void *wf;       // when included in C++ sources
#endif /* __OBJC__ */
};

//
// We need to define the constants from the WF API headers because they
// assume you are building with OBJ C. And fail to compile with gcc/g++
//


#endif