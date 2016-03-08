#include "DOtherSide/DOtherSide.h"

#include <iostream>

#include <QtCore/QDir>
#include <QtCore/QDebug>
#include <QtCore/QModelIndex>
#include <QtCore/QHash>
#include <QtCore/QResource>
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlContext>
#include <QtQml/QQmlApplicationEngine>
#include <QtQuick/QQuickView>
#include <QtWidgets/QApplication>

#include "DOtherSide/DynamicQObject.h"
#include "DOtherSide/BaseQAbstractListModel.h"
#include "DOtherSide/BaseQObject.h"
#include "DOtherSide/OnSlotExecutedHandler.h"

void convert_to_cstring(const QString& source, char** destination)
{
    QByteArray array = source.toUtf8();
    *destination = qstrdup(array.data());
}

void dos_qcoreapplication_application_dir_path(char** result)
{
    convert_to_cstring(QCoreApplication::applicationDirPath(), result);
}

void dos_qcoreapplication_add_library_path(const char* path)
{
	        QCoreApplication::addLibraryPath(QString(path));
}


void dos_qguiapplication_create()
{
    static int argc = 1;
    static char empty[1] = {0};
    static char* argv[] = {empty};
    new QGuiApplication(argc, argv);
}

void dos_qguiapplication_delete()
{
    delete qApp;
}

void dos_qguiapplication_exec()
{
    qApp->exec();
}

void dos_qguiapplication_quit()
{
    qApp->quit();
}

void dos_qapplication_create()
{
    static int argc = 1;
    static char empty[1] = {0};
    static char* argv[] = {empty};
    new QApplication(argc, argv);
}

void dos_qapplication_delete()
{
    delete qApp;
}

void dos_qapplication_exec()
{
    qApp->exec();
}

void dos_qapplication_quit()
{
    qApp->quit();
}

void dos_qqmlapplicationengine_create(void** vptr)
{
    *vptr = new QQmlApplicationEngine();
}

void dos_qqmlapplicationengine_load(void* vptr, const char* filename)
{
    QQmlApplicationEngine* engine = reinterpret_cast<QQmlApplicationEngine*>(vptr);
    engine->load(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + QDir::separator() + QString(filename)));
}

void dos_qqmlapplicationengine_load_url(void* vptr, void* url)
{
    QQmlApplicationEngine* engine = reinterpret_cast<QQmlApplicationEngine*>(vptr);
    QUrl* qurl = reinterpret_cast<QUrl*>(url);
    engine->load(*qurl);
}

void dos_qqmlapplicationengine_add_import_path(void* vptr, const char* path)
{
    QQmlApplicationEngine* engine = reinterpret_cast<QQmlApplicationEngine*>(vptr);
    engine->addImportPath(QString(path));
}

void dos_qqmlapplicationengine_context(void* vptr, void** context)
{
    QQmlApplicationEngine* engine = reinterpret_cast<QQmlApplicationEngine*>(vptr);
    engine->rootContext();
    *context = engine->rootContext();
}

void dos_qqmlapplicationengine_rootObjects(void* vptr, void*** array, int* array_length)
{
    QQmlApplicationEngine* engine = reinterpret_cast<QQmlApplicationEngine*>(vptr);
    QList<QObject*> list = engine->rootObjects();
    auto objects = new QObject*[list.size()];
    if (objects == nullptr) return;
    for (int i = 0; i < list.length(); i += 1) objects[i] = list.at(i);
    *array = reinterpret_cast<void**>(objects);
    *array_length = list.length();
}

void dos_qqmlapplicationengine_delete(void* vptr)
{
    QQmlApplicationEngine* engine = reinterpret_cast<QQmlApplicationEngine*>(vptr);
    delete engine;
}

void dos_qquickview_create(void** vptr)
{
    *vptr = new QQuickView();
}

void dos_qquickview_show(void* vptr)
{
    QQuickView* view = reinterpret_cast<QQuickView*>(vptr);
    view->show();
}

void dos_qquickview_delete(void* vptr)
{
    QQuickView* view = reinterpret_cast<QQuickView*>(vptr);
    delete view;
}

void dos_qquickview_source(void* vptr, char** result)
{
    QQuickView* view = reinterpret_cast<QQuickView*>(vptr);
    QUrl url = view->source();
    convert_to_cstring(url.toString(), result);
}

