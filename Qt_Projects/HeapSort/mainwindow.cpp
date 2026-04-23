#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QInputDialog>
#include <QMessageBox>
#include <QRandomGenerator>
#include <algorithm>
#include <QPaintEvent>
#include <QTextEdit>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QIntValidator>

struct HighlightInfo {
    int index;
    QColor color;
    QString message;
};
QVector<HighlightInfo> currentHighlights;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , currentStep(0)
    , heapSize(0)
    , buildHeapIndex(-1)
    , isSorting(false)
    , isBuildingHeap(false)
    , isMinHeap(true) // 默认使用最小堆
{
    ui->setupUi(this);

    // 设置窗口标题显示当前堆类型
    this->setWindowTitle("堆排序可视化 - 最小堆");

    animationTimer = new QTimer(this);
    buildHeapTimer = new QTimer(this);
    connect(animationTimer, &QTimer::timeout, this, &MainWindow::sortStep);
    connect(buildHeapTimer, &QTimer::timeout, this, &MainWindow::buildHeapStep);

    ui->sortButton->setEnabled(false);
    ui->stepButton->setEnabled(false);
    ui->resetButton->setEnabled(false);
    ui->buildHeapButton->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_generateButton_clicked()
{
    bool ok;
    int n = QInputDialog::getInt(this, tr("生成随机数据"),
                                 tr("请输入要生成的整数数量:"), 10, 1, 20, 1, &ok);
    if (!ok) return;

    heapArray.clear();
    originalArray.clear();
    currentHighlights.clear();

    for (int i = 0; i < n; ++i) {
        int value = QRandomGenerator::global()->bounded(1, 100);
        heapArray.append(value);
        originalArray.append(value);
    }

    heapSize = heapArray.size();
    currentStep = 0;
    buildHeapIndex = -1;
    isSorting = false;
    isBuildingHeap = false;

    ui->sortButton->setEnabled(true);
    ui->stepButton->setEnabled(true);
    ui->resetButton->setEnabled(true);
    ui->buildHeapButton->setEnabled(true);

    updateHeapDisplay();
}

void MainWindow::on_buildHeapButton_clicked()
{
    if (isBuildingHeap) {
        buildHeapTimer->stop();
        ui->buildHeapButton->setText("开始构建堆");
        isBuildingHeap = false;
    } else {
        buildHeapIndex = heapSize / 2 - 1;
        currentStep = 0;
        currentHighlights.clear();
        buildHeapTimer->start(1500);
        ui->buildHeapButton->setText("暂停构建");
        isBuildingHeap = true;

        ui->sortButton->setEnabled(false);
        ui->stepButton->setEnabled(false);
    }
}

void MainWindow::buildHeapStep()
{
    if (buildHeapIndex < 0) {
        buildHeapTimer->stop();
        ui->buildHeapButton->setText("构建完成");
        ui->buildHeapButton->setEnabled(false);

        ui->sortButton->setEnabled(true);
        ui->stepButton->setEnabled(true);

        currentHighlights.clear();
        QString heapType = isMinHeap ? "最小堆" : "最大堆";
        currentHighlights.append({-1, QColor(0, 255, 0), heapType + "构建完成！"});
        updateHeapDisplay();
        return;
    }

    currentHighlights.clear();
    currentHighlights.append({buildHeapIndex, QColor(255, 200, 0),
                              QString("正在处理节点 %1 (值: %2)").arg(buildHeapIndex).arg(heapArray[buildHeapIndex])});

    heapify(heapSize, buildHeapIndex);

    currentStep++;
    buildHeapIndex--;

    updateHeapDisplay();
}

void MainWindow::heapify(int n, int i)
{
    int target = i; // 修改：使用通用名称
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // 高亮比较过程
    if (left < n) {
        currentHighlights.append({left, QColor(200, 200, 255),
                                  QString("比较左子节点 %1 (值: %2)").arg(left).arg(heapArray[left])});
    }
    if (right < n) {
        currentHighlights.append({right, QColor(200, 200, 255),
                                  QString("比较右子节点 %1 (值: %2)").arg(right).arg(heapArray[right])});
    }

    // 修改：最小堆的比较逻辑
    if (isMinHeap) {
        if (left < n && heapArray[left] < heapArray[target]) {
            target = left;
        }
        if (right < n && heapArray[right] < heapArray[target]) {
            target = right;
        }
    } else {
        // 最大堆的比较逻辑（保留以备切换）
        if (left < n && heapArray[left] > heapArray[target]) {
            target = left;
        }
        if (right < n && heapArray[right] > heapArray[target]) {
            target = right;
        }
    }

    if (target != i) {
        QString heapType = isMinHeap ? "最小" : "最大";
        currentHighlights.append({target, QColor(255, 100, 100),
                                  QString("需要交换: 节点 %1 ↔ 节点 %2 (%3值)").arg(i).arg(target).arg(heapType)});

        swapElements(i, target);
        heapify(n, target);
    } else {
        currentHighlights.append({i, QColor(100, 255, 100),
                                  QString("节点 %1 已在正确位置").arg(i)});
    }
}

void MainWindow::buildHeap()
{
    heapSize = heapArray.size();
    for (int i = heapSize / 2 - 1; i >= 0; i--) {
        heapify(heapSize, i);
    }
}

void MainWindow::sortStep()
{
    if (heapSize <= 1) {
        animationTimer->stop();
        ui->sortButton->setEnabled(false);
        ui->stepButton->setEnabled(false);
        ui->sortButton->setText("排序完成");

        currentHighlights.clear();
        currentHighlights.append({-1, QColor(0, 255, 0), "排序完成！结果为从小到大排序"});
        updateHeapDisplay();
        return;
    }

    currentHighlights.clear();
    QString operation = isMinHeap ? "交换堆顶(最小)元素和最后一个元素" : "交换堆顶(最大)元素和最后一个元素";
    currentHighlights.append({0, QColor(255, 200, 0), operation});
    currentHighlights.append({heapSize-1, QColor(255, 200, 0), operation});

    swapElements(0, heapSize - 1);
    heapSize--;

    if (heapSize > 0) {
        currentHighlights.append({0, QColor(255, 150, 0), "重新堆化根节点"});
        heapify(heapSize, 0);
    }

    currentStep++;
    updateHeapDisplay();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    if (heapArray.isEmpty()) return;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int startY = 200;

    // 绘制堆类型提示
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 12, QFont::Bold));
    QString heapType = isMinHeap ? "最小堆" : "最大堆";
    painter.drawText(20, 30, "当前堆类型: " + heapType);

    // 计算堆的深度
    int depth = 0;
    int nodes = heapSize;
    while (nodes > 0) {
        depth++;
        nodes >>= 1;
    }

    if (depth > 0) {
        drawHeap(painter, 0, width() / 2, startY, 1, depth);
    }

    // 绘制高亮信息
    if (!currentHighlights.isEmpty()) {
        painter.setPen(Qt::white);
        painter.setFont(QFont("Arial", 10));

        int yPos = 50;
        for (const HighlightInfo &info : currentHighlights) {
            if (info.index == -1) {
                painter.setPen(Qt::white);
                painter.drawText(20, yPos, info.message);
                painter.setPen(Qt::white);
            } else {
                painter.drawText(20, yPos, info.message);
            }
            yPos += 20;
        }
    }
}

