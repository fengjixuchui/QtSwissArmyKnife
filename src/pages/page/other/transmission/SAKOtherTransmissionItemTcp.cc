﻿/*
 * Copyright 2018-2020 Qter(qsaker@qq.com). All rights reserved.
 *
 * The file is encoding with utf-8 (with BOM). It is a part of QtSwissArmyKnife
 * project(https://www.qsak.pro). The project is an open source project. You can
 * get the source of the project from: "https://github.com/qsak/QtSwissArmyKnife"
 * or "https://gitee.com/qsak/QtSwissArmyKnife". Also, you can join in the QQ
 * group which number is 952218522 to have a communication.
 */
#include <QHostAddress>

#include "SAKGlobal.hh"
#include "SAKOtherTransmissionItemTcp.hh"

#include "ui_SAKOtherTransmissionItemTcp.h"

SAKOtherTransmissionItemTcp::SAKOtherTransmissionItemTcp(SAKDebugPage *debugPage, QWidget *parent)
    :SAKOtherTransmissionItem (debugPage, parent)
    ,mUi (new Ui::SAKOtherTransmissionItemTcp)
    ,mTcpSocket (Q_NULLPTR)
{
    mUi->setupUi(this);

    mEnableCheckBox = mUi->enableCheckBox;
    mCustomAddressCheckBox = mUi->customAddressCheckBox;
    mLocalAddressComboBox = mUi->addressComboBox;
    mLocalPortLineEdit = mUi->portLineEdit;
    mHandleReceiveDataCheckBox = mUi->handleReceiveDataCheckBox;
    mServerAddressLineEdit = mUi->targetAddressLineEdit;
    mServerPortLineEdit = mUi->targetPortLineEdit;

    SAKGlobal::initIpComboBox(mLocalAddressComboBox);
}

SAKOtherTransmissionItemTcp::~SAKOtherTransmissionItemTcp()
{
    if (mTcpSocket){
        delete mTcpSocket;
    }
    delete mUi;
}

void SAKOtherTransmissionItemTcp::write(QByteArray data)
{
    if (mTcpSocket){
        if (!mTcpSocket->write(data)){
#ifdef QT_DEBUG
        qDebug() << "发送取数据失败" << mTcpSocket->errorString();
#endif
        }
    }
}

void SAKOtherTransmissionItemTcp::on_enableCheckBox_clicked()
{
    auto closeDev = [&](){
        if (mTcpSocket){
            mTcpSocket->disconnectFromHost();
            if (mTcpSocket->state() == QTcpSocket::ConnectedState){
                mTcpSocket->waitForDisconnected();
            }
            disconnect(mTcpSocket, &QTcpSocket::readyRead, this, &SAKOtherTransmissionItemTcp::read);
            delete mTcpSocket;
            mTcpSocket = Q_NULLPTR;
            this->setUiEnable(true);
        }
    };

    if (mEnableCheckBox->isChecked()){
        mTcpSocket = new QTcpSocket;
        if (mCustomAddressCheckBox->isChecked()){
             if (!mTcpSocket->bind(QHostAddress(mLocalAddressComboBox->currentText()), static_cast<quint16>(mLocalPortLineEdit->text().toInt()))){
                emit requestOutputMessage(tr("设备绑定失败：") + mTcpSocket->errorString(), false);
                mEnableCheckBox->setChecked(false);
                closeDev();
                return;
             }
        }

        if (!mTcpSocket->open(QTcpSocket::ReadWrite)){
            emit requestOutputMessage(tr("设备无法打开：") + mTcpSocket->errorString(), false);
            mEnableCheckBox->setChecked(false);
            closeDev();
            return;
        }

        connect(mTcpSocket, &QTcpSocket::readyRead, this, &SAKOtherTransmissionItemTcp::read);
        mTcpSocket->connectToHost(mServerAddressLineEdit->text(), static_cast<quint16>(mServerPortLineEdit->text().toInt()));
        if (!mTcpSocket->waitForConnected()){
            emit requestOutputMessage(tr("无法连接服务器：") + mTcpSocket->errorString(), false);
            mEnableCheckBox->setChecked(false);
            closeDev();
        }else{
            this->setUiEnable(false);
        }
    }else{
        closeDev();
    }
}

void SAKOtherTransmissionItemTcp::read()
{    
    if (mTcpSocket){
        QByteArray data = mTcpSocket->readAll();
        if (mHandleReceiveDataCheckBox->isChecked()){
            emit bytesRead(data);;
        }
    }
}

void SAKOtherTransmissionItemTcp::setUiEnable(bool enable)
{
    mCustomAddressCheckBox->setEnabled(enable);
    mLocalAddressComboBox->setEnabled(enable);
    mLocalPortLineEdit->setEnabled(enable);
    mServerAddressLineEdit->setEnabled(enable);
    mServerPortLineEdit->setEnabled(enable);
}