void dos_qquickview_set_source(void* vptr, const char* filename)
{
    QQuickView* view = reinterpret_cast<QQuickView*>(vptr);
    view->setSource(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + QDir::separator() + QString(filename)));
}

void dos_qquickview_set_source_url(void* vptr, void* url)
{
    QQuickView* view = reinterpret_cast<QQuickView*>(vptr);
    QUrl* _url = reinterpret_cast<QUrl*>(url);
    view->setSource(*_url);
}

void dos_qquickview_set_resize_mode(void* vptr, int resizeMode)
{
    QQuickView* view = reinterpret_cast<QQuickView*>(vptr);
    view->setResizeMode((QQuickView::ResizeMode) resizeMode);
}

void dos_qquickview_rootContext(void* vptr, void** context)
{
    QQuickView* view = reinterpret_cast<QQuickView*>(vptr);
    *context = view->rootContext();
}

void dos_chararray_delete(char* ptr)
{
    if (ptr) delete[] ptr;
}

void dos_qobjectptr_array_delete(void** ptr)
{
    if (ptr) delete[] ptr;
}

void dos_qqmlcontext_baseUrl(void* vptr, char** result)
{
    QQmlContext* context = reinterpret_cast<QQmlContext*>(vptr);
    QUrl url = context->baseUrl();
    convert_to_cstring(url.toString(), result);
}

void dos_qqmlcontext_setcontextproperty(void* vptr, const char* name, void* value)
{
    QQmlContext* context = reinterpret_cast<QQmlContext*>(vptr);
    auto variant = reinterpret_cast<QVariant*>(value);
    context->setContextProperty(QString::fromUtf8(name), *variant);
}

void dos_qvariant_create(void** vptr)
{
    *vptr = new QVariant();
}

void dos_qvariant_create_int(void** vptr, int value)
{
    *vptr = new QVariant(value);
}

void dos_qvariant_create_bool(void** vptr, bool value)
{
    *vptr = new QVariant(value);
}

void dos_qvariant_create_string(void** vptr, const char* value)
{
    *vptr = new QVariant(value);
}

void dos_qvariant_create_qvariant(void** vptr, void* other)
{
    auto newQVariant = new QVariant();
    auto otherQVariant = reinterpret_cast<QVariant*>(other);
    *newQVariant = *otherQVariant;
    *vptr = newQVariant;
}

void dos_qvariant_create_qobject(void** vptr, void* value)
{
    auto qobject = reinterpret_cast<QObject*>(value);
    auto variant = new QVariant();
    variant->setValue<QObject*>(qobject);
    *vptr = variant;
}

void dos_qvariant_create_float(void** vptr, float value)
{
    *vptr = new QVariant(value);
}

void dos_qvariant_create_double(void** vptr, double value)
{
    *vptr = new QVariant(value);
}

void dos_qvariant_create_qabstractlistmodel(void** vptr, void* value)
{
    auto qobject = reinterpret_cast<QObject*>(value);
    auto variant = new QVariant();
    variant->setValue<QObject*>(qobject);
    *vptr = variant;
}

void dos_qvariant_isnull(void* vptr, bool* isNull)
{
    auto variant = reinterpret_cast<QVariant*>(vptr);
    *isNull = variant->isNull();
}

void dos_qvariant_delete(void* vptr)
{
    auto variant = reinterpret_cast<QVariant*>(vptr);
    delete variant;
}

void dos_qvariant_assign(void* vptr, void* other)
{
    auto leftQVariant = reinterpret_cast<QVariant*>(vptr);
    auto rightQVariant = reinterpret_cast<QVariant*>(other);
    *leftQVariant = *rightQVariant;
}

void dos_qvariant_toInt(void* vptr, int* value)
{
    auto variant = reinterpret_cast<QVariant*>(vptr);
    *value = variant->toInt();
}

void dos_qvariant_toBool(void* vptr, bool* value)
{
    auto variant = reinterpret_cast<QVariant*>(vptr);
    *value = variant->toBool();
}

void dos_qvariant_toFloat(void* vptr, float* value)
{
    auto variant = reinterpret_cast<QVariant*>(vptr);
    *value = variant->toFloat();
}

void dos_qvariant_toDouble(void* vptr, double* value)
{
    auto variant = reinterpret_cast<QVariant*>(vptr);
    *value = variant->toDouble();
}

