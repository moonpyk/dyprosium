#include "frmmain.h"

#include "dhconfiguration.h"
#include "iptools.h"
#include "wizardcreator.h"

#include "optioneditor.h"

#include "showexport.h"

#include "spinnerwidget.h"

#include "titlewidget.h"

// CTor

FrmMain::FrmMain(QWidget *parent, Qt::WFlags flags): QMainWindow(parent, flags) {
	ui.setupUi(this);

#ifdef Q_WS_MAC
	this->setUnifiedTitleAndToolBarOnMac(true);
#endif

	ui.sideBarTree->expandAll();
	ui.sideBarTree->headerItem()->setHidden(true);

	_initializeSeparators();
	_initializeEditionControlsEvents();

	_resetCurrentConfigurationHelpers();

	QObject::connect(ui.actionNavigateLeft, SIGNAL(activated()),this, SLOT(navigateLeft()));
	QObject::connect(ui.actionNavigateRight, SIGNAL(activated()), this, SLOT(navigateRight()));

	this->setWindowTitle(FRMMAIN_TITLE_BASE);
	ui.controlsStack->setCurrentIndex(FRMMAIN_PAGE_INTRO);

#ifdef Q_WS_MAC
	this->setWindowIcon(QIcon());
#endif
}

FrmMain::~FrmMain() { }

// Test

void FrmMain::test () {
	DHConfiguration * configuration = new DHConfiguration("Masterplop", "");

	DHSubNetwork * subnet
		= new DHSubNetwork("Test", "192.168.1.0", "255.255.255.0", "192.168.1.1", "192.168.1.99");

	DHSubNetworkReservation * reservation = 
		new DHSubNetworkReservation("Test", "192.168.1.1", "00:00:00:00:00:01", true);

	DHSubNetworkReservation * reservationtwo = 
		new DHSubNetworkReservation("Test", "192.168.1.2", "00:FF:00:00:00:02", true);

	subnet->addSubNetworkReservation(reservation);
	subnet->addSubNetworkReservation(reservationtwo);

	configuration->addSubNetwork(subnet);

	_appendConfigurationTreeItem(configuration);
}

// Properties

DHConfiguration * FrmMain::currentDHConfiguration () const {
	return _currentDHConfiguration;
}

DHSubNetwork * FrmMain::currentDHSubNetwork () const {
	return _currentDHSubNetwork;
}

DHSubNetworkReservation * FrmMain::currentSubNetworkReservation() const {
	return _currentDHSubNetworkReservation;
}

// Public slots

void FrmMain::navigateLeft() {
	QTreeWidgetItem * currentItem = ui.sideBarTree->currentItem();

	if(currentItem) {
		QTreeWidgetItem * itemAbove = 
			ui.sideBarTree->itemAbove(ui.sideBarTree->currentItem());

		if(itemAbove) {
			itemAbove->setExpanded(true);
			ui.sideBarTree->setCurrentItem(itemAbove);
		}
	}
}

void FrmMain::navigateRight() {
	QTreeWidgetItem * currentItem = ui.sideBarTree->currentItem();

	if(currentItem) {
		if(!currentItem->isExpanded()) {
			currentItem->setExpanded(true);
		}

		QTreeWidgetItem * itemBelow = 
			ui.sideBarTree->itemBelow(ui.sideBarTree->currentItem());

		if(itemBelow) {
			itemBelow->setExpanded(true);
			ui.sideBarTree->setCurrentItem(itemBelow);
		}
	}
}

