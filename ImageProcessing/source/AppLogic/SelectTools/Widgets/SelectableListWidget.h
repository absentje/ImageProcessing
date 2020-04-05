#pragma once
#include <QGroupBox>

class SelectableList;
class QComboBox;
class QVBoxLayout;

class SelectableListWidget: public QGroupBox
{
	Q_OBJECT
public:
	SelectableListWidget( SelectableList* list, QWidget* parent );

	void SetCurrentSelectedWidget( QWidget* widget );

private:
	SelectableList* list_ = nullptr;

	QVBoxLayout* mainLayout = nullptr;
	QComboBox* comboBox_ = nullptr;
	QWidget* curSelectedWidget_ = nullptr;

	void TextChanged_( const QString& str );
};
