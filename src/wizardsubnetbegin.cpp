#include "wizardsubnetbegin.h"

WizardSubnetBegin::WizardSubnetBegin(QWidget *parent) : QWizardPage(parent) {
	ui.setupUi(this);

	setTitle(tr("Nom de l'étendue"));
	setSubTitle(tr(
		"Vous devez fournir un nom pour identifier l'étendue.\n"
		"Vous avez aussi la possibilité de fournir une description"
		)
	);

	registerField(SN_WIZ_FIELD_NAME "*", ui.editName);
	registerField(SN_WIZ_FIELD_DESCRIPTION, ui.editDescription, "plainText", "textChanged");
}

WizardSubnetBegin::~WizardSubnetBegin() { }
