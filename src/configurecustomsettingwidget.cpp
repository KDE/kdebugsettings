/*
  Copyright (c) 2015 Montel Laurent <montel@kde.org>

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
#include "kdebugsettingsdialog.h"
#include "kdebugsettingsutil.h"
#include <KLocalizedString>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QComboBox>

ConfigureCustomSettingWidget::ConfigureCustomSettingWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *vbox = new QVBoxLayout;
    setLayout(vbox);

    QLabel *lab = new QLabel(i18n("Category:"));
    lab->setObjectName(QStringLiteral("category_label"));
    mCategoryLineEdit = new QLineEdit;
    mCategoryLineEdit->setObjectName(QStringLiteral("category_lineedit"));
    connect(mCategoryLineEdit, SIGNAL(textChanged(QString)), SLOT(slotTextChanged(QString)));
    QHBoxLayout *categoryLayout = new QHBoxLayout;
    vbox->addLayout(categoryLayout);
    categoryLayout->addWidget(lab);
    categoryLayout->addWidget(mCategoryLineEdit);

    mEnableCategory = new QCheckBox(i18n("Enable"));
    mEnableCategory->setObjectName(QStringLiteral("enable_category"));
    vbox->addWidget(mEnableCategory);

    lab = new QLabel(i18n("Type:"));
    lab->setObjectName(QStringLiteral("categorytype_label"));
    QHBoxLayout *categoryTypeLayout = new QHBoxLayout;
    vbox->addLayout(categoryTypeLayout);

    mCategoryType = new QComboBox;
    mCategoryType->setObjectName(QStringLiteral("categorytype_combobox"));
    mCategoryType->addItem(i18n("All"), QString());
    mCategoryType->addItem(i18n("Debug"), QStringLiteral("debug"));
    mCategoryType->addItem(i18n("Warning"), QStringLiteral("warning"));
    mCategoryType->addItem(i18n("Critical"), QStringLiteral("critical"));

    categoryTypeLayout->addWidget(lab);
    categoryTypeLayout->addWidget(mCategoryType);
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
    const Category cat = KDebugSettingsUtil::parseLineLoggingQtCategory(rule);
    mCategoryLineEdit->setText(cat.logName);
    mEnableCategory->setChecked(cat.enabled);
    if (cat.type.isEmpty()) {
        //All
        mCategoryType->setCurrentIndex(0);
    } else {
        const int pos = mCategoryType->findData(cat.type);
        if (pos != -1) {
            mCategoryType->setCurrentIndex(pos);
        } else {
            //Default;
            mCategoryType->setCurrentIndex(0);
        }
    }
}

QString ConfigureCustomSettingWidget::rule()
{
    QString ruleStr = mCategoryLineEdit->text().trimmed();
    if (!ruleStr.isEmpty()) {
        const QString type = mCategoryType->currentData().toString();
        if (!type.isEmpty()) {
            ruleStr += QLatin1Char('.') + type;
        }
        if (mEnableCategory->isChecked()) {
            ruleStr += QStringLiteral("=true");
        } else {
            ruleStr += QStringLiteral("=false");
        }
    }
    return ruleStr;
}

