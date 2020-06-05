﻿/*
 * Copyright 2020 Qter. All rights reserved.
 *
 * This file is encoding with utf-8 (with BOM). It is a part of QtSwissArmyKnife
 * project, which is an open source project. you can get the source from:
 *     https://github.com/qsak/QtSwissArmyKnife
 * or
 *     https://gitee.com/qsak/QtSwissArmyKnife
 * ----------------------------------------------------------------------------
 * QQ Group     : 952218522
 * Bug Report   : qsak@foxmail.com
 * Official Web : https://qsak.pro
 */
#ifndef SAKDEBUGPAGEDATABASEMANAGER_HH
#define SAKDEBUGPAGEDATABASEMANAGER_HH

#include <QObject>
#include <QSqlQuery>
#include <QSqlDatabase>

class SAKDebugPage;
/// @brief 为数据库读写提供了一套接口，主要是用户配置内容的读写
class SAKDebugPageDatabaseInterface : public QObject
{
    Q_OBJECT
public:
    friend SAKDebugPage;
    /// @brief 自动应答数据表
    struct AutoResponseTable {
        QString tableName;              /// 自动回复表名称
        QString idColumn;               /// 自动回复条目ID
        QString nameColumn;             /// 自动回复条目名称
        QString referenceDataColumn;    /// 自动回复条目参考数据
        QString responseDataColumn;     /// 自动回复条目回复数据
        QString enableColumn;           /// 是否使能该自动回复条目
        QString referenceFormatColumn;  /// 自动回复条目参考数据格式
        QString responseFormatColumn;   /// 自动回复条目应答数据格式
    };

    /// @brief 定时发送数据表
    struct TimingSendingTable {

    };

    /// @brief 数据预设数据表
    struct PresettingDataTable{

    };
private:
    SAKDebugPageDatabaseInterface(QObject *parent = Q_NULLPTR);
    ~SAKDebugPageDatabaseInterface();
public:
    static SAKDebugPageDatabaseInterface *instance();
private:
    static SAKDebugPageDatabaseInterface *instancePtr;
    QSqlDatabase sakDatabase;
    QSqlQuery sakDatabaseQuery;
    QList<AutoResponseTable> autoResponseTableList;
    QString databaseName;
private:
    void initDatabase();
    void createTables();
    void createAutoResponseTables();
    bool createAutoResponseTable(const AutoResponseTable &table);
};

#endif
