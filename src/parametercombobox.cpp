#include "parametercombobox.h"

ParameterComboBox::ParameterComboBox(ParameterObject *parameterobject)
{
    object=parameterobject;
    setName(QString::fromStdString(object->name));
    setValue();
    connect(comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(on_Changed(int)));
    setDescription(QString::fromStdString(object->descritpion));
}

void ParameterComboBox::on_Changed(int idx){
    if(object->dvt == Value::STRING){
        const string v = comboBox->currentText().toUtf8().constData();
        object->value = ValuePtr(v);
    }else{
        const double v = comboBox->currentText().toDouble();
        object->value = ValuePtr(v);
    }
    emit changed();
}

void ParameterComboBox::setValue(){

    this->stackedWidget->setCurrentWidget(this->pageComboBox);
    comboBox->clear();
    const Value::VectorType& vec = object->values->toVector();
    for (Value::VectorType::const_iterator it = vec.begin(); it != vec.end(); it++) {
        const ValuePtr *v = &(*it);
        comboBox->addItem(QString::fromStdString((*it)->toString()), qVariantFromValue((void *)v));
    }
    QString defaultText = QString::fromStdString(object->value->toString());
    int idx = comboBox->findText(defaultText);
    if (idx >= 0) {
        comboBox->setCurrentIndex(idx);
    }
}