void dos_qvariant_toString(void* vptr, char** ptr)
{
    auto variant = reinterpret_cast<QVariant*>(vptr);
    convert_to_cstring(variant->toString(), ptr);
}

void dos_qvariant_toQObject(void* vptr, void** value)
{
    auto variant = reinterpret_cast<QVariant*>(vptr);
    *value = variant->value<QObject*>();
}

void dos_qvariant_setInt(void* vptr, int value)
{
    auto variant = reinterpret_cast<QVariant*>(vptr);
    *variant = value;
}

void dos_qvariant_setBool(void* vptr, bool value)
{
    auto variant = reinterpret_cast<QVariant*>(vptr);
    *variant = value;
}

void dos_qvariant_setFloat(void* vptr, float value)
{
    auto variant = reinterpret_cast<QVariant*>(vptr);
    *variant = value;
}

void dos_qvariant_setDouble(void* vptr, double value)
{
    auto variant = reinterpret_cast<QVariant*>(vptr);
    *variant = value;
}

void dos_qvariant_setString(void* vptr, const char* value)
{
    auto variant = reinterpret_cast<QVariant*>(vptr);
    *variant = value;
}

void dos_qvariant_setQObject(void* vptr, void* value)
{
    auto variant = reinterpret_cast<QVariant*>(vptr);
    auto qobject = reinterpret_cast<QObject*>(value);
    variant->setValue<QObject*>(qobject);
}

void dos_qvariant_setQAbstractListModel(void* vptr, void* value)
{
    auto variant = reinterpret_cast<QVariant*>(vptr);
    auto qobject = reinterpret_cast<QObject*>(value);
    variant->setValue<QObject*>(qobject);
}

void dos_qobject_create(void** vptr, void* dObjectPointer, DObjectCallback dObjectCallback)
{
    auto dynamicQObject = new BaseQObject();
    QQmlEngine::setObjectOwnership(dynamicQObject, QQmlEngine::CppOwnership);
    dynamicQObject->setOnSlotExecutedHandler(OnSlotExecutedHandler(dObjectPointer, dObjectCallback));
    *vptr = dynamicQObject;
}

void dos_qobject_delete(void* vptr)
{
    auto dynamicQObject = reinterpret_cast<BaseQObject*>(vptr);
    dynamicQObject->disconnect();
    delete dynamicQObject;
}

void dos_qobject_slot_create(void* vptr, const char* name, int parametersCount, int* parametersMetaTypes, int* slotIndex)
{
    if (parametersCount <= 0)
        return;

    auto qobject = reinterpret_cast<QObject*>(vptr);
    auto dynamicQObject = dynamic_cast<IDynamicQObject*>(qobject);

    QMetaType::Type returnType = static_cast<QMetaType::Type>(parametersMetaTypes[0]);
    QList<QMetaType::Type> argumentsTypes;
    for (int i = 1; i < parametersCount; ++i)
        argumentsTypes << static_cast<QMetaType::Type>(parametersMetaTypes[i]);

    dynamicQObject->registerSlot(QString::fromStdString(name), returnType, argumentsTypes, *slotIndex);
}

void dos_qobject_signal_create(void* vptr, const char* name, int parametersCount, int* parametersMetaTypes, int* signalIndex)
{
    if (parametersCount < 0)
        return;

    auto qobject = reinterpret_cast<QObject*>(vptr);
    auto dynamicQObject = dynamic_cast<IDynamicQObject*>(qobject);

    QList<QMetaType::Type> argumentsTypes;
    for (int i = 0; i < parametersCount; ++i)
        argumentsTypes << static_cast<QMetaType::Type>(parametersMetaTypes[i]);

    dynamicQObject->registerSignal(QString::fromStdString(name), argumentsTypes, *signalIndex);
}

void dos_qobject_signal_emit(void* vptr, const char* name, int parametersCount, void** parameters)
{
    auto qobject = reinterpret_cast<QObject*>(vptr);
    auto dynamicQObject = dynamic_cast<IDynamicQObject*>(qobject);

    QVariantList arguments;
    for (int i = 0; i < parametersCount; ++i)
        arguments << *(reinterpret_cast<QVariant*>(parameters[i]));

    dynamicQObject->emitSignal(QString::fromStdString(name), arguments);
}

