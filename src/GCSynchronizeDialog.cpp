/*
 * Copyright (c) 2010 Mark Liversedge (liversedge@gmail.com)
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc., 51
 * Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */
#include "GCSynchronizeDialog.h"
#include "GCUser.h"
#include "MainWindow.h"
#include "Context.h"
#include "Athlete.h"
#include "PwxRideFile.h"
#include "JsonRideFile.h"
#include "RideFile.h"
#include "Settings.h"
#include "MetricAggregator.h"
#include "Units.h"

GCSynchronizeDialog::GCSynchronizeDialog(Context *context) : QDialog(context->mainWindow, Qt::Dialog), context(context)
{
    setWindowTitle(tr("Synchronize with Garmin Connect"));

    user = new GCUser(this);
    //connect (user, SIGNAL(completed()), this, SLOT(loggedIn()));
    //QWidget::hide(); // don't show just yet...
    loggedIn();
}

void GCSynchronizeDialog::loggedIn()
{
    // setup tabs
    tabs = new QTabWidget(this);
    QWidget * download = new QWidget(this);
    tabs->addTab(download, tr("Download"));
    QVBoxLayout *downloadLayout = new QVBoxLayout(download);


    QLabel *fromLabel = new QLabel(tr("From:"), this);
    QLabel *toLabel = new QLabel(tr("To:"), this);

    from = new QDateEdit(this);
    from->setDate(QDate::currentDate().addMonths(-1));
    from->setCalendarPopup(true);
    to = new QDateEdit(this);
    to->setDate(QDate::currentDate());
    to->setCalendarPopup(true);

    // Buttons
    refreshButton = new QPushButton(tr("Refresh Ride List"), this);
    cancelButton = new QPushButton(tr("Close"),this);
    downloadButton = new QPushButton(tr("Download"),this);

    selectAll = new QCheckBox(tr("Select all"), this);
    selectAll->setChecked(Qt::Unchecked);

    // ride list
    rideList = new QTreeWidget(this);
    rideList->headerItem()->setText(0, " ");
    rideList->headerItem()->setText(1, "Workout Id");
    rideList->headerItem()->setText(2, "Date");
    rideList->headerItem()->setText(3, "Time");
    rideList->headerItem()->setText(4, "Duration");
    rideList->headerItem()->setText(5, "Distance");
    rideList->headerItem()->setText(6, "Exists");
    rideList->headerItem()->setText(7, "Status");
    rideList->setColumnCount(8);
    rideList->setSelectionMode(QAbstractItemView::SingleSelection);
    rideList->setEditTriggers(QAbstractItemView::SelectedClicked); // allow edit
    rideList->setUniformRowHeights(true);
    rideList->setIndentation(0);
    rideList->header()->resizeSection(0,20);
    rideList->header()->resizeSection(1,90);
    rideList->header()->resizeSection(2,100);
    rideList->header()->resizeSection(3,100);
    rideList->header()->resizeSection(4,100);
    rideList->header()->resizeSection(5,70);
    rideList->header()->resizeSection(6,50);
    rideList->setSortingEnabled(true);

    downloadLayout->addWidget(selectAll);
    downloadLayout->addWidget(rideList);


    // show progress
    progressBar = new QProgressBar(this);
    progressLabel = new QLabel("Initial", this);

    overwrite = new QCheckBox(tr("Overwrite existing files"), this);

    // layout the widget now...
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QHBoxLayout *topline = new QHBoxLayout;
//    topline->addWidget(athleteCombo);
    topline->addStretch();
    topline->addWidget(fromLabel);
    topline->addWidget(from);
    topline->addWidget(toLabel);
    topline->addWidget(to);
    topline->addStretch();
    topline->addWidget(refreshButton);


    QHBoxLayout *botline = new QHBoxLayout;
    botline->addWidget(progressLabel);
    botline->addStretch();
    botline->addWidget(overwrite);
    botline->addWidget(cancelButton);
    botline->addWidget(downloadButton);

    mainLayout->addLayout(topline);
    mainLayout->addWidget(tabs);
    mainLayout->addWidget(progressBar);
    mainLayout->addLayout(botline);


    connect (cancelButton, SIGNAL(clicked()), this, SLOT(cancelClicked()));
    connect (downloadButton, SIGNAL(clicked()), this, SLOT(downloadClicked()));
    connect (refreshButton, SIGNAL(clicked()), this, SLOT(refreshClicked()));
    connect (tabs, SIGNAL(currentChanged(int)), this, SLOT(tabChanged(int)));

    QWidget::show();

}

void
GCSynchronizeDialog::cancelClicked()
{
    reject();
}

void
GCSynchronizeDialog::downloadClicked()
{
    reject();
}

void
GCSynchronizeDialog::tabChanged(int idx)
{
    reject();
}

void
GCSynchronizeDialog::refreshClicked()
{
    reject();
}

