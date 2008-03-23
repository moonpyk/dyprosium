#include "wizardsubnetbegin.h"

WizardSubnetBegin::WizardSubnetBegin(QWidget *parent) : QWizardPage(parent) {
	ui.setupUi(this);

	setTitle(tr("Nom de l'�tendue"));
	setSubTitle(tr(
		"Vous devez fournir un nom pour identifier l'�tendue.\n"
		"Vous avez aussi la possibilit� de fournir une description"
		)
	);

	registerField(SN_WIZ_FIELD_NAME "*", ui.editName);
	registerField(SN_WIZ_FIELD_DESCRIPTION, ui.editDescription, "plainText", "textChanged");
}

WizardSubnetBegin::~WizardSubnetBegin() { }
