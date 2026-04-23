#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_generateButton_clicked();
    void on_inputButton_clicked();
    void on_sortButton_clicked();
    void on_stepButton_clicked();
    void on_resetButton_clicked();
    void on_buildHeapButton_clicked();
    void sortStep();
    void buildHeapStep();

    void on_CloseButton_clicked();

private:
    Ui::MainWindow *ui;
    QVector<int> heapArray;
    QVector<int> originalArray;
    int currentStep;
    int heapSize;
    int buildHeapIndex;
    QTimer *animationTimer;
    QTimer *buildHeapTimer;
    bool isSorting;
    bool isBuildingHeap;
    bool isMinHeap; // 新增：标记是否为最小堆

    void buildHeap(); // 修改：通用堆构建函数
    void heapify(int n, int i);
    void updateHeapDisplay();
    void drawHeap(QPainter &painter, int index, int x, int y, int level, int maxLevel);
    void swapElements(int i, int j);

    void paintEvent(QPaintEvent *event) override;
};

#endif // MAINWINDOW_H
