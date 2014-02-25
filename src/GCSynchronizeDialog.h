#ifndef GCSYNCHRONIZEDIALOG_H
#define GCSYNCHRONIZEDIALOG_H
#include "GoldenCheetah.h"

#include <QtGui>
#include <QDialog>
#include <QHeaderView>
#include <QProgressBar>
#include <QMessageBox>

#include "GCUser.h"
#include "RideFile.h"
#include "MetricAggregator.h"
class Context;

class GCSynchronizeDialog : public QDialog
{
    Q_OBJECT
    G_OBJECT


    public:
        GCSynchronizeDialog(Context *context);

    protected:
        // cached state
        QSettings *settings;
        bool useMetricUnits;

    public slots:
        void loggedIn();
        void cancelClicked();
        void refreshClicked();
        void downloadClicked();
        void tabChanged(int idx);

    private:
        Context *context;

        GCUser *user;
        // tabs - Upload/Download
        QTabWidget *tabs;

        QPushButton *refreshButton;
        QPushButton *cancelButton;
        QPushButton *downloadButton;

        QDateEdit *from, *to;

        // Download
        QCheckBox *selectAll;
        QTreeWidget *rideList;

        // show progress
        QProgressBar *progressBar;
        QLabel *progressLabel;

        QCheckBox *overwrite;


        // athlete selection
        QMap<QString, QString> athlete;
        QComboBox *athleteCombo;


};


#endif // GCSYNCHRONIZEDIALOG_H