void dos_qobject_signal_connect(void* senderVPtr,
                                const char* signal,
                                void* receiverVPtr,
                                const char* method,
                                int type,
                                bool* result)
{
    auto sender = reinterpret_cast<QObject*>(senderVPtr);
    auto receiver = reinterpret_cast<QObject*>(receiverVPtr);
    *result = QObject::connect(sender,
                               signal,
                               receiver,
                               method,
                               (Qt::ConnectionType) type);
}

void dos_qobject_signal_disconnect(void* senderVPtr,
                                   const char* signal,
                                   void* receiverVPtr,
                                   const char* method,
                                   bool* result)
{
    auto sender = reinterpret_cast<QObject*>(senderVPtr);
    auto receiver = reinterpret_cast<QObject*>(receiverVPtr);
    *result = QObject::disconnect(sender,
                                  signal,
                                  receiver,
                                  method);
}

void dos_qobject_property_create(void* vptr,
                                 const char* name,
                                 int type,
                                 const char* readSlot,
                                 const char* writeSlot,
                                 const char* notifySignal)
{
    auto qobject = reinterpret_cast<QObject*>(vptr);
    auto dynamicQObject = dynamic_cast<IDynamicQObject*>(qobject);
    dynamicQObject->registerProperty(QString(name),
                                     QMetaType::Type(type),
                                     QString(readSlot),
                                     QString(writeSlot),
                                     QString(notifySignal));
}

void dos_qobject_objectName(void* vptr, char** result)
{
    QObject* object = reinterpret_cast<QObject*>(vptr);
    convert_to_cstring(object->objectName(), result);
}

void dos_qobject_findChild(void* vptr, const char* name, int options, void** child)
{
    QObject* object = reinterpret_cast<QObject*>(vptr);
    *child = object->findChild<QObject*>(QString::fromUtf8(name), (Qt::FindChildOptions) options);
}

void dos_qmodelindex_create(void** vptr)
{
    auto index = new QModelIndex();
    *vptr = index;
}

void dos_qmodelindex_delete(void* vptr)
{
    auto index = reinterpret_cast<QModelIndex*>(vptr);
    delete index;
}

void dos_qmodelindex_row(void* vptr, int* row)
{
    auto index = reinterpret_cast<QModelIndex*>(vptr);
    *row = index->row();
}

void dos_qmodelindex_column(void* vptr, int* column)
{
    auto index = reinterpret_cast<QModelIndex*>(vptr);
    *column = index->column();
}

void dos_qmodelindex_isValid(void* vptr, bool* isValid)
{
    auto index = reinterpret_cast<QModelIndex*>(vptr);
    *isValid = index->isValid();
}

void dos_qmodelindex_data(void* vptr, int role, void* data)
{
    auto index = reinterpret_cast<QModelIndex*>(vptr);
    auto result = reinterpret_cast<QVariant*>(data);
    *result = index->data(role);
}

void dos_qmodelindex_parent(void* vptr, void* parent)
{
    auto index = reinterpret_cast<QModelIndex*>(vptr);
    auto parentIndex = reinterpret_cast<QModelIndex*>(parent);
    *parentIndex = index->parent();
}

void dos_qmodelindex_child(void* vptr, int row, int column, void* child)
{
    auto index = reinterpret_cast<QModelIndex*>(vptr);
    auto childIndex = reinterpret_cast<QModelIndex*>(child);
    *childIndex = index->child(row, column);
}

void dos_qmodelindex_sibling(void* vptr, int row, int column, void* sibling)
{
    auto index = reinterpret_cast<QModelIndex*>(vptr);
    auto siblingIndex = reinterpret_cast<QModelIndex*>(sibling);
    *siblingIndex = index->sibling(row, column);
}

void dos_qabstractlistmodel_create(void** vptr,
                                   void* dObjectPointer,
                                   DObjectCallback dObjectCallback,
                                   RowCountCallback rowCountCallback,
                                   ColumnCountCallback columnCountCallback,
                                   DataCallback dataCallback,
                                   SetDataCallback setDataCallback,
                                   RoleNamesCallback roleNamesCallaback,
                                   FlagsCallback flagsCallback,
                                   HeaderDataCallback headerDataCallback)
{
    auto model = new BaseQAbstractListModel(dObjectPointer,
                                            rowCountCallback,
                                            columnCountCallback,
                                            dataCallback,
                                            setDataCallback,
                                            roleNamesCallaback,
                                            flagsCallback,
                                            headerDataCallback);
    model->setOnSlotExecutedHandler(OnSlotExecutedHandler(dObjectPointer, dObjectCallback));
    *vptr = model;
}

