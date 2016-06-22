/*
  Copyright (c) 2015-2016 Montel Laurent <montel@kde.org>

  This library is free software; you can redistribute it and/or modify it
  under the terms of the GNU Library General Public License as published by
  the Free Software Foundation; either version 2 of the License, or (at your
  option) any later version.

  This library is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
  License for more details.

  You should have received a copy of the GNU Library General Public License
  along with this library; see the file COPYING.LIB.  If not, write to the
  Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
  02110-1301, USA.

*/

#include "configurecustomsettingwidget.h"
#include "categorytypecombobox.h"
#include "kdebugsettingsdialog.h"
#include "kdebugsettingsutil.h"
#include <KLocalizedString>
#include <QLabel>
#include <KLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCheckBox>

ConfigureCustomSettingWidget::ConfigureCustomSettingWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *vbox = new QVBoxLayout;
    setLayout(vbox);

    QLabel *lab = new QLabel(i18n("Category:"));
    lab->setObjectName(QStringLiteral("category_label"));
    mCategoryLineEdit = new KLineEdit;
    mCategoryLineEdit->setTrapReturnKey(true);
    mCategoryLineEdit->setClearButtonShown(true);
    mCategoryLineEdit->setObjectName(QStringLiteral("category_lineedit"));
    connect(mCategoryLineEdit, &KLineEdit::textChanged, this, &ConfigureCustomSettingWidget::slotTextChanged);
    QHBoxLayout *categoryLayout = new QHBoxLayout;
    vbox->addLayout(categoryLayout);
    categoryLayout->addWidget(lab);
    categoryLayout->addWidget(mCategoryLineEdit);

    lab = new QLabel(i18n("Type:"));
    lab->setObjectName(QStringLiteral("categorytype_label"));
    categoryLayout->addWidget(lab);

    mCategoryType = new CategoryTypeComboBox(true, this);
    mCategoryType->setObjectName(QStringLiteral("categorytype_combobox"));
    categoryLayout->addWidget(mCategoryType);

    mEnableCategory = new QCheckBox(i18n("Enable"));
    mEnableCategory->setObjectName(QStringLiteral("enable_category"));
    categoryLayout->addWidget(mEnableCategory);
}

ConfigureCustomSettingWidget::~ConfigureCustomSettingWidget()
{

}

void ConfigureCustomSettingWidget::slotTextChanged(const QString &text)
{
    const bool state = !text.trimmed().isEmpty();
    Q_EMIT enableButton(state);
}

void ConfigureCustomSettingWidget::setRule(const QString &rule)
{
    const KDebugSettingsUtil::LoadLoggingCategory cat = KDebugSettingsUtil::parseLineLoggingQtCategory(rule);
    mCategoryLineEdit->setText(cat.logName);
    mEnableCategory->setChecked(cat.enabled);
    switch (cat.type) {
    case KDebugSettingsUtil::LoadLoggingCategory::Unknown:
        break;
    case KDebugSettingsUtil::LoadLoggingCategory::Info:
        mCategoryType->setType(LoggingCategory::Info);
        break;
    case KDebugSettingsUtil::LoadLoggingCategory::Warning:
        mCategoryType->setType(LoggingCategory::Warning);
        break;
    case KDebugSettingsUtil::LoadLoggingCategory::Debug:
        mCategoryType->setType(LoggingCategory::Debug);
        break;
    case KDebugSettingsUtil::LoadLoggingCategory::Critical:
        mCategoryType->setType(LoggingCategory::Critical);
        break;
    case KDebugSettingsUtil::LoadLoggingCategory::All:
        mCategoryType->setType(LoggingCategory::All);
        break;
    }
}

QString ConfigureCustomSettingWidget::rule() const
{
    QString ruleStr = mCategoryLineEdit->text().trimmed();
    if (!ruleStr.isEmpty()) {
        switch (mCategoryType->type()) {
        case LoggingCategory::All:
            break;
        case LoggingCategory::Info:
            ruleStr += QStringLiteral(".info");
            break;
        case LoggingCategory::Warning:
            ruleStr += QStringLiteral(".warning");
            break;
        case LoggingCategory::Debug:
            ruleStr += QStringLiteral(".debug");
            break;
        case LoggingCategory::Critical:
            ruleStr += QStringLiteral(".critical");
            break;
        case LoggingCategory::Off:
            break;
        }

        if (mEnableCategory->isChecked()) {
            ruleStr += QStringLiteral("=true");
        } else {
            ruleStr += QStringLiteral("=false");
        }
    }
    return ruleStr;
}

