/*
    SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "configurecustomsettingwidget.h"
using namespace Qt::Literals::StringLiterals;

#include "categorytypecombobox.h"
#include "kdebugsettingsutil.h"
#include <KLineEdit>
#include <KLocalizedString>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>

ConfigureCustomSettingWidget::ConfigureCustomSettingWidget(QWidget *parent)
    : QWidget(parent)
    , mCategoryLineEdit(new KLineEdit(this))
    , mEnableCategory(new QCheckBox(i18nc("@option:check", "Enable"), this))
    , mCategoryType(new CategoryTypeComboBox(true, this))
{
    auto vbox = new QVBoxLayout(this);

    auto lab = new QLabel(i18nc("@label:textbox", "Category:"), this);
    lab->setObjectName("category_label"_L1);
    mCategoryLineEdit->setTrapReturnKey(true);
    mCategoryLineEdit->setClearButtonEnabled(true);
    mCategoryLineEdit->setObjectName("category_lineedit"_L1);
    connect(mCategoryLineEdit, &KLineEdit::textChanged, this, &ConfigureCustomSettingWidget::slotTextChanged);
    auto categoryLayout = new QHBoxLayout;
    vbox->addLayout(categoryLayout);
    categoryLayout->addWidget(lab);
    categoryLayout->addWidget(mCategoryLineEdit);

    lab = new QLabel(i18nc("@label:textbox", "Type:"), this);
    lab->setObjectName("categorytype_label"_L1);
    categoryLayout->addWidget(lab);

    mCategoryType->setObjectName("categorytype_combobox"_L1);
    categoryLayout->addWidget(mCategoryType);

    mEnableCategory->setObjectName("enable_category"_L1);
    categoryLayout->addWidget(mEnableCategory);
}

ConfigureCustomSettingWidget::~ConfigureCustomSettingWidget() = default;

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
    return KDebugSettingsUtil::generateDisplayRule(mCategoryLineEdit->text().trimmed(), mEnableCategory->isChecked(), mCategoryType->type());
}

#include "moc_configurecustomsettingwidget.cpp"
