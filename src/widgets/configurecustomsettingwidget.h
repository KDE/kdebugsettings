/*
    SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once

#include "libkdebugsettings_private_export.h"
#include <QWidget>
class KLineEdit;
class QCheckBox;
class CategoryTypeComboBox;
class LIBKDEBUGSETTINGS_EXPORT_TEST_EXPORT ConfigureCustomSettingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ConfigureCustomSettingWidget(QWidget *parent = nullptr);
    ~ConfigureCustomSettingWidget() override;

    [[nodiscard]] QString rule() const;
    void setRule(const QString &rule);

Q_SIGNALS:
    void enableButton(bool state);

private:
    void slotTextChanged(const QString &);

    KLineEdit *const mCategoryLineEdit;
    QCheckBox *const mEnableCategory;
    CategoryTypeComboBox *const mCategoryType;
};