/**
* This function is executed when user selects a new QTreeWidgetItem in the sidebar.
* It shows right configuration page, configures editor
*
* @param currentItem the newly selected item of the sideBar
*
* @see on_sideBarTree_currentItemChanged
*/
void FrmMain::selectConfigurationMode(QTreeWidgetItem * currentItem) {
	_resetCurrentConfigurationHelpers();

	_resetViewMode();
	_hideAllToggleActions();

	if(currentItem) {
		if(currentItem != ui.sideBarTree->currentItem()) {
			ui.sideBarTree->setCurrentItem(currentItem, 0);
			return;
		}

		ui.actionNavigateLeft->setEnabled(ui.sideBarTree->itemAbove(currentItem));
		ui.actionNavigateRight->setEnabled(ui.sideBarTree->itemBelow(currentItem));

		bool typeSet;
		int type = currentItem->getItemRole(&typeSet);

		if(typeSet) {
			switch(type) {
		case TREE_ROLE_ROOT:
			_currentMode = ConfigurationRoot;
			_setCurrentConfiguration (currentItem->getConfiguration());

			_setActionsSeparatorsVisible(true);
			ui.actionAddSubnet->setVisible(true);
			ui.actionAddOption->setVisible(true);

			ui.controlsStack->setCurrentIndex(FRMMAIN_PAGE_ROOT);
			break;

		case TREE_ROLE_SUBNET:
			_setCurrentSubNetwork (currentItem->getSubNetwork());
			_setViewModeToSubNetwork();

			break;

		case TREE_ROLE_SUBNET_EXCLUSIONS:
			_setCurrentSubNetwork (_getBackOnTree(currentItem)->getSubNetwork());

			_setSimpleActionsVisible(true);

			ui.controlsStack->setCurrentIndex(FRMMAIN_PAGE_EXCLUSIONS);
			break;

		case TREE_ROLE_SUBNET_RESERVATIONS:
			_setCurrentSubNetwork (_getBackOnTree(currentItem)->getSubNetwork());
			_setViewModeToSubnetReservations();
			break;

		case TREE_ROLE_GLOBAL_OPTIONS:
			_setCurrentConfiguration (_getBackOnTree(currentItem)->getConfiguration());
			_setViewModeToOptions(ConfigurationGlobalOptions);
			break;

		case TREE_ROLE_SUBNET_RESERVATION_OPTION: {
			DHSubNetworkReservation * reservation = 
				currentItem->getSubNetworkReservation();

			_setCurrentSubNetworkReservation(reservation);

			QString infos;

			if (reservation) {
				infos = QString(tr("%1 [%2]")
					.arg(reservation->name())
					.arg(reservation->address())
				);
			}

			_setViewModeToOptions(SubnetReservationOptions, infos);
		  }
		    break;

		case TREE_ROLE_SUBNET_OPTIONS:
			_setCurrentSubNetwork (_getBackOnTree(currentItem)->getSubNetwork());
			_setViewModeToOptions(SubnetOptions);
			break;
			}
		}

	} else {
		ui.actionNavigateLeft->setEnabled(false);
		ui.actionNavigateRight->setEnabled(false);
	}

	_setWindowTitle(currentItem);
}

// Private Properties

void FrmMain::_setCurrentConfiguration(DHConfiguration * val) {
	_setFileActionsEnabled(val != NULL);

	_currentDHConfiguration = val;
}

void FrmMain::_setCurrentSubNetwork(DHSubNetwork * val) {
	_currentDHSubNetwork = val;

	if(val) {
		_setCurrentConfiguration(val->parentConfiguration());
	}
}

void FrmMain::_setCurrentSubNetworkReservation(DHSubNetworkReservation * val) {
	_currentDHSubNetworkReservation = val;

	if (val) {
		_setCurrentSubNetwork(val->parentSubnetwork());
	}
}

/**
* This function sets new main window title depending on currently selected QTreeWidgetItem.
*
* @param currentItem newly selected QTreeWidgetItem
*
* @remarks <TODO: insert remarks here>
* @see selectConfigurationMode
*/
void FrmMain::_setWindowTitle(QTreeWidgetItem* currentItem) {
	if(currentItem && _currentDHConfiguration) {
		if(_currentMode == ConfigurationRoot) {
			this->setWindowTitle(
				QString(FRMMAIN_TITLE_NO_CONFIGNAME)
				.arg(currentItem->text(0))
				);

		} else {
			this->setWindowTitle(
				QString(FRMMAIN_TITLE_NORMAL)
				.arg(currentItem->text(0))
				.arg(_currentDHConfiguration->name())
				);
		}		

	} else {
		this->setWindowTitle(FRMMAIN_TITLE_BASE);
	}
}

// Private methods

