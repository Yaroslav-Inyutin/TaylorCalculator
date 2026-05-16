#pragma once
#include <QMainWindow>
class QLineEdit;
class QTextEdit;
class QPushButton;
class QComboBox;
class QCheckBox;
class TaylorController;
class MainWindow : public QMainWindow {
Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);
private slots:
    void onCalculate();
private:
    QLineEdit* functionInput;			     
    QLineEdit* xInput;			
    QLineEdit* nInput;	
    QLineEdit* accInput;		
    QLineEdit* dxInput;		
    QComboBox* modeBox;		
    QCheckBox* reductionBox;			
    QTextEdit* output;		
    QPushButton* button;		
    TaylorController* controller;
};
