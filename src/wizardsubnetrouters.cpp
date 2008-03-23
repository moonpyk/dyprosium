#include "wizardsubnetrouters.h"

WizardSubnetRouters::WizardSubnetRouters(QWidget *parent)
	: QWizardPage(parent)
{
	ui.setupUi(this);

	setTitle(tr("Routeur (passerelle par défaut)"));
	setSubTitle(
		tr("Vous pouvez spécifier les routeurs, ou les passerelles"
		"par défaut, qui doivent être distribuées par cette étendue."
	));

	registerField(SN_WIZ_FIELD_ROUTERS, ui.routersList, "stringList", "stringListChanged");
}

WizardSubnetRouters::~WizardSubnetRouters() {}
