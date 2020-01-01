/*
  Copyright (c) 2015-2020 Laurent Montel <montel@kde.org>

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
    QVBoxLayout *vbox = new QVBoxLayout(this);

    QLabel *lab = new QLabel(i18n("Category:"), this);
    lab->setObjectName(QStringLiteral("category_label"));
    mCategoryLineEdit = new KLineEdit(this);
    mCategoryLineEdit->setTrapReturnKey(true);
    mCategoryLineEdit->setClearButtonEnabled(true);
    mCategoryLineEdit->setObjectName(QStringLiteral("category_lineedit"));
    connect(mCategoryLineEdit, &KLineEdit::textChanged, this, &ConfigureCustomSettingWidget::slotTextChanged);
    QHBoxLayout *categoryLayout = new QHBoxLayout;
    vbox->addLayout(categoryLayout);
    categoryLayout->addWidget(lab);
    categoryLayout->addWidget(mCategoryLineEdit);

    lab = new QLabel(i18n("Type:"), this);
    lab->setObjectName(QStringLiteral("categorytype_label"));
    categoryLayout->addWidget(lab);

    mCategoryType = new CategoryTypeComboBox(true, this);
    mCategoryType->setObjectName(QStringLiteral("categorytype_combobox"));
    categoryLayout->addWidget(mCategoryType);

    mEnableCategory = new QCheckBox(i18n("Enable"), this);
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
    const KDebugSettingsUtil::LineLoggingQtCategory cat = KDebugSettingsUtil::parseLineLoggingQtCategory(rule);
    mCategoryLineEdit->setText(cat.logName);
    mEnableCategory->setChecked(cat.enabled);
    switch (cat.type) {
    case KDebugSettingsUtil::LineLoggingQtCategory::Unknown:
        break;
    case KDebugSettingsUtil::LineLoggingQtCategory::Info:
        mCategoryType->setType(LoggingCategory::Info);
        break;
    case KDebugSettingsUtil::LineLoggingQtCategory::Warning:
        mCategoryType->setType(LoggingCategory::Warning);
        break;
    case KDebugSettingsUtil::LineLoggingQtCategory::Debug:
        mCategoryType->setType(LoggingCategory::Debug);
        break;
    case KDebugSettingsUtil::LineLoggingQtCategory::Critical:
        mCategoryType->setType(LoggingCategory::Critical);
        break;
    case KDebugSettingsUtil::LineLoggingQtCategory::All:
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
        case LoggingCategory::Undefined:
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