void MainWindow::drawHeap(QPainter &painter, int index, int x, int y, int level, int maxLevel)
{
    if (index >= heapArray.size()) return;

    int horizontalSpacing = 300 / (level + 1);
    int verticalSpacing = 80;

    // 确定节点颜色
    QColor nodeColor = QColor(100, 150, 250);

    for (const HighlightInfo &info : currentHighlights) {
        if (info.index == index) {
            nodeColor = info.color;
            break;
        }
    }

    if (index >= heapSize) {
        nodeColor = QColor(150, 150, 150);
    }

    // 绘制节点
    painter.setBrush(nodeColor);
    painter.setPen(QPen(Qt::black, 2));
    painter.drawEllipse(QPoint(x, y), 30, 30);

    // 绘制索引
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 8));
    painter.drawText(QRect(x-15, y-45, 30, 20), Qt::AlignCenter, QString("[%1]").arg(index));

    // 绘制数值
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 12, QFont::Bold));
    painter.drawText(QRect(x-25, y-15, 50, 30), Qt::AlignCenter, QString::number(heapArray[index]));

    // 绘制子节点
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;

    if (leftChild < heapArray.size()) {
        int childX = x - horizontalSpacing;
        int childY = y + verticalSpacing;
        painter.setPen(QPen(Qt::black, 2));
        painter.drawLine(x, y + 30, childX, childY - 30);
        drawHeap(painter, leftChild, childX, childY, level + 1, maxLevel);
    }

    if (rightChild < heapArray.size()) {
        int childX = x + horizontalSpacing;
        int childY = y + verticalSpacing;
        painter.setPen(QPen(Qt::black, 2));
        painter.drawLine(x, y + 30, childX, childY - 30);
        drawHeap(painter, rightChild, childX, childY, level + 1, maxLevel);
    }
}