/**
* This function resets editors state between modes changes
*
* @see selectConfigurationMode
*/
void FrmMain::_resetCurrentConfigurationHelpers() {
	_currentMode					= Intro;
	_currentSimpleActionsClient		= NULL;

	_currentDHSubNetwork			= NULL;
	_currentDHSubNetworkReservation	= NULL;

	_setCurrentConfiguration(NULL);
}

/**
* This function creates separators between toggling elements
*
* @remarks <TODO: insert remarks here>
* @see <TODO: insert text here>
*/
void FrmMain::_initializeSeparators () {
	_toolbarActionsSeparator = ui.mainToolBar->insertSeparator(ui.actionAddSubnet);
	_toolbarActionsSeparator->setVisible(false);

	_toolbarSimpleActionsSeparator = ui.mainToolBar->insertSeparator(ui.actionAdd);
	_toolbarSimpleActionsSeparator->setVisible(false);

	_menuActionsSeparator = ui.menuAction->insertSeparator(ui.actionAddSubnet);
	_menuActionsSeparator->setVisible(false);

	_menuSimpleActionsSeparator = ui.menuAction->insertSeparator(ui.actionAdd);
	_menuSimpleActionsSeparator->setVisible(false);
}

/**
* This functions initializes all edition controls events
*/
void FrmMain::_initializeEditionControlsEvents () {
	QObject::connect(ui.pageOptionsView, SIGNAL(simpleActionButtonsEnabledChanged()), this, SLOT(_simpleActionButtonEnabledChanged()));
	QObject::connect(ui.pageReservationsView, SIGNAL(simpleActionButtonsEnabledChanged()), this, SLOT(_simpleActionButtonEnabledChanged()));
}

/**
* This function hides all actions buttons of the menus and toobars plus their separators
*/
void FrmMain::_hideAllToggleActions () {
	_setActionsSeparatorsVisible(false);

	ui.actionAddSubnet->setVisible(false);
	ui.actionAddReservation->setVisible(false);
	ui.actionAddOption->setVisible(false);
	ui.actionAddExclusion->setVisible(false);
	ui.actionRemoveSubnet->setVisible(false);

	_setSimpleActionsVisible(false);
	_setSimpleActionsEnabled(false);
}

void FrmMain::_setFileActionsEnabled(bool value) {
	ui.actionSave->setEnabled(value);
	ui.actionExport->setEnabled(value);
	ui.actionCloseConfiguration->setEnabled(value);
}

void FrmMain::_setSimpleActionsVisible (bool value) {
	_setSimpleActionsSeparatorsVisible(value);

	ui.actionAdd->setVisible(value);
	ui.actionDelete->setVisible(value);
	ui.actionEdit->setVisible(value);
}

void FrmMain::_setSimpleActionsEnabled(bool value) {
	ui.actionAdd->setEnabled(value);
	ui.actionDelete->setEnabled(value);
	ui.actionEdit->setEnabled(value);
}

void FrmMain::_setSimpleActionsSeparatorsVisible (bool value) {
	_toolbarSimpleActionsSeparator->setVisible(value);
	_menuSimpleActionsSeparator->setVisible(value);
}

void FrmMain::_setActionsSeparatorsVisible (bool value) {
	_toolbarActionsSeparator->setVisible(value);
	_menuActionsSeparator->setVisible(value);
}

void FrmMain::_setSimpleActionsEnabled(ISimpleActionsClient * client) {
	ui.actionAdd->setEnabled(client->addEnabled());
	ui.actionDelete->setEnabled(client->removeEnabled());
	ui.actionEdit->setEnabled(client->editEnabled());
}

void FrmMain::_resetViewMode() {
	ui.controlsStack->setCurrentIndex(FRMMAIN_PAGE_INTRO);

	_currentMode					= Intro;
	_currentSimpleActionsClient		= NULL;
}

void FrmMain::_setViewModeToSubNetwork() {
	_setActionsSeparatorsVisible(true);

	_currentMode = SubnetRoot;

	ui.actionAddSubnet->setVisible(true);
	ui.actionRemoveSubnet->setVisible(true);
	ui.actionAddReservation->setVisible(true);
	ui.actionAddOption->setVisible(true);

#ifdef SUBNET_EXCLUSIONS_SUPPORT
	ui.actionAddExclusion->setVisible(true);
#endif

	ui.controlsStack->setCurrentIndex(FRMMAIN_PAGE_SUBNET);
}

