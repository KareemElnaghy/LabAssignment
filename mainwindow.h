#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void printArr();
    int Binary(int);
    int Normal(int);
    void Fill();
    void Swap(int&, int&);
    void MergeSort(int, int);
    void Merge(int, int, int);
    void resetAll();


private slots:
    void on_normal_button_clicked();

    void on_binary_button_clicked();

    void on_generate_button_clicked();

    void on_mergeSort_button_clicked();

    void on_stl_button_clicked();

    void on_findIt_button_clicked();


    void on_exit_Button_clicked();

private:
    Ui::MainWindow *ui;
    int size;
    int *arr;
    bool normalSearch;
    bool binarySearch;
   float timeTaken_sort;
   float timeTaken_search;
   int idx;
   bool sorted;
   bool arrayGenerated;
   bool targetValue;

};
#endif // MAINWINDOW_H