// 其他函数保持不变...
void MainWindow::on_inputButton_clicked()
{
    QDialog dialog(this);
    dialog.setWindowTitle("手动输入数据");
    dialog.resize(400, 300);

    QVBoxLayout *mainLayout = new QVBoxLayout(&dialog);

    QHBoxLayout *countLayout = new QHBoxLayout();
    QLabel *countLabel = new QLabel("数据个数 (n):", &dialog);
    QLineEdit *countEdit = new QLineEdit(&dialog);
    countEdit->setValidator(new QIntValidator(1, 20, &dialog));
    countEdit->setText("10");
    countLayout->addWidget(countLabel);
    countLayout->addWidget(countEdit);
    mainLayout->addLayout(countLayout);

    QLabel *dataLabel = new QLabel("请输入数据 (每行一个整数):", &dialog);
    mainLayout->addWidget(dataLabel);

    QTextEdit *dataEdit = new QTextEdit(&dialog);
    dataEdit->setPlaceholderText("例如:\n34\n12\n78\n56\n23\n...");
    mainLayout->addWidget(dataEdit);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *okButton = new QPushButton("确定", &dialog);
    QPushButton *cancelButton = new QPushButton("取消", &dialog);
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    mainLayout->addLayout(buttonLayout);

    connect(okButton, &QPushButton::clicked, &dialog, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        int n = countEdit->text().toInt();
        QStringList dataLines = dataEdit->toPlainText().split('\n', Qt::SkipEmptyParts);
        QVector<int> inputData;

        for (const QString &line : dataLines) {
            QString trimmedLine = line.trimmed();
            if (!trimmedLine.isEmpty()) {
                bool conversionOk;
                int value = trimmedLine.toInt(&conversionOk);
                if (conversionOk) {
                    inputData.append(value);
                }
            }
        }

        if (inputData.size() < n) {
            QMessageBox::warning(this, "输入错误",
                                 QString("输入的数据数量 (%1) 少于指定的个数 (%2)").arg(inputData.size()).arg(n));
            return;
        }

        heapArray.clear();
        originalArray.clear();
        currentHighlights.clear();

        for (int i = 0; i < n && i < inputData.size(); ++i) {
            heapArray.append(inputData[i]);
            originalArray.append(inputData[i]);
        }

        heapSize = heapArray.size();
        currentStep = 0;
        buildHeapIndex = -1;
        isSorting = false;
        isBuildingHeap = false;

        ui->sortButton->setEnabled(true);
        ui->stepButton->setEnabled(true);
        ui->resetButton->setEnabled(true);
        ui->buildHeapButton->setEnabled(true);

        updateHeapDisplay();
    }
}

void MainWindow::on_sortButton_clicked()
{
    if (isSorting) {
        animationTimer->stop();
        ui->sortButton->setText("开始排序");
        isSorting = false;
    } else {
        if (currentStep == 0) {
            buildHeap();
        }
        animationTimer->start(1000);
        ui->sortButton->setText("暂停排序");
        isSorting = true;
        ui->buildHeapButton->setEnabled(false);
    }
}

void MainWindow::on_stepButton_clicked()
{
    if (currentStep == 0) {
        buildHeap();
    } else {
        sortStep();
    }
}

void MainWindow::on_resetButton_clicked()
{
    animationTimer->stop();
    buildHeapTimer->stop();
    heapArray = originalArray;
    heapSize = heapArray.size();
    currentStep = 0;
    buildHeapIndex = -1;
    isSorting = false;
    isBuildingHeap = false;
    currentHighlights.clear();

    ui->sortButton->setText("开始排序");
    ui->buildHeapButton->setText("构建堆");
    ui->buildHeapButton->setEnabled(true);
    ui->sortButton->setEnabled(true);
    ui->stepButton->setEnabled(true);

    updateHeapDisplay();
}

void MainWindow::swapElements(int i, int j)
{
    std::swap(heapArray[i], heapArray[j]);
}

void MainWindow::updateHeapDisplay()
{
    update();

    QString status;
    if (currentStep == 0 && buildHeapIndex == -1) {
        status = "初始数组";
    } else if (isBuildingHeap) {
        status = QString("构建堆 - 第 %1 步").arg(currentStep);
    } else if (heapSize > 0) {
        status = QString("排序 - 第 %1 步: 堆大小 %2").arg(currentStep).arg(heapSize);
    } else {
        status = "排序完成!";
    }
    ui->statusLabel->setText(status);

    QString arrayText = "当前数组: [";
    for (int i = 0; i < heapArray.size(); ++i) {
        if (i < heapSize) {
            arrayText += QString::number(heapArray[i]);
        } else {
            arrayText += "<font color='green'>" + QString::number(heapArray[i]) + "</font>";
        }
        if (i < heapArray.size() - 1) {
            arrayText += ", ";
        }
    }
    arrayText += "]";
    ui->arrayLabel->setText(arrayText);
}

void MainWindow::on_CloseButton_clicked()
{
    this->close();
}

