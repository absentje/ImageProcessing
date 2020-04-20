#pragma once
#include <QGroupBox>
#include <string>
#include <vlCore/Object.hpp>

class SelectableList;
class QComboBox;
class QVBoxLayout;
class Selectable;

class SelectableListWidget: public QGroupBox
{
	Q_OBJECT
public:
	SelectableListWidget( SelectableList* list, QWidget* parent );

private:
	SelectableList* list_ = nullptr;

	QVBoxLayout* mainLayout = nullptr;
	QComboBox* comboBox_ = nullptr;
	QWidget* curSelectedWidget_ = nullptr;
	std::wstring curSelectedStr_;

	void					TextChanged_( const QString& str );
	vl::ref<Selectable>		getSelectable_( const std::wstring& str );
};