void dos_qabstractlistmodel_delete(void* vptr)
{
    auto model = reinterpret_cast<BaseQAbstractListModel*>(vptr);
    delete model;
}

void dos_qabstractlistmodel_beginInsertRows(void* vptr, QModelIndexVoidPtr parentIndex, int first, int last)
{
    auto model = reinterpret_cast<BaseQAbstractListModel*>(vptr);
    auto index = reinterpret_cast<QModelIndex*>(parentIndex);
    model->publicBeginInsertRows(*index, first, last);
}

void dos_qabstractlistmodel_endInsertRows(void* vptr)
{
    auto model = reinterpret_cast<BaseQAbstractListModel*>(vptr);
    model->publicEndInsertRows();
}

void dos_qabstractlistmodel_beginRemoveRows(void* vptr, QModelIndexVoidPtr parentIndex, int first, int last)
{
    auto model = reinterpret_cast<BaseQAbstractListModel*>(vptr);
    auto index = reinterpret_cast<QModelIndex*>(parentIndex);
    model->publicBeginRemoveRows(*index, first, last);
}

void dos_qabstractlistmodel_endRemoveRows(void* vptr)
{
    auto model = reinterpret_cast<BaseQAbstractListModel*>(vptr);
    model->publicEndRemoveRows();
}

void dos_qabstractlistmodel_beginResetModel(void* vptr)
{
    auto model = reinterpret_cast<BaseQAbstractListModel*>(vptr);
    model->publicBeginResetModel();
}

void dos_qabstractlistmodel_endResetModel(void* vptr)
{
    auto model = reinterpret_cast<BaseQAbstractListModel*>(vptr);
    model->publicEndResetModel();
}

void dos_qabstractlistmodel_dataChanged(void* vptr,
                                        QModelIndexVoidPtr topLeftIndex,
                                        QModelIndexVoidPtr bottomRightIndex,
                                        int* rolesArrayPtr,
                                        int rolesArrayLength)
{
    auto model = reinterpret_cast<BaseQAbstractListModel*>(vptr);
    auto topLeft = reinterpret_cast<QModelIndex*>(topLeftIndex);
    auto bottomRight = reinterpret_cast<QModelIndex*>(bottomRightIndex);
    auto roles = QVector<int>::fromStdVector(std::vector<int>(rolesArrayPtr, rolesArrayPtr + rolesArrayLength));
    model->publicDataChanged(*topLeft, *bottomRight, roles);
}

void dos_qhash_int_qbytearray_create(QHashIntQByteArrayVoidPtr* vptr)
{
    *vptr = new QHash<int, QByteArray>();
}

void dos_qhash_int_qbytearray_delete(QHashIntQByteArrayVoidPtr vptr)
{
    auto qHash = reinterpret_cast<QHash<int, QByteArray>*>(vptr);
    delete qHash;
}

void dos_qhash_int_qbytearray_insert(QHashIntQByteArrayVoidPtr vptr, int key, const char* value)
{
    auto qHash = reinterpret_cast<QHash<int, QByteArray>*>(vptr);
    qHash->insert(key, QByteArray(value));
}

void dos_qhash_int_qbytearray_value(QHashIntQByteArrayVoidPtr vptr, int key, char** result)
{
    auto qHash = reinterpret_cast<QHash<int, QByteArray>*>(vptr);
    QByteArray value = qHash->value(key);
    *result = qstrdup(value.data());
}

void dos_qresource_register(const char* filename)
{
    QResource::registerResource(QString::fromUtf8(filename));
}

void dos_qurl_create(void** vptr, const char* url, int parsingMode)
{
    *vptr = new QUrl(QString::fromUtf8(url), (QUrl::ParsingMode) parsingMode);
}

void dos_qurl_delete(void* vptr)
{
    QUrl* url = reinterpret_cast<QUrl*>(vptr);
    delete url;
}

void dos_qurl_to_string(void* vptr, char** result)
{
    QUrl* url = reinterpret_cast<QUrl*>(vptr);
    convert_to_cstring(url->toString(), result);
}

