﻿/*
 * Copyright 2018-2020 Qter(qsaker@qq.com). All rights reserved.
 *
 * The file is encoding with utf-8 (with BOM). It is a part of QtSwissArmyKnife
 * project(https://www.qsak.pro). The project is an open source project. You can
 * get the source of the project from: "https://github.com/qsak/QtSwissArmyKnife"
 * or "https://gitee.com/qsak/QtSwissArmyKnife". Also, you can join in the QQ
 * group which number is 952218522 to have a communication.
 */
#include "SAKUdpMulticastEditingDialog.hh"
#include "ui_SAKUdpMulticastEditingDialog.h"

SAKUdpMulticastEditingDialog::SAKUdpMulticastEditingDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SAKUdpMulticastEditingDialog)
{
    ui->setupUi(this);
    setModal(true);
}

SAKUdpMulticastEditingDialog::~SAKUdpMulticastEditingDialog()
{
    delete ui;
}

QString SAKUdpMulticastEditingDialog::address()
{
    return ui->addressLineEdit->text().trimmed();
}

quint16 SAKUdpMulticastEditingDialog::port()
{
    return ui->portLineEdit->text().trimmed().toUShort();
}