void FrmMain::_setViewModeToOptions(ConfigurationMode mode, QString titleArgs /*= QString()*/) {
	_currentMode = mode;

	ui.pageOptionsView->clear();

	QString title;

	switch(mode)
	{
	case ConfigurationGlobalOptions:
		title = tr("Configuration global options");
		ui.pageOptionsView->setOptionsList(*(_currentDHConfiguration->options()));
		break;

	case SubnetOptions:
		title = tr("Subnet options");
		ui.pageOptionsView->setOptionsList(*(_currentDHSubNetwork->options()));
		break;

	case SubnetReservationOptions:
		title = tr("Reservation options : %1").arg(titleArgs);
		ui.pageOptionsView->setOptionsList(*(_currentDHSubNetworkReservation->options()));
		break;

	default: break;
	}

	ui.pageOptionsView->setTitle(title);
	ui.controlsStack->setCurrentIndex(FRMMAIN_PAGE_OPTIONS_VIEW);

	_setSimpleActionsVisible(true);
	_setSimpleActionsEnabled(ui.pageOptionsView);

	_currentSimpleActionsClient = ui.pageOptionsView;
}

void FrmMain::_setViewModeToSubnetReservations() {
	ui.pageReservationsView->clear();

	_currentMode = SubnetReservations;
	ui.pageReservationsView->setCurrentDHSubNetwork(_currentDHSubNetwork);

	_setSimpleActionsVisible(true);
	_setSimpleActionsEnabled(ui.pageReservationsView);

	_currentSimpleActionsClient = ui.pageReservationsView;

	ui.controlsStack->setCurrentIndex(FRMMAIN_PAGE_RESERVATIONS);
}

void FrmMain::_appendConfigurationTreeItem (DHConfiguration * configuration) {
	ui.sideBarTree->addTopLevelItem(configuration->rootItemWidget());
	configuration->rootItemWidget()->setExpanded(true);

	ui.sideBarTree->setCurrentItem(configuration->rootItemWidget());
}

QTreeWidgetItem * FrmMain::_getBackOnTree(QTreeWidgetItem* item, int passes /*= 1*/) {
	for (int i = 0 ; i < passes ; i++) {
		item = item->parent();

		if(item == NULL) {
			break;
		}
	}

	return item;
}

// Private slots

void FrmMain::_simpleActionButtonEnabledChanged () {
	switch(_currentMode) {
		case ConfigurationGlobalOptions:
		case SubnetOptions:
		case SubnetReservationOptions:
			_setSimpleActionsEnabled(ui.pageOptionsView);
			break;

		case SubnetReservations:
			_setSimpleActionsEnabled(ui.pageReservationsView);
			break;

		default:
			break;
	}
}

void FrmMain::on_actionNew_triggered() {
	test();
}

void FrmMain::on_actionOpen_triggered() {

}

void FrmMain::on_actionSave_triggered () {

}


void FrmMain::on_actionAddSubnet_triggered() {
	QWizard * wizard = WizardCreator::subnetWizard(this);

	if (wizard->exec() == QDialog::Accepted) {
		QString name				= wizard->field(SN_WIZ_FIELD_NAME).toString();
		QString description			= wizard->field(SN_WIZ_FIELD_DESCRIPTION).toString();

		QString firstIp				= wizard->field(SN_WIZ_FIELD_FIRST_IP_ADDRESS).toString();
		QString lastIp				= wizard->field(SN_WIZ_FIELD_LAST_IP_ADDRESS).toString();
		QString mask				= wizard->field(SN_WIZ_FIELD_MASK_IP_ADDRESS).toString();
		QString networkAdress		= wizard->field(SN_WIZ_FILED_NETWORK_IP_ADDRESS).toString();

		QString leaseTime			= wizard->field(SN_WIZ_FIELD_LEASE_TIME).toString();

		QStringList routersList		= wizard->field(SN_WIZ_FIELD_ROUTERS).toStringList();

		QString dnsParentDomain		= wizard->field(SN_WIZ_FIELD_PARENT_DOMAIN).toString();
		QStringList dnsServersList	= wizard->field(SN_WIZ_FIELD_DNSLIST).toStringList();

		DHSubNetwork * newSubnet = 
			new DHSubNetwork(name, networkAdress, mask, firstIp, lastIp);

		newSubnet->setLeaseTime(leaseTime);
		newSubnet->setDescription(description);

		if(!routersList.isEmpty()) {
			newSubnet->options()->append(DHOptionDuet(routers, routersList.join(", ")));
		}

		if (!dnsParentDomain.isEmpty()) {
			newSubnet->options()->append(DHOptionDuet(domain_name, dnsParentDomain));
		}

		if(!dnsServersList.isEmpty()) {
			newSubnet->options()->append(DHOptionDuet(domain_name_servers, dnsServersList.join(", ")));
		}

		if(_currentDHConfiguration) {
			_currentDHConfiguration->addSubNetwork(newSubnet);
		}
	}

	wizard->deleteLater();
}

