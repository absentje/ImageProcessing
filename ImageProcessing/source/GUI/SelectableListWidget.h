#pragma once
#include <QGroupBox>
#include <string>
#include <vlCore/Object.hpp>
#include <vector>

class SelectableList;
class QComboBox;
class QVBoxLayout;
class Selectable;

class SelectableListWidget: public QGroupBox
{
	Q_OBJECT
public:
	SelectableListWidget( SelectableList* list, QWidget* parent );
	void AddSelectableName( const std::wstring& name );

private:
	SelectableList* list_ = nullptr;

	QVBoxLayout* mainLayout = nullptr;
	QComboBox* comboBox_ = nullptr;
	QWidget* curSelectedWidget_ = nullptr;

	void					TextChanged_( const QString& str );
};
