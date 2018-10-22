# -*- coding: utf-8 -*-

import names

def main():
    startApplication("MediaServerApp")
    mouseClick(waitForObject(names.o_Rectangle), 110, 46, Qt.LeftButton)
    mouseClick(waitForObject(names.label_MnemonicLabel_4))
    test.compare(str(waitForObjectExists(names.tfServerString_TextField).text), "SambaServer")
    test.compare(str(waitForObjectExists(names.tfWorkgroup_TextField).text), "WORKGROUP")
    test.compare(str(waitForObjectExists(names.tfNetbiosName_TextField).text), "DataServer")
    test.compare(waitForObjectExists(names.cbSecurity_ComboBox).currentIndex, 0)
    test.compare(str(waitForObjectExists(names.cbSecurity_ComboBox).currentText), "user")
    test.compare(str(waitForObjectExists(names.cbMapToGuest_ComboBox).currentText), "Bad User")
    test.compare(waitForObjectExists(names.cbMapToGuest_ComboBox).currentIndex, 0)
    test.compare(waitForObjectExists(names.cbBrowseable_CheckBox).checked, True)
    test.compare(waitForObjectExists(names.cbLocalMaster_CheckBox).checked, True)
    test.compare(waitForObjectExists(names.cbDomainMaster_CheckBox).checked, True)
