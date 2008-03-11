#ifndef FRMMAIN_H
#define FRMMAIN_H

#include "ui_frmmain.h"

#include <QtGui/QMainWindow>

#include "optionsview.h"

#pragma region DEFINES

#define FRMMAIN_TITLE_BASE "Dyprosium"
#define FRMMAIN_TITLE_NO_CONFIGNAME FRMMAIN_TITLE_BASE " - %1" 
#define FRMMAIN_TITLE_NORMAL FRMMAIN_TITLE_NO_CONFIGNAME " (%2)"

#define FRMMAIN_PAGE_INTRO 0
#define FRMMAIN_PAGE_ROOT 1
#define FRMMAIN_PAGE_SUBNET 2
#define FRMMAIN_PAGE_EXCLUSIONS 3
#define FRMMAIN_PAGE_RESERVATIONS 4
#define FRMMAIN_PAGE_OPTIONS_VIEW 5

#pragma endregion

class FrmMain : public QMainWindow {
	Q_OBJECT

#pragma region ConfigurationMode

	enum ConfigurationMode {
		Intro,
		ConfigurationRoot,
		SubnetRoot,
		SubnetOptions,
		SubnetReservations,
		SubnetReservationOptions,
		ConfigurationGlobalOptions
	};

	//Q_ENUMS(ConfigurationMode);

#pragma endregion

public:
	FrmMain(QWidget *parent = 0, Qt::WFlags flags = 0);
	~FrmMain();

	void test ();

public:
	Q_PROPERTY(DHConfiguration * currentDHConfiguration READ currentDHConfiguration);
	Q_PROPERTY(DHSubNetwork * currentDHSubNetwork READ currentDHSubNetwork);
	Q_PROPERTY(DHSubNetworkReservation * currentSubNetworkReservation READ currentSubNetworkReservation);

	DHConfiguration * currentDHConfiguration() const;
	DHSubNetwork * currentDHSubNetwork() const;
	DHSubNetworkReservation * currentSubNetworkReservation() const;

public slots:
	void navigateLeft();
	void navigateRight();

	void selectConfigurationMode(QTreeWidgetItem* currentItem);

private:
	void _setCurrentConfiguration(DHConfiguration * val);
	void _setCurrentSubNetwork(DHSubNetwork * val);
	void _setCurrentSubNetworkReservation(DHSubNetworkReservation * val);

	void _setWindowTitle(QTreeWidgetItem* currentItem);

private:
	void _resetCurrentConfigurationHelpers();

	void _initializeSeparators ();
	void _initializeEditionControlsEvents ();

	void _hideAllToggleActions ();

	void _setFileActionsEnabled(bool value);
	void _setSimpleActionsVisible (bool value);
	void _setSimpleActionsEnabled(bool value);
	void _setSimpleActionsEnabled(ISimpleActionsClient * client);

	void _setSimpleActionsSeparatorsVisible (bool value);
	void _setActionsSeparatorsVisible (bool value);

	void _resetViewMode();

	void _setViewModeToOptions(ConfigurationMode mode, QString titleArgs = QString());
	void _setViewModeToSubnetReservations();

	QTreeWidgetItem * _getBackOnTree(QTreeWidgetItem* item, int passes = 1);

	void _appendConfigurationTreeItem (DHConfiguration * configuration);

private slots:
	void _simpleActionButtonEnabledChanged();
	
	void on_actionEdit_triggered();

	void on_actionExport_triggered();

	void on_actionRemoveSubnet_triggered();
	
	void on_sideBarTree_currentItemChanged(QTreeWidgetItem* current, QTreeWidgetItem*);

	void on_actionAdd_triggered();
	void on_actionDelete_triggered();

	void on_actionAddSubnet_triggered();

	void on_actionNew_triggered();
	void on_actionOpen_triggered();
	void on_actionSave_triggered();
	void on_actionCloseConfiguration_triggered();

	void on_pageOptionsView_valuesChanged();

private:
	Ui::FrmMain ui;

	ConfigurationMode _currentMode;

	DHConfiguration * _currentDHConfiguration;
	DHSubNetwork * _currentDHSubNetwork;
	DHSubNetworkReservation * _currentDHSubNetworkReservation;

	ISimpleActionsClient * _currentSimpleActionsClient;

	QAction * _toolbarActionsSeparator;
	QAction * _toolbarSimpleActionsSeparator;
	QAction * _menuActionsSeparator;
	QAction * _menuSimpleActionsSeparator;
};

#endif // FRMMAIN_H
