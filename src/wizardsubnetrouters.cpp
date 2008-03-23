#include "wizardsubnetrouters.h"

WizardSubnetRouters::WizardSubnetRouters(QWidget *parent)
	: QWizardPage(parent)
{
	ui.setupUi(this);

	setTitle(tr("Routeur (passerelle par d�faut)"));
	setSubTitle(
		tr("Vous pouvez sp�cifier les routeurs, ou les passerelles"
		"par d�faut, qui doivent �tre distribu�es par cette �tendue."
	));

	registerField(SN_WIZ_FIELD_ROUTERS, ui.routersList, "stringList", "stringListChanged");
}

WizardSubnetRouters::~WizardSubnetRouters() {}