void FrmMain::on_sideBarTree_currentItemChanged(QTreeWidgetItem* currentItem, QTreeWidgetItem*) {
	selectConfigurationMode(currentItem);
}

void FrmMain::on_actionAdd_triggered(){
	if(ui.actionAdd->isVisible() && _currentSimpleActionsClient) {
		_currentSimpleActionsClient->add();
	}
}

void FrmMain::on_actionDelete_triggered(){
	if(ui.actionDelete->isVisible() && _currentSimpleActionsClient) {
		_currentSimpleActionsClient->remove();
	}
}

void FrmMain::on_actionEdit_triggered() {
	if(ui.actionEdit->isVisible() && _currentSimpleActionsClient) {
		_currentSimpleActionsClient->edit();
	}
}

void FrmMain::on_actionExport_triggered() {
	if(_currentDHConfiguration) {
		ShowExport::showMessage(this, _currentDHConfiguration->xmlConfiguration());
	}
}

void FrmMain::on_actionCloseConfiguration_triggered() {
	if(_currentDHConfiguration) {
		delete _currentDHConfiguration;

		if(!ui.sideBarTree->currentItem()) {
			_setCurrentConfiguration(NULL);
		}
	}
}

void FrmMain::on_actionRemoveSubnet_triggered() {
	if(_currentDHConfiguration && _currentDHSubNetwork) {
		_currentDHConfiguration->removeSubNetwork(_currentDHSubNetwork);
	}
}

/**
* This slot is executed when user changes the values-set in the pageOptionsView.
* This binds options value to the right DH configuration class.
*/
void FrmMain::on_pageOptionsView_valuesChanged() {
	QList<DHOptionDuet> * list = NULL;

	switch(_currentMode) {
	case ConfigurationGlobalOptions:
		if(_currentDHConfiguration) {
			list = _currentDHConfiguration->options();
		}
		break;

	case SubnetOptions:
		if(_currentDHSubNetwork) {
			list = _currentDHSubNetwork->options();
		}
		
		break;

	case SubnetReservationOptions:
		if(_currentDHSubNetworkReservation) {
			list = _currentDHSubNetworkReservation->options();
		}
		break;

	default: break;
	}

	if(list) {
		list->clear();

		*list << ui.pageOptionsView->optionsList();
	}
}

void FrmMain::on_actionAddReservation_triggered() {
	selectConfigurationMode(
		_currentDHSubNetwork->subnetReservationsItemWidget()
	);
	
	if(_currentSimpleActionsClient) {
		_currentSimpleActionsClient->add();
	}
}

void FrmMain::on_actionAddOption_triggered() {
	if(_currentMode == SubnetRoot) {
		selectConfigurationMode(
			_currentDHSubNetwork->subnetOptionsItemWidget()
			);

		if(_currentSimpleActionsClient) {
			_currentSimpleActionsClient->add();
		}

	} else if (_currentMode == ConfigurationRoot) {
		selectConfigurationMode(_currentDHConfiguration->globalOptionsItemWidget());

		if(_currentSimpleActionsClient) {
			_currentSimpleActionsClient->add();
		}
	}
}
