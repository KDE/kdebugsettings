#!/usr/bin/env python3
# SPDX-License-Identifier: LGPL-2.0-or-later
# SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

import unittest

from appium import webdriver
from appium.options.common.base import AppiumOptions
from appium.webdriver.common.appiumby import AppiumBy


class SmokeTests(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        options = AppiumOptions()
        options.set_capability("app", "org.kde.kdebugsettings.desktop")
        cls.driver = webdriver.Remote(command_executor='http://127.0.0.1:4723', options=options)

    @classmethod
    def tearDownClass(self):
        self.driver.quit()

    def setUp(self):
        pass

    def test_addTrainTrip(self):
        self.driver.find_element(by=AppiumBy.ACCESSIBILITY_ID, value="QApplication.KDebugSettingsDialog.buttonbox.insert_button").click()


if __name__ == '__main__':
    unittest.main()
