#include "mainwindow.hpp"
#include <QVBoxLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QComboBox>
#include <QCheckBox>
#include <QLabel>
#include <QString>
#include <QMessageBox>
#include "../taylor_controller.hpp"
#include <sstream>

std::ostringstream ss;

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    controller = new TaylorController();	      
    auto* central = new QWidget(this);	
    auto* layout = new QVBoxLayout();

    functionInput = new QLineEdit();
    layout->addWidget(new QLabel("Функция"));
    layout->addWidget(functionInput);

    reductionBox = new QCheckBox("Use reduction");
    reductionBox->setChecked(true);
    layout->addWidget(reductionBox);

    modeBox = new QComboBox();
    modeBox->addItem("r");
    modeBox->addItem("n");
    modeBox->addItem("x");
    layout->addWidget(modeBox);
			
    xInput = new QLineEdit();
    layout->addWidget(new QLabel("x"));
    layout->addWidget(xInput);

    nInput = new QLineEdit();
    layout->addWidget(new QLabel("n"));
    layout->addWidget(nInput);

    accInput = new QLineEdit();
    layout->addWidget(new QLabel("accuracy"));
    layout->addWidget(accInput);

    dxInput = new QLineEdit();
    layout->addWidget(new QLabel("dx"));
    layout->addWidget(dxInput);

    button = new QPushButton("Calculate");
    layout->addWidget(button);
    output = new QTextEdit();			
    output->setReadOnly(true);			
    layout->addWidget(output);

    central->setLayout(layout);
    setCentralWidget(central);
			
    connect(button, &QPushButton::clicked, this, &MainWindow::onCalculate);
}

void MainWindow::onCalculate() {
    try {
	std::string func = functionInput->text().toStdString();			           
       	bool reduction = reductionBox->isChecked();
				       
   	std::string mode = modeBox->currentText().toStdString();					          
      	if (mode == "r") {						        
		double x = xInput->text().toDouble();			
		unsigned n = nInput->text().toUInt();
		controller->runRemainder(func, reduction, x, n, ss);
		output->setText(QString::fromStdString(ss.str()));		
	} else if (mode == "n") {			
		double x = xInput->text().toDouble();				
		double acc = accInput->text().toDouble();							
		controller->runDegree(func, reduction, x, acc, ss);
		output->setText(QString::fromStdString(ss.str()));    
	} else if (mode == "x") {		
		double acc = accInput->text().toDouble();				
		double dx = dxInput->text().toDouble();							
		unsigned n = nInput->text().toUInt();		
		controller->runInterval(func, reduction, dx, acc, n, ss);
		output->setText(QString::fromStdString(ss.str()));    
	}
    } catch (const std::exception& e) {QMessageBox::critical(this, "Error", e.what());}
}
